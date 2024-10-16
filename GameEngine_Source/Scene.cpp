#include "pch.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "Application.h"
#include "TileRenderer.h"
#include "..\\GameEngine_Lib\\Tile.h"
#include "GameObject.h"
#include "Resources.h"
#include "Object.h"


extern GE::Application app;

GE::Scene::Scene() : mLayers{}
{
	mLayers.resize((UINT)eLayerType::MAX);
	for (size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i] = new Layer();
	}
}

GE::Scene::~Scene()
{
	for (auto& iter : mLayers)
	{
		delete iter;
		iter = nullptr;
	}
	for (auto& tile : mTiles)
	{
		for (auto& t : tile)
		{
			delete t;
			t = nullptr;
		}
	}
}

void GE::Scene::Initialize()
{
	for (Layer* layers : mLayers)
	{
		if (layers == nullptr)
			continue;
		layers->Initialize();
	}
}

void GE::Scene::Update()
{
	for (Layer* layers : mLayers)
	{
		if (layers == nullptr)
			continue;
		layers->Update();
	}
}

void GE::Scene::LateUpdate()
{
	for (Layer* layers : mLayers)
	{
		if (layers == nullptr)
			continue;
		layers->LateUpdate();
	}
}
void GE::Scene::Destroy()
{
	for (Layer* layers : mLayers)
	{
		if (layers == nullptr)
			continue;
		layers->Destroy();
	}
	
}
void GE::Scene::Render(HDC hdc)
{
	for (Layer* layers : mLayers)
	{
		if (layers == nullptr)
			continue;
		layers->Render(hdc);
	}
}
void GE::Scene::CreateTileBuffer(Vector2 tileCount)
{
	TileRenderer::TileRenderer();

	mTileCount = tileCount;
	mSize = Vector2( tileCount.x * TileRenderer::GetTileSize().x,
		tileCount.y * TileRenderer::GetTileSize().y);

	app.ChangeTileBuffer(mSize);

	mTiles.resize(tileCount.y);

	for (size_t y= 0; y < tileCount.y; y++)
	{
		mTiles[y].resize(tileCount.x);
		for (size_t x = 0; x < tileCount.x; x++)
		{
			Tile* tile = new Tile;
			TileRenderer* tileRenderer = tile->AddComponent<TileRenderer>();
			Texture* tileTex = Resources::Find<Texture>(L"SpringFloor");
			tileRenderer->SetTexture(tileTex);
			tileRenderer->SetIndex(Vector2(0, 0));
			tile->SetIndexPos(x, y);

			mTiles[y][x] = tile;
			tileRenderer->Render(app.GetBackTileHdc());
		}
	}

}
void GE::Scene::RenderTiles()
{
	for (auto& tilesX : mTiles)
	{
		for (auto& tile : tilesX)
		{
			tile->GetComponent<TileRenderer>()->Render(app.GetBackTileHdc());
		}
	}
}


void GE::Scene::AddGameObject(GameObject* gameObj,eLayerType type)
{
	mLayers[(UINT)type]->AddGameObject(gameObj); 
}

void GE::Scene::EraseGameObject(GameObject* gameObj)
{
	eLayerType layerType = gameObj->GetLayerType();
	mLayers[(UINT)layerType]->EraseGameObject(gameObj);
}
void GE::Scene::Load()
{
	OPENFILENAME ofn = {};
	wchar_t szFilePath[256] = {};
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (false == GetOpenFileName(&ofn))
		return;
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	if (pFile == nullptr)
		return;

	int tileCountX;
	int tileCountY;
	fread(&tileCountX, sizeof(int), 1, pFile);
	fread(&tileCountY, sizeof(int), 1, pFile);


	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int idxX = 0;
			int idxY = 0;
			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1)
				break;

			GetTiles()[y][x]->GetComponent<TileRenderer>()->SetIndex({ (float)idxX, (float)idxY });
			GetTiles()[y][x]->GetComponent<Transform>()->SetPos({ (float)posX , (float)posY });
			GetTiles()[y][x]->GetComponent<TileRenderer>()->Render(app.GetBackTileHdc());
		}
	}
	fclose(pFile);
}

void GE::Scene::LoadTileMap(const std::wstring& path , const std::wstring& name)
{
	std::wstring fullPath = path + L"\\" + name;
	// std::fstream 사용하여 파일 열기

	std::fstream file(fullPath, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::wcerr << L"Error: Could not open file for reading: " << fullPath << std::endl;
		return;
	}

	int tileCountX;
	int tileCountY;

	// 타일 개수 읽기
	file.read(reinterpret_cast<char*>(&tileCountX), sizeof(int));
	file.read(reinterpret_cast<char*>(&tileCountY), sizeof(int));

	for (int y = 0; y < tileCountY; y++) {
		for (int x = 0; x < tileCountX; x++) {
			int idxX = 0;
			int idxY = 0;
			int posX = 0;
			int posY = 0;

			// 인덱스와 위치 읽기
			if (file.read(reinterpret_cast<char*>(&idxX), sizeof(int)) &&
				file.read(reinterpret_cast<char*>(&idxY), sizeof(int)) &&
				file.read(reinterpret_cast<char*>(&posX), sizeof(int)) &&
				file.read(reinterpret_cast<char*>(&posY), sizeof(int))) 
			{

				// TileRenderer 및 Transform에 데이터 설정
				GetTiles()[y][x]->GetComponent<TileRenderer>()->SetIndex({ static_cast<float>(idxX), static_cast<float>(idxY) });
				GetTiles()[y][x]->GetComponent<Transform>()->SetPos({ static_cast<float>(posX), static_cast<float>(posY) });

				// 타일 렌더링
				GetTiles()[y][x]->GetComponent<TileRenderer>()->Render(app.GetBackTileHdc());
			}
			else {
				std::wcerr << L"Error: Failed to read data from file." << std::endl;
				break; // 오류 발생 시 루프 종료
			}
		}
	}
	file.close(); // 파일 닫기
}

void GE::Scene::OnEnter()
{
	//CreateTileBuffer({ 35, 20 });
}
void GE::Scene::OnExit()
{
	CollisionManager::Clear();
}


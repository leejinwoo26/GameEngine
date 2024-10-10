#include "ToolScene.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\TileRenderer.h"
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\Camera.h"
#include "..\\GameEngine_Source\\Renderer.h"
#include "..\\GameEngine_Source\\Input.h"
#include "..\\GameEngine_Source\\Application.h"
#include "Tile.h"
#include "CameraScript.h"

extern GE::Application app;

namespace GE
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE, Vector2(800, 450));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		mainCamera = cameraComp;



		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 pos = Input::GetMousePosition();
			Vector2 cameraOriginPos = Vector2(800, 450);
			Vector2 cameraPos = mainCamera->GetCameraPosition();
			Vector2 cameraDiffrent = cameraPos - cameraOriginPos;
			if (pos.x >= 0 && pos.y >= 0)
			{
				int idx_x = (pos.x + cameraPos.x) / TileRenderer::TileSize.x;
				int idx_y = (pos.y + cameraPos.y) / TileRenderer::TileSize.y;
			
				GetTiles()[idx_y][idx_x]->GetComponent<TileRenderer>()->SetIndex(TileRenderer::SelectedIndex);
				GetTiles()[idx_y][idx_x]->GetComponent<TileRenderer>()->Render(app.GetBackTileHdc());
			}

		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			Load();
		}

	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ToolScene::Destroy()
	{
		Scene::Destroy();
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 0; i < 50; i++)
		{
			Vector2 tileSize = TileRenderer::GetTileSize();
			Vector2 pos = mainCamera->CalculatePosition(Vector2(tileSize.x * i, 0));
			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 2000);
		}
		for (size_t i = 0; i < 50; i++)
		{
			Vector2 tileSize = TileRenderer::GetTileSize();
			Vector2 pos = mainCamera->CalculatePosition(Vector2(0, tileSize.y * i));
			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 2000, pos.y);
		}
	}
	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
	void ToolScene::Save()
	{
		OPENFILENAME ofn = {};
		wchar_t szFilePath[256] = {};
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");
		int tileCountX = GetTiles()[0].size();
		int tileCountY = GetTiles().size();

		fwrite(&tileCountX, sizeof(int), 1, pFile);
		fwrite(&tileCountY, sizeof(int), 1, pFile);

		for (auto& tilesX : GetTiles())
		{
			for (auto& tile : tilesX)
			{
				TileRenderer* tmr = tile->GetComponent<TileRenderer>();
				Transform* tr = tile->GetComponent<Transform>();

				Vector2 sourceIndex;
				sourceIndex = tmr->GetIndex();

				Vector2 position;
				position = tr->GetPosition();

				int x = sourceIndex.x;
				fwrite(&x, sizeof(int), 1, pFile);
				int y = sourceIndex.y;
				fwrite(&y, sizeof(int), 1, pFile);

				x = position.x;
				fwrite(&x, sizeof(int), 1, pFile);
				y = position.y;
				fwrite(&y, sizeof(int), 1, pFile);
			}
		}
		/*for (Tile* tile : mTiles)
		{
			TileRenderer* tmr = tile->GetComponent<TileRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex;
			sourceIndex = tmr->GetIndex();

			Vector2 position;
			position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, pFile);
		}*/
		fclose(pFile);

	}
	void ToolScene::Load()
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
		//while (true)
		//{
		//	int idxX = 0;
		//	int idxY = 0;
		//	int posX = 0;
		//	int posY = 0;


		//	if (fread(&idxX, sizeof(int), 1, pFile) != 1)
		//		break;
		//	if (fread(&idxY, sizeof(int), 1, pFile) != 1)
		//		break;
		//	if (fread(&posX, sizeof(int), 1, pFile) != 1)
		//		break;
		//	if (fread(&posY, sizeof(int), 1, pFile) != 1)
		//		break;


		//	Tile* tile = Instantiate<Tile>(eLayerType::TILE,Vector2(posX,posY));
		//	TileRenderer* tileRenderer = tile->AddComponent<TileRenderer>();
		//	Texture* tileTex = Resources::Find<Texture>(L"SpringFloor");
		//	tileRenderer->SetTexture(tileTex);
		//	tileRenderer->SetIndex(Vector2(idxX,idxY));

		//	//mTiles.push_back(tile);
		//}

		fclose(pFile);
	}
}
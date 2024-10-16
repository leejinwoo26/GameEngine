#include "pch.h"
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
		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE, Vector2(0, 0));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		Scene::CreateTileBuffer({ 10, 10 });

		//Scene::LoadTileMap(L"..\\Resource\\Map", L"grass");

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
			Scene::Load();
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
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT; // 파일 덮어쓰기 확인

		if (false == GetSaveFileName(&ofn))
			return;

		// std::fstream 사용하여 파일 열기
		std::fstream file(szFilePath, std::ios::out | std::ios::binary);
		if (!file.is_open()) {
			std::wcerr << L"Error: Could not open file for writing: " << szFilePath << std::endl;
			return;
		}

		int tileCountX = GetTiles()[0].size();
		int tileCountY = GetTiles().size();

		// 타일 개수 저장
		file.write(reinterpret_cast<char*>(&tileCountX), sizeof(int));
		file.write(reinterpret_cast<char*>(&tileCountY), sizeof(int));

		for (const auto& tilesX : GetTiles())
		{
			for (const auto& tile : tilesX)
			{
				TileRenderer* tmr = tile->GetComponent<TileRenderer>();
				Transform* tr = tile->GetComponent<Transform>();

				Vector2 sourceIndex = tmr->GetIndex();
				Vector2 position = tr->GetPosition();

				// 인덱스와 위치를 파일에 저장
				int x = static_cast<int>(sourceIndex.x);
				int y = static_cast<int>(sourceIndex.y);
				file.write(reinterpret_cast<char*>(&x), sizeof(int));
				file.write(reinterpret_cast<char*>(&y), sizeof(int));

				x = static_cast<int>(position.x);
				y = static_cast<int>(position.y);
				file.write(reinterpret_cast<char*>(&x), sizeof(int));
				file.write(reinterpret_cast<char*>(&y), sizeof(int));
			}
		}
		file.close(); // 파일 닫기
	}
}
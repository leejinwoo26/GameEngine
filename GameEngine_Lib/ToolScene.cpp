#include "ToolScene.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\TileRenderer.h"
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\Camera.h"
#include "..\\GameEngine_Source\\Renderer.h"
#include "..\\GameEngine_Source\\Input.h"
#include "Tile.h"



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
		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE);
		Camera* cameraComp = camera->AddComponent<Camera>();
		mainCamera = cameraComp;




		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 pos = Input::GetMousePosition();
			int idx_x = pos.x / TileRenderer::GetTileSize().x;
			int idx_y = pos.y / TileRenderer::GetTileSize().y;

			Tile* tile = Instantiate<Tile>(eLayerType::TILE);
			TileRenderer* tileRenderer = tile->AddComponent<TileRenderer>();
			Texture* tileTex = Resources::Find<Texture>(L"SpringFloor");
			tileRenderer->SetTexture(tileTex);
			tile->SetPos(idx_x, idx_y);
		}
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
			MoveToEx(hdc, tileSize.x * i, 0, NULL);
			LineTo(hdc, tileSize.x * i, 2000);
		}
		for (size_t i = 0; i < 50; i++)
		{
			Vector2 tileSize = TileRenderer::GetTileSize();
			MoveToEx(hdc, 0 , tileSize.y * i, NULL);
			LineTo(hdc, 2000, tileSize.y * i);
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
}
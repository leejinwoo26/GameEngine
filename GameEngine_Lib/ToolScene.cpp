#include "ToolScene.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\TileRenderer.h"
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\Camera.h"
#include "..\\GameEngine_Source\\Renderer.h"
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

		Tile* tile = Instantiate<Tile>(eLayerType::TILE);
		TileRenderer* tileRenderer = tile->AddComponent<TileRenderer>();
		Transform* tileTr = tile->AddComponent<Transform>();
		Texture* tileTex = Resources::Find<Texture>(L"SpringFloor");
		tileRenderer->SetTexture(tileTex);

		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();
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
			MoveToEx(hdc, (16*3) * i, 0, NULL);
			LineTo(hdc, (16*3) * i, 2000);
		}
		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(hdc, 0 , (16 * 3) * i, NULL);
			LineTo(hdc, 2000, (16 * 3) * i);
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
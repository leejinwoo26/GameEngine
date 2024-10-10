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
void GE::Scene::CreateTileBuffer(Gdiplus::Size tileCount)
{
	mTileCount = tileCount;

	/*mSize = { tileCount.Width * INT(TileRenderer::TileSize.x),
		tileCount.Height * INT(TileRenderer::TileSize.y) };*/
	mSize = {1680, 960};
	app.ChangeTileBuffer(mSize);

	mTiles.resize(tileCount.Height);

	for (size_t y= 0; y < tileCount.Height; y++)
	{
		mTiles[y].resize(tileCount.Width);
		for (size_t x = 0; x < tileCount.Width; x++)
		{
			Tile* tile = new Tile;
			TileRenderer* tileRenderer = tile->AddComponent<TileRenderer>();
			Texture* tileTex = Resources::Find<Texture>(L"SpringFloor");
			tileRenderer->SetTexture(tileTex);
			tileRenderer->SetIndex(Vector2(10.f, 10.f));
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

void GE::Scene::OnEnter()
{
	CreateTileBuffer({ 35, 20 });
}
void GE::Scene::OnExit()
{
	CollisionManager::Clear();
}


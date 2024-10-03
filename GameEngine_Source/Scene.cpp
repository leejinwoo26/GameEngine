#include "Scene.h"
#include "CollisionManager.h"

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

}
void GE::Scene::OnExit()
{
	CollisionManager::Clear();
}


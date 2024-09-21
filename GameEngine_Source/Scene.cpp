#include "Scene.h"

GE::Scene::Scene()
{
}

GE::Scene::~Scene()
{
}

void GE::Scene::Initialize()
{
	for (GameObject* gameObj : mGameObjs)
	{
		gameObj->Initialize();
	}
}

void GE::Scene::Update()
{
	for (GameObject* gameObj : mGameObjs)
	{
		gameObj->Update();
	}
}

void GE::Scene::LateUpdate()
{
	for (GameObject* gameObj : mGameObjs)
	{
		gameObj->LateUpdate();
	}
}

void GE::Scene::Render(HDC hdc)
{
	for (GameObject* gameObj : mGameObjs)
	{
		gameObj->Render(hdc);
	}
}
void GE::Scene::AddGameObject(GameObject* gameObj)
{
}


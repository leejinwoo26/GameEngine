#include "Layer.h"
namespace GE
{
	Layer::Layer() : mGameObjs{}
	{

	}
	Layer::~Layer()
	{
		for (auto& iter : mGameObjs)
		{
			delete iter;
			iter = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjs)
		{
			if (gameObj == nullptr)
				continue;
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjs)
		{
			if (gameObj == nullptr)
				continue;
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjs)
		{
			if (gameObj == nullptr)
				continue;
			gameObj->LateUpdate();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjs)
		{
			if (gameObj == nullptr)
				continue;
			gameObj->Render(hdc);
		}
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;
		mGameObjs.push_back(gameObj);
	}

}
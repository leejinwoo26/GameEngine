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
			if (gameObj->GetState() == GameObject::eState::DEAD
				|| gameObj->GetState() == GameObject::eState::PAUSE)
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
			if (gameObj->GetState() == GameObject::eState::DEAD
				|| gameObj->GetState() == GameObject::eState::PAUSE)
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
			if (gameObj->GetState() == GameObject::eState::DEAD
				|| gameObj->GetState() == GameObject::eState::PAUSE)
				continue;
			gameObj->Render(hdc);
		}
	}
	void Layer::Destroy()
	{
		for (auto iter = mGameObjs.begin(); iter != mGameObjs.end();)
		{
			if ((*iter)->GetState() == GameObject::eState::DEAD)
			{
				GameObject* gameObj = (*iter);
				iter = mGameObjs.erase(iter);
				
				mDestroyObjs.push_back(gameObj);
				continue;
			}
			iter++;
		}

		for (auto& iter : mDestroyObjs)
		{
			delete iter;
			iter = nullptr;
		}
	}	
	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;
		mGameObjs.push_back(gameObj);
	}
}
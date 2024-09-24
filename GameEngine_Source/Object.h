#pragma once
#include "CommonInclude.h"
#include "GameObject.h"
#include "Layer.h"
#include "SceneManager.h"
#include "Transform.h"

namespace GE
{
	template <typename T>
	static T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);
		return gameObj;
	}

	template <typename T>
	static T* Instantiate(eLayerType type, Vector2 pos)
	{
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);

		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPos(pos);

		return gameObj;
	}
}
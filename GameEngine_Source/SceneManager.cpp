#include "SceneManager.h"
namespace GE
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	SceneManager::SceneManager()
	{
	}
	SceneManager::~SceneManager()
	{
	}
	void SceneManager::Initialize()
	{
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
	void SceneManager::Release()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

}
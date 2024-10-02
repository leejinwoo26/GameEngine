#include "SceneManager.h"
#include "DontDestroyOnLoad.h"
namespace GE
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	SceneManager::SceneManager()
	{
	}
	SceneManager::~SceneManager()
	{
	}
	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad =  CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}
	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
		mDontDestroyOnLoad->Render(hdc);
	}
	void SceneManager::Release()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
	}
}
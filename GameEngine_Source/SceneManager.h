#pragma once
#include "Scene.h"

namespace GE
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			T* scene = new T;
			scene->SetName(name);
			mActiveScene = scene;
			scene->Initialize();

			mScenes.insert(std::make_pair(name, scene));

			return scene;	
		}
		static Scene* LoadScene(const std::wstring& name)
		{
			if (mActiveScene)
				mActiveScene->OnExit();
			auto iter = mScenes.find(name);
			if (iter == mScenes.end())
				return nullptr;
			mActiveScene = iter->second;
			mActiveScene->OnEnter();
			return iter->second;
		}


		__forceinline static Scene* GetActiveScene() { return mActiveScene; }
		__forceinline static Scene* GetDontDestroyScene() { return mDontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjects(eLayerType layer);

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();

	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static Scene* mDontDestroyOnLoad;
	};
}

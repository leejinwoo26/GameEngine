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
			scene->Initialize();
			mActiveScene = scene;

			mScenes.insert(std::make_pair(name, scene));

			return scene;	
		}

		static Scene* LoadScene(const std::wstring& name)
		{
			auto iter = mScenes.find(name);
			if (iter == mScenes.end())
				return nullptr;
			mActiveScene = iter->second;
			return iter->second;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
	};
}

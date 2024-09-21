#pragma once
#include "..\\GameEngine_Source\\SceneManager.h"
#include "PlayScene.h"

namespace GE
{
	void LoadScenes(const std::wstring& name)
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");


		SceneManager::LoadScene(L"PlayScene");
	}
}


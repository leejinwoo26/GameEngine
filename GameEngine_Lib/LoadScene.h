#pragma once
#include "..\\GameEngine_Source\\SceneManager.h"
#include "PlayScene.h"	

namespace GE
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");


		SceneManager::LoadScene(L"PlayScene");
	}
}


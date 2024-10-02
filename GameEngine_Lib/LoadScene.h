#pragma once
#include "..\\GameEngine_Source\\SceneManager.h"
#include "PlayScene.h"	
#include "ToolScene.h"

namespace GE
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");


		SceneManager::LoadScene(L"ToolScene");
	}
}


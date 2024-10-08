#pragma once
#include "..\\GameEngine_Source\\SceneManager.h"
#include "PlayScene.h"	
#include "ToolScene.h"
#include "CullingScene.h"

namespace GE
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");
		//SceneManager::CreateScene<CullingScene>(L"CullingScene");


		SceneManager::LoadScene(L"PlayScene");
	}
}


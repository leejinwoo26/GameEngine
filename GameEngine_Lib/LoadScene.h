#pragma once
#include "..\\GameEngine_Source\\SceneManager.h"
#include "PlayScene.h"	
#include "ToolScene.h"
#include "CullingScene.h"
#include "AnimationScene.h"
#include "ParticleScene.h"

namespace GE
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");
		//SceneManager::CreateScene<AnimationScene>(L"AnimationScene");
		SceneManager::CreateScene<ParticleScene>(L"ParticleScene");
		//SceneManager::CreateScene<CullingScene>(L"CullingScene");


		SceneManager::LoadScene(L"ParticleScene");
	}
}


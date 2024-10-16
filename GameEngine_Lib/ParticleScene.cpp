#include "pch.h"
#include "ParticleScene.h"
#include "..\\GameEngine_Source\\Application.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\ParticleSystem.h"
#include "..\\GameEngine_Source\\Particle.h"



extern GE::Application app;

namespace GE
{

	ParticleScene::ParticleScene()
	{
	}
	ParticleScene::~ParticleScene()
	{
	}
	void ParticleScene::Initialize()
	{
		Scene::Initialize();
		GameObject* player = Instantiate<GameObject>(eLayerType::PLAYER,Vector2(800,500));
		ParticleSystem* playerPS = player->AddComponent<ParticleSystem>();

	}
	void ParticleScene::Update()
	{
		Scene::Update();
	}
	void ParticleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ParticleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void ParticleScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ParticleScene::OnExit()
	{
		Scene::OnExit();
	}
}
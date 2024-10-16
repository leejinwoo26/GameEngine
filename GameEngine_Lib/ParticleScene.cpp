#include "pch.h"
#include "ParticleScene.h"
#include "..\\GameEngine_Source\\Application.h"
#include "..\\GameEngine_Source\\Particle.h"
#include "..\\GameEngine_Source\\Object.h"


extern GE::Application app;

namespace GE
{
	HDC ParticleScene::particleHdc = nullptr;

	ParticleScene::ParticleScene()
	{
	}
	ParticleScene::~ParticleScene()
	{
	}
	void ParticleScene::Initialize()
	{
		Scene::Initialize();
		Instantiate<Particle>(eLayerType::PARTICLE);
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
#include "PlayScene.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Object.h"
#include "Resources.h"
#include "PlayerScript.h"
#include "Camera.h"
#include "Renderer.h"
#include "Animator.h"

namespace GE
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE);
		Camera* cameraComp  = camera->AddComponent<Camera>();
		mainCamera = cameraComp;

		//camera->AddComponent<PlayerScript>();

		bg = Instantiate<Player>(eLayerType::PLAYER);

		SpriteRenderer* sr
			= bg->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");

		//PlayerScript* ps = bg->AddComponent<PlayerScript>();

		Texture* bgTex = Resources::Find<Texture>(L"BG");
		sr->SetTexture(bgTex);

		Animator* animator = bg->AddComponent<Animator>();


		animator->CreateAnimation(L"CatWalk", bgTex,
			Vector2(0.f, 0.f), Vector2(30.f, 30.f), Vector2(0.f, 0.f), 4, 0.1f);

	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
	}
}
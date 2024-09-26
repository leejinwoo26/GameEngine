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
		//mainCamera = cameraComp;

		//camera->AddComponent<PlayerScript>();

		bg = Instantiate<Player>(eLayerType::PLAYER);

		/*SpriteRenderer* sr
			= bg->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");*/


		Transform* playerTr = bg->GetComponent<Transform>();
		playerTr->SetScale(Vector2(6.f, 6.f));

		PlayerScript* ps = bg->AddComponent<PlayerScript>();

		Texture* bgTex = Resources::Find<Texture>(L"Cat");

		//sr->SetTexture(bgTex);

		Animator* animator = bg->AddComponent<Animator>();
		animator->CreateAnimation(L"DownWalk", bgTex
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2(0.f,0.f), 4, 0.1f);
		animator->CreateAnimation(L"RightWalk", bgTex
			, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		animator->CreateAnimation(L"UpWalk", bgTex
			, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		animator->CreateAnimation(L"LeftWalk", bgTex
			, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		animator->CreateAnimation(L"SitDown", bgTex
			, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		animator->CreateAnimation(L"Grooming", bgTex
			, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);

		animator->PlayAnimation(L"SitDown", false);

		Scene::Initialize();
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
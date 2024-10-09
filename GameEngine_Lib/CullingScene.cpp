#include "CullingScene.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Object.h"
#include "Resources.h"
#include "CameraScript.h"
#include "Camera.h"
#include "Renderer.h"
#include "Animator.h"
#include "Texture.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
//#include "Collider.h"
#include "CollisionManager.h"
#include "RigidBody.h"
#include "AudioClip.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "AnimationMananger.h"
#include "PlayerScript.h"


namespace GE
{
	CullingScene::CullingScene()
	{
	}
	CullingScene::~CullingScene()
	{
	}
	void CullingScene::Initialize()
	{
		AnimationMananger::Initialize();

		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE);
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		GameObject* back = Instantiate<GameObject>(eLayerType::NONE,Vector2(0,0));
		//back->AddComponent<CameraScript>();
		SpriteRenderer* backSr = back->AddComponent<SpriteRenderer>();
		backSr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
		Scene::Initialize();


		GameObject* Player = Instantiate<GameObject>(eLayerType::PLAYER, Vector2(500, 500));
		Animator* playerAnimator = Player->AddComponent<Animator>();
		Texture* boyTex = Resources::Find<Texture>(L"Boy_Right");
		Player->AddComponent<PlayerScript>();
		GameObject* PlayerHair = Instantiate<GameObject>(eLayerType::ANIMAL, Vector2(450, 425));
		Animator* hairAnimator = PlayerHair->AddComponent<Animator>();
		Texture* hairTex = Resources::Find<Texture>(L"cloth");
		PlayerHair->SetTarget(Player);

		playerAnimator->CreateAnimation(L"Idle_Right", boyTex, 0.2);
		playerAnimator->CreateAnimation(L"Walk_Right", boyTex, 0.2);
		playerAnimator->CreateAnimation(L"Run_Right", boyTex, 0.15);
		playerAnimator->CreateAnimation(L"Flying_Right", boyTex, 0.5);
		playerAnimator->CreateAnimation(L"Land_Right", boyTex, 0.5);
		playerAnimator->CreateAnimation(L"Jump_Right", boyTex, 0.5);
		playerAnimator->CreateAnimation(L"A_Idle_Right", boyTex, 0.2);
		playerAnimator->CreateAnimation(L"N_Attack_H_Right", boyTex, 0.2);
		playerAnimator->CreateAnimation(L"N_Attack_V_Right", boyTex, 0.2);
		playerAnimator->CreateAnimation(L"N_Attack_St_Right", boyTex, 0.5);
		playerAnimator->CreateAnimation(L"Defence_Right", boyTex, 1);
		playerAnimator->CreateAnimation(L"Hitted_Right", boyTex, 1);
		playerAnimator->CreateAnimation(L"HandStorm_Right", boyTex, 0.18);
		playerAnimator->CreateAnimation(L"EnergCharge_Right", boyTex, 1);
		playerAnimator->CreateAnimation(L"Breathing_Right", boyTex, 1);
		playerAnimator->CreateAnimation(L"Dead_Right", boyTex, 1);
		playerAnimator->CreateAnimation(L"Anger_Right", boyTex, 1);

		hairAnimator->CreateAnimation(L"cloth", hairTex, 0.2);
		hairAnimator->PlayAnimation(L"cloth");
		
		playerAnimator->PlayAnimation(L"Idle_Right");


		cameraComp->SetTarget(Player);

	}
	void CullingScene::Update()
	{
		Scene::Update();
	}
	void CullingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CullingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void CullingScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void CullingScene::OnExit()
	{
		Scene::OnExit();
	}
}

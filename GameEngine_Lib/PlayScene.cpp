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
#include "Texture.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
//#include "Collider.h"
#include "CollisionManager.h"
#include "RigidBody.h"
#include "AudioClip.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "PixelCollider.h"
#include "AnimationMananger.h"


namespace GE
{
	
	PlayScene::PlayScene() : bgTex(nullptr) , rot(0.f)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		AnimationMananger::Initialize();

		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE);
		Camera* cameraComp  = camera->AddComponent<Camera>();
		mainCamera = cameraComp;

		GameObject* otherCat = Instantiate<GameObject>(eLayerType::ANIMAL,Vector2(600, 500));
		//BoxCollider2D* otherCatCol = otherCat->AddComponent<BoxCollider2D>();
		CircleCollider2D* otherCatCol = otherCat->AddComponent<CircleCollider2D>();
		Transform* otherCatTr = otherCat->GetComponent<Transform>();
		otherCatTr->SetScale(Vector2(2, 2));
		otherCatCol->SetOffset(Vector2(17.5f, 27.5));
		otherCatCol->SetRadius(50);
		//otherCatCol->SetBoxCollsionSize(Vector2(35, 40));
		AudioSource* as = otherCat->AddComponent<AudioSource>();
		//camera->AddComponent<PlayerScript>();

		bg = Instantiate<Player>(eLayerType::PLAYER,Vector2(800,500));
		Rigidbody* playerRigid = bg->AddComponent<Rigidbody>();
		playerRigid->SetGround(true);
		cameraComp->SetTarget(bg);

		bg->AddComponent<AudioListener>();
		PixelCollider* bgPixelCol = bg->AddComponent<PixelCollider>();


		playerTr = bg->GetComponent<Transform>();
		playerTr->SetScale(Vector2(2.f, 2.f));

		//BoxCollider2D* boxCol = bg->AddComponent<BoxCollider2D>();
		/*CircleCollider2D* boxCol = bg->AddComponent<CircleCollider2D>();
		boxCol->SetOffset(Vector2(17.5, 27.5));
		boxCol->SetRadius(50);*/
		//boxCol->SetBoxCollsionSize(Vector2(160, 40));

		PlayerScript* ps = bg->AddComponent<PlayerScript>();
		
		bgTex = Resources::Find<Texture>(L"Cat");
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


		Animator* otheranimator = otherCat->AddComponent<Animator>();
		otheranimator->CreateAnimation(L"DownWalk", bgTex
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		otheranimator->CreateAnimation(L"RightWalk", bgTex
			, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		otheranimator->CreateAnimation(L"UpWalk", bgTex
			, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		otheranimator->CreateAnimation(L"LeftWalk", bgTex
			, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		otheranimator->CreateAnimation(L"SitDown", bgTex
			, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		otheranimator->CreateAnimation(L"Grooming", bgTex
			, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2(0.f, 0.f), 4, 0.1f);
		
		otheranimator->PlayAnimation(L"SitDown", false);

		//animator->GetCompleteEvent(L"SitDown") = std::bind(&PlayerScript::Attack, ps);

		AudioClip* ac = Resources::Load<AudioClip>(L"BGsound", L"..\\Resource\\Sound\\smw_bonus_game_end.wav");
		as->SetClip(ac);
		//as->Play();


		GameObject* back = Instantiate<GameObject>(eLayerType::NONE, Vector2(0, 0));
		SpriteRenderer* backSr = back->AddComponent<SpriteRenderer>();
		backSr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
		bgPixelCol->SetPixelMap(Resources::Find<Texture>(L"SpringFloor"));

		GameObject* GhostPlayer = Instantiate<GameObject>(eLayerType::NONE, Vector2(900, 500));
		Animator* GhostAnimator = GhostPlayer->AddComponent<Animator>();

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
		CollisionManager::CollisionLayerCheck(eLayerType::PLAYER, eLayerType::ANIMAL, true);
	}
	void PlayScene::OnExit()
	{
	}
}
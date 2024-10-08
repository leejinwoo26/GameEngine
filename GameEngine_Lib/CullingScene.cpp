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
		GameObject* camera = Instantiate<GameObject>(eLayerType::NONE);
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		cameraComp->SetTarget(camera);

		GameObject* back = Instantiate<GameObject>(eLayerType::NONE,Vector2(0,0));
		SpriteRenderer* backSr = back->AddComponent<SpriteRenderer>();
		backSr->SetTexture(Resources::Find<Texture>(L"PixelMap"));
		Scene::Initialize();
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

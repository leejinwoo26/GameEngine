#include "pch.h"
#include "PlayerScript.h"
#include "..\\GameEngine_Source\\Input.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\GETime.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\Animator.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\Renderer.h"
#include "..\\GameEngine_Source\\RigidBody.h"
#include "..\\GameEngine_Source\\UiManager.h"

namespace GE
{
	PlayerScript::PlayerScript():
		mState(PlayerScript::eState::SitDown), 
		mAnimator(nullptr),
		mDeathTime(0)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
	
		if (Input::GetKey(eKeyCode::A))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= 500 * Time::DeltaTime();
			tr->SetPos(pos);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 500 * Time::DeltaTime();
			tr->SetPos(pos);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.y -= 500 * Time::DeltaTime();
			tr->SetPos(pos);
		}
		if (Input::GetKey(eKeyCode::S))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.y += 500 * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hdc)
	{
	}

	void PlayerScript::Attack()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
	}

	void PlayerScript::sitDown()
	{
		if (Input::GetKey(eKeyCode::D))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKey(eKeyCode::A))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"LeftWalk");
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"UpWalk");
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mState = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"DownWalk");
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			mainCamera->SetTarget(nullptr);
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mainCamera->SetTarget(this->GetOwner());
		}
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			UiManager::Push(eUIType::HPBAR);
		}
	}


	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (Input::GetKey(eKeyCode::D))
		{
			//pos.x += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(200, 0));
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//pos.x -= 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(-200, 0));
		}
		if (Input::GetKey(eKeyCode::W))
		{
			//pos.y -= 100.0f * Time::DeltaTime();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500;
			rb->SetVelocity(velocity);
			//rb->SetGround(true);
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//pos.y += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(0, 200));
		}

		//tr->SetPos(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = PlayerScript::eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
}
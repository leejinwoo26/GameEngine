#include "PlayerScript.h"
#include "..\\GameEngine_Source\\Input.h"
#include "..\\GameEngine_Source\\Transform.h"
#include "..\\GameEngine_Source\\Time.h"
#include "..\\GameEngine_Source\\GameObject.h"
#include "..\\GameEngine_Source\\Animator.h"
#include "..\\GameEngine_Source\\Object.h"
#include "..\\GameEngine_Source\\Renderer.h"

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
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		/*mDeathTime += Time::DeltaTime();

		if (mDeathTime > 1.f)
		{
			ObjectDeath(this->GetOwner());
		}*/

		switch (mState)
		{
		case PlayerScript::eState::SitDown:
			sitDown();
			break;
		case PlayerScript::eState::Walk:
			move();
			break;
		case PlayerScript::eState::Sleep:
			break;
		case PlayerScript::eState::Attack:
			Attack();
			break;
		default:
			break;
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
		int a = 0;
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
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 a = Input::GetMousePosition();
			int b = 0;
		}


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
	}


	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = PlayerScript::eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
}
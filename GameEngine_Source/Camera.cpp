#include "pch.h"

#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "GETime.h"
#include "Debug_Text.h"
#include "SceneManager.h"
extern GE::Application app;

namespace GE
{
	Camera::Camera():
		Component(eComponentType::CAMERA),
		mDistance(Vector2(0.f,0.f)),
		mResolution(Vector2(0.f,0.f)),
		mLookPosition(Vector2(1.f,1.f)),
		mTarget(nullptr)
	{
	}
	Camera::~Camera()
	{

	}
	void Camera::Initialize()
	{
		mResolution.x = app.GetWidth();
		mResolution.y = app.GetHeight();
	}
	void Camera::Update()
	{
		if (mTarget)
		{
			if (mTarget->GetState() == GameObject::eState::ACTIVE 
				|| mTarget->GetState() == GameObject::eState::PAUSE)
			{
				Transform* tr = mTarget->GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				if (SceneManager::GetActiveScene()->GetName() == L"AnimationScene")
				{
					mLookPosition = pos;
				}
				else
				{
					mLookPosition = Vector2::ExponentialLerp(mLookPosition, pos - (mResolution / 2.f), Time::DeltaTime(), 3.5f);
				}
			}
		}
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}

		GetOwner()->GetComponent<Transform>()->SetPos(mLookPosition);
		mDistance = mLookPosition;// -(mResolution / 2.f);
	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hdc)
	{
		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = cameraTr->GetPosition();

	}
	Vector2 Camera::GetCameraPosition()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		return pos;
	}
}
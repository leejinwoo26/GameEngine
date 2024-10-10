#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Time.h"
#include "Debug_Text.h"

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
				mLookPosition = Vector2::ExponentialLerp(mLookPosition, tr->GetPosition() - (mResolution / 2.f), Time::DeltaTime(), 3.5f);
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
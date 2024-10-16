#include "pch.h"

#include "RigidBody.h"
#include "GETime.h"
#include "Transform.h"
#include "GameObject.h"

namespace GE
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::RIGIDBODY)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(100.0f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mLimitVelocity(Vector2(200,500))
		, mGravity(Vector2(0,500))
		, mAccelation(Vector2::Zero)
	{
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// f(��) = m(����) x a(���ӵ�)
		// a = f / m;
		mAccelation = mForce / mMass;
		// �ӵ��� ���ӵ��� ���Ѵ�.
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			Vector2 gravity = mGravity;
			gravity.normalize();
			float dot = Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = Vector2::Dot(mVelocity, gravity);
		gravity = gravity * dot;


		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitVelocity.x;
		}

		mVelocity = gravity + sideVelocity;
		
		
		if (!(mVelocity == Vector2::Zero))
		{
			//�ӵ��� �ݴ�������� ������ �ۿ�
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();
			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (mVelocity.length() <= friction.length())
			{
				// ����
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPos(pos);

		mForce.clear();
	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render(HDC hdc)
	{
	/*	wchar_t str[50] = L"";

		swprintf_s(str, 50, L"Velocity_X : %f", mVelocity.x);
		int len = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 100, str, len);

		swprintf_s(str, 50, L"Velocity_Y : %f", mVelocity.y);
		len = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 150, str, len);

		swprintf_s(str, 50, L"mAccelation : %f , %f", mAccelation.x, mAccelation.y);
		len = wcsnlen_s(str, 50);
		TextOut(hdc, 0, 200, str, len);*/
	}
}
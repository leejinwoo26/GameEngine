#include "pch.h"
#include "PixelCollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "Debug_Text.h"
#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Animator.h"
#include "Animation.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "Debug_Text.h"

extern GE::Application app;

namespace GE
{
	PixelCollider::PixelCollider() :
		mPixelCollsions(0),
		mPixelMap(nullptr)
	{
	}
	PixelCollider::~PixelCollider()
	{
	}
	void PixelCollider::Initialize()
	{
		Collider::SetState(eCollisionState::Pixel2D);
	}
	void PixelCollider::Update()
	{
		PixelUpdate();
	}
	void PixelCollider::LateUpdate()
	{
	}
	void PixelCollider::Render(HDC hdc)
	{
		Print_Text(hdc, L"mPixelCollsions[UP]", (int)mPixelCollsions[(UINT)ePixelColDirection::UP], Vector2(0, 500));
		Print_Text(hdc, L"mPixelCollsions[Down]", (int)mPixelCollsions[(UINT)ePixelColDirection::DOWN], Vector2(0, 550));
		Print_Text(hdc, L"mPixelCollsions[Left]", (int)mPixelCollsions[(UINT)ePixelColDirection::LEFT], Vector2(0, 600));
		Print_Text(hdc, L"mPixelCollsions[Right]", (int)mPixelCollsions[(UINT)ePixelColDirection::RIGHT], Vector2(0, 650));

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos =  tr->GetPosition();
		Animator* activeAnimator = GetOwner()->GetComponent<Animator>();
		Animation* activeAnimation = activeAnimator->GetActiveAnimation();

		std::vector<Animation::Sprite> activeSprite = activeAnimation->GetSprite();
		int idx = activeAnimation->GetIndex();
		Vector2 Size = activeSprite[idx].Size;

		if (mainCamera->GetTarget() == GetOwner()) //카메라가 게임오브젝트 타겟팅일때
		{
			Vector2 offset = pos - Vector2(app.GetWidth()/2, app.GetHeight()/2);
			pos -= offset;
		}

		Rectangle(hdc
			, pos.x + (Size.x / 2) - 2.5
			, pos.y + -5
			, pos.x + (Size.x / 2) + 2.5
			, pos.y
		);//위
		Rectangle(hdc
			, pos.x -2.5
			, pos.y + (Size.y / 2)
			, pos.x +2.5
			, pos.y + (Size.y / 2) + 5
		);//왼
		Rectangle(hdc
			, pos.x + Size.x - 2.5
			, pos.y + (Size.y / 2)
			, pos.x + Size.x + 2.5
			, pos.y + (Size.y / 2) + 5
		);//오
		Rectangle(hdc
			, pos.x + (Size.x / 2) - 2.5
			, pos.y + Size.y + 15
			, pos.x + (Size.x / 2) + 2.5
			, pos.y + Size.y + 20
		);//아래
	}
	void PixelCollider::PixelUpdate()
	{
		if (mPixelMap == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* activeAnimator = GetOwner()->GetComponent<Animator>();
		if (activeAnimator == nullptr)
			return;
		Animation* activeAnimation = activeAnimator->GetActiveAnimation();
		if (activeAnimation == nullptr)
			return;

		std::vector<Animation::Sprite> activeSprite = activeAnimation->GetSprite();
		int idx = activeAnimation->GetIndex();
		Vector2 Size = activeSprite[idx].Size;

		if (mPixelMap->GetPixel(pos.x + (Size.x / 2), pos.y - 5) == MAGENTA)
		{
			mPixelCollsions[(UINT)ePixelColDirection::UP] = 1;
		}
		else
		{
			mPixelCollsions[(UINT)ePixelColDirection::UP] = 0;
		}
		if (mPixelMap->GetPixel(pos.x - 2.5, pos.y + (Size.y / 2)) == MAGENTA)
		{
			mPixelCollsions[(UINT)ePixelColDirection::LEFT] = 1;
		}
		else
		{
			mPixelCollsions[(UINT)ePixelColDirection::LEFT] = 0;
		}
		if (mPixelMap->GetPixel(pos.x + Size.x + 2.5, pos.y + (Size.y / 2)) == MAGENTA)
		{
			mPixelCollsions[(UINT)ePixelColDirection::RIGHT] = 1;
		}
		else
		{
			mPixelCollsions[(UINT)ePixelColDirection::RIGHT] = 0;
		}
		if (mPixelMap->GetPixel(pos.x + (Size.x / 2), pos.y + Size.y + 2.5) == MAGENTA)
		{
			mPixelCollsions[(UINT)ePixelColDirection::DOWN] = 1;
		}
		else
		{
			mPixelCollsions[(UINT)ePixelColDirection::DOWN] = 0;
		}
	}
}
#include "Animation.h"
#include "Animator.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"


namespace GE
{
	Animation::Animation():
		Resource(eResourceType::ANIMATION),
		mAnimator(nullptr),
		mTexture(nullptr),
		mAnimationSheet{},
		mIndex(-1),
		mTime(0.f),
		mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::CreateAnimation(const std::wstring& name, Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLeghth, float duration)
	{
		mTexture = spriteSheet;

		for (size_t i = 0; i < spriteLeghth; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.Size = size;
			sprite.Offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0;
			if (mIndex < mAnimationSheet.size() - 1)
			{
				mIndex++;
			}
			else
			{
				mbComplete = true;
			}
		}

	}
	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mainCamera)
		{
			pos = mainCamera->CalculatePosition(pos);
		}

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();

		AlphaBlend(hdc
			, pos.x, pos.y
			, sprite.Size.x 
			, sprite.Size.y
			, imgHdc
			, sprite.leftTop.x
			, sprite.leftTop.y	
			, sprite.Size.x
			, sprite.Size.y
			, func);
	}

	void Animation::Reset()
	{
		mTime = 0;
		mIndex = 0;
		mbComplete = false;
	}
}
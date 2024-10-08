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

	void Animation::CreateAnimation(const std::wstring& name, Texture* spriteSheet,
		Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLeghth, float duration)
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
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (mainCamera->GetTarget())
			pos = mainCamera->CalculatePosition(pos);



		Sprite sprite = mAnimationSheet[mIndex];
		Texture::eTextureType textureType = mTexture->GetTextureType();

		if (textureType == Texture::eTextureType::BMP)
		{
			HDC imgHdc = mTexture->GetHdc();
			if (mTexture->GetAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x - ((sprite.Size.x /** scale.x*/) / 2.0f) + sprite.Offset.x
					, pos.y - ((sprite.Size.y /** scale.y*/) / 2.0f) + sprite.Offset.y
					, sprite.Size.x * scale.x
					, sprite.Size.y * scale.y
					, imgHdc
					, sprite.leftTop.x
					, sprite.leftTop.y
					, sprite.Size.x
					, sprite.Size.y
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x - ((sprite.Size.x /** scale.x*/) / 2.0f) + sprite.Offset.x
					, pos.y - ((sprite.Size.y /** scale.y*/) / 2.0f) + sprite.Offset.y
					, sprite.Size.x * scale.x
					, sprite.Size.y * scale.y
					, imgHdc
					, sprite.leftTop.x
					, sprite.leftTop.y
					, sprite.Size.x
					, sprite.Size.y
					, RGB(255, 0, 255));
			}
			//Rectangle(hdc, pos.x, pos.y, pos.x + 10, pos.y + 10);
		}
		else if (textureType == Texture::eTextureType::PNG)
		{
			Gdiplus::ImageAttributes imgAtt = {};
			// 투명화 시킬 픽셀의 색 범위
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));
			Gdiplus::Graphics graphics(hdc);

			graphics.RotateTransform(rot);

			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					pos.x - ((sprite.Size.x /** scale.x*/) / 2.0f)
					, pos.y - ((sprite.Size.y /** scale.y*/) / 2.0f)
					, sprite.Size.x * scale.x
					, sprite.Size.y * scale.y
				)
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.Size.x
				, sprite.Size.y
				, Gdiplus::UnitPixel
				, /*&imgAtt*/nullptr
			);
		}
		
	}

	void Animation::Reset()
	{
		mTime = 0;
		mIndex = 0;
		mbComplete = false;
	}
}
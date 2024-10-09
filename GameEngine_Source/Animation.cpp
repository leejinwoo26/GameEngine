#include "Animation.h"
#include "Animator.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "AnimationMananger.h"


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
	void Animation::CreateAnimation(const std::wstring& name, Texture* spriteSheet, float duration)
	{
		mTexture = spriteSheet;

		auto animSprites = AnimationMananger::GetAnimSprites();

		auto iter = animSprites.find(name);

		if (iter->second.size()<=0)
			return;

		for (size_t i = 0; i < iter->second.size(); i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = iter->second[i].LeftTop.x;
			sprite.leftTop.y = iter->second[i].LeftTop.y;
			sprite.Size = iter->second[i].SpriteSize;
			sprite.Offset = iter->second[i].Offset;
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
				//HDC memDC = CreateCompatibleDC(hdc);

				//HBITMAP memBitmap = CreateCompatibleBitmap(hdc, sprite.Size.x * scale.x, sprite.Size.y * scale.y);
				//SelectObject(memDC, memBitmap);
				//StretchBlt(memDC,
				//	0, 0,  // 메모리 DC의 시작 위치
				//	sprite.Size.x * scale.x,   // 메모리 DC에 출력할 크기
				//	sprite.Size.y * scale.y,
				//	imgHdc,
				//	sprite.leftTop.x + sprite.Size.x - 1,  // 원본 이미지의 오른쪽 끝에서 시작
				//	sprite.leftTop.y,
				//	-sprite.Size.x,   // 너비를 음수로 설정하여 반전
				//	sprite.Size.y,
				//	SRCCOPY);

				//TransparentBlt(hdc,
				//	pos.x - (sprite.Size.x / 2.0f) + sprite.Offset.x,
				//	pos.y - (sprite.Size.y / 2.0f) + sprite.Offset.y,
				//	sprite.Size.x * scale.x,
				//	sprite.Size.y * scale.y,
				//	memDC,
				//	0, 0,  // 메모리 DC의 시작 위치
				//	sprite.Size.x * scale.x,
				//	sprite.Size.y * scale.y,
				//	BLACK); // 투명색으로 처리할 색상
				//DeleteObject(memBitmap);
				//DeleteDC(memDC);

				TransparentBlt(hdc
					, pos.x - (sprite.Size.x / 2.0f) + sprite.Offset.x
					, pos.y - (sprite.Size.y / 2.0f) + sprite.Offset.y
					, sprite.Size.x * scale.x
					, sprite.Size.y * scale.y
					, imgHdc
					, sprite.leftTop.x 
					, sprite.leftTop.y
					, sprite.Size.x
					, sprite.Size.y
					, BLACK);


			}
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
#include "pch.h"
#include "TileRenderer.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Debug_Text.h"

namespace GE
{
	Vector2 TileRenderer::TileSize = Vector2(1,1);
	Vector2 TileRenderer::OriginTileSize = Vector2::One;
	Vector2 TileRenderer::SelectedIndex = Vector2(-1.0f, -1.0f);

	TileRenderer::TileRenderer()
		: mSize(Vector2(3.f, 3.f))
		, mTexture(nullptr)
		, Component(eComponentType::SPRITERENDERER)
		, mIndex(Vector2(0,0))
		, mTileSize(Vector2(16.f,16.f))
	{
		TileSize = mTileSize * mSize;
		OriginTileSize = mTileSize;
	}
	TileRenderer::~TileRenderer()
	{
	}
	void TileRenderer::Initialize()
	{
	}
	void TileRenderer::Update()
	{
	}
	void TileRenderer::LateUpdate()
	{
	}
	void TileRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		HDC texHdc = mTexture->GetHdc();

		if (mainCamera->GetTarget() != nullptr)
		{
			pos = mainCamera->CalculatePosition(pos);
		}

		if (mainCamera == nullptr)
			return;


		
	
		if (mTexture->GetTextureType() == Texture::eTextureType::BMP)
		{
			if (mTexture->GetAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, RGB(255, 0, 255));
			}
		}
		//else if (mTexture->GetTextureType() == Texture::eTextureType::PNG)
		//{
		//	Gdiplus::ImageAttributes imgAtt = {};
		//	imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

		//	Gdiplus::Graphics graphcis(hdc);

		//	graphcis.RotateTransform(rot);

		//	graphcis.DrawImage(mTexture->GetImage()
		//		, Gdiplus::Rect
		//		(
		//			pos.x - ((mTexture->GetWidth() * mSize.x) / 2),
		//			pos.y - ((mTexture->GetHeight() * mSize.y) / 2)
		//			, mTexture->GetWidth() * mSize.x * scale.x
		//			, mTexture->GetHeight() * mSize.y * scale.y
		//		)
		//		, 0, 0
		//		, mTexture->GetWidth(), mTexture->GetHeight()
		//		, Gdiplus::UnitPixel
		//		, nullptr/*&imgAtt*/);
		//}
	}
}
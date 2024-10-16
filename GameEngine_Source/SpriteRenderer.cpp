#include "pch.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Debug_Text.h"
namespace GE
{
	SpriteRenderer::SpriteRenderer()
		: mSize(Vector2(1.f,1.f))
		, mTexture(nullptr)
		, Component(eComponentType::SPRITERENDERER)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::LateUpdate()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		HDC texHdc = mTexture->GetHdc();

		if (mainCamera->GetTarget()!=nullptr)
		{
			pos = mainCamera->CalculatePosition(pos);	
		}

		float width = mTexture->GetWidth() * mSize.x * scale.x;
		float height = mTexture->GetHeight() * mSize.y * scale.y;

		float cameraX = mainCamera->GetCameraPosition().x;
		float cameraY = mainCamera->GetCameraPosition().y;
		float cameraWidth = 1600;
		float cameraHeight = 900;

		/*Print_Text(hdc, L"pos.x", pos.x, Vector2(0, 150));
		Print_Text(hdc, L"pos.y", pos.y, Vector2(0, 200));
		Print_Text(hdc, L"cameraX", cameraX, Vector2(0, 250));
		Print_Text(hdc, L"cameraY", cameraY, Vector2(0, 300));*/
		
		bool culling = false;

		//Print_Text(hdc, L"Culling ",culling, Vector2(0, 350));

		if (pos.x + width < 0 || pos.x > cameraWidth||
			pos.y + height < 0 || pos.y > cameraHeight)
		{
			culling = true;
			//Print_Text(hdc, L"Culling ",culling, Vector2(0, 350));
			return;
		}

		HRGN clipRegion = CreateRectRgn(0, 0, (int)cameraWidth, (int)cameraHeight);
		SelectClipRgn(hdc, clipRegion);

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
					, pos.x
					, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc()
					, 0, 0
					, mTexture->GetWidth()
					, mTexture->GetHeight()
					, RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == Texture::eTextureType::PNG)
		{
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphcis(hdc);

			graphcis.RotateTransform(rot);

			graphcis.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					pos.x,
					pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
				)
				, 0, 0
				, mTexture->GetWidth(), mTexture->GetHeight()
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}
		SelectClipRgn(hdc, NULL);
		DeleteObject(clipRegion);
	}
}
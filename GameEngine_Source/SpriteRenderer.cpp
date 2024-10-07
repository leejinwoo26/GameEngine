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
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		HDC texHdc = mTexture->GetHdc();

		if (mainCamera != nullptr)
		{
			pos = mainCamera->CalculatePosition(pos);	
		}

		float width = mTexture->GetWidth() * mSize.x * scale.x;
		float height = mTexture->GetHeight() * mSize.y * scale.y;

		// 카메라의 뷰 포트
		float cameraX = mainCamera->GetCameraPosition().x;
		float cameraY = mainCamera->GetCameraPosition().y;
		float cameraWidth = 1600;
		float cameraHeight = 900;

		Print_Text(hdc, L"pos.x", pos.x, Vector2(0, 150));
		Print_Text(hdc, L"pos.y", pos.y, Vector2(0, 200));
		
		bool culling = false;

		Print_Text(hdc, L"Culling ",culling, Vector2(0, 250));

		if (pos.x + width < 0 || pos.x > cameraWidth - 325 ||
			pos.y + height < 0 || pos.y > cameraHeight - 200)
		{
			culling = true;
			Print_Text(hdc, L"Culling ",culling, Vector2(0, 250));
			return;
		}





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
				//https://blog.naver.com/power2845/50147965306
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
			/*TransparentBlt(hdc, pos.x - ((mTexture->GetWidth() * mSize.x) / 2), pos.y - ((mTexture->GetHeight() * mSize.y) / 2)
				, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
				, RGB(255, 0, 255));*/
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
	}
}
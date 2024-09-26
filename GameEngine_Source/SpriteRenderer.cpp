#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Renderer.h"

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

		if (mainCamera)
		{
			pos = mainCamera->CalculatePosition(pos);
		}


		if (mTexture->GetTextureType() == Texture::eTextureType::BMP)
		{
			TransparentBlt(hdc, pos.x - ((mTexture->GetWidth() * mSize.x) / 2), pos.y - ((mTexture->GetHeight() * mSize.y) / 2)
				, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
				, RGB(255, 0, 255));
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
					pos.x - ((mTexture->GetWidth() * mSize.x) / 2), pos.y - ((mTexture->GetHeight() * mSize.y) / 2)
					, mTexture->GetWidth() * mSize.x 
					, mTexture->GetHeight() * mSize.y 
				)
				, 0, 0
				, mTexture->GetWidth(), mTexture->GetHeight()
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}
	}
}
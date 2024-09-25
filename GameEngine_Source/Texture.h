#pragma once
#include "Resource.h"

namespace GE
{
	class Texture : public Resource
	{
	public:
		enum class eTextureType
		{
			BMP,
			PNG,
			NONE
		};
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetTextureType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:
		Gdiplus::Image* mImage;
		HBITMAP mBitmap;
		HDC mHdc;
		eTextureType mType;

		UINT mWidth;
		UINT mHeight;
	};
}
#include "Texture.h"
#include "Application.h"

extern GE::Application app;

namespace GE
{

	Texture::Texture() :
		Resource(eResourceType::TEXTURE),
		mbAlpha(false)
	{
	}
	Texture::~Texture()
	{
	}
	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);
		mFilePath = path;

		if (ext == L"bmp")
		{
			mType = eTextureType::BMP;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			if (info.bmBitsPixel == 32)
				mbAlpha = true;
			else if (info.bmBitsPixel == 24)
				mbAlpha = false;


			HDC mainDC = app.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			GetObject(mBitmap, sizeof(BITMAP), &info);

			DeleteObject(oldBitmap);
		}
		else if (ext == L"png")
		{
			mType = eTextureType::PNG;
			mImage = Gdiplus::Image::FromFile(path.c_str());
			if (mImage == nullptr)
				return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		
		return S_OK;
	}
	COLORREF Texture::GetPixel(int x , int y)
	{
		return ::GetPixel(mHdc, x, y);
	}
}
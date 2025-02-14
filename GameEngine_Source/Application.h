#pragma once
#include "CommonInclude.h"

namespace GE
{
	class Application
	{
	public:
		void Initialize(HWND hwnd,UINT width,UINT height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		void Release();
		void Destroy();
		void ChangeTileBuffer(const Vector2& size);
		Application();
		~Application();

		void SetParticleHwnd(HWND particleHwnd) { mParticleHwnd = particleHwnd; };
		HWND GetParticleHwnd() { return mParticleHwnd; }

		HDC& GetParticleBackHdc() { return mParticleBackHdc; }
		HDC& GetParticleHdc() { return mParticleHdc; }


		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetBackTileHdc() { return mBackTileHdc; }
		HBITMAP GetBackTileBuffer() { return mBackTileBuffer; }
		void ClearBitmap();
	private:
		void CopyHighSpeed();
		void CreateBackBuffer(HWND hwnd,UINT width, UINT height);
	private:
		HWND mHwnd;
		HDC mHdc;

		HWND mParticleHwnd;
		HDC mParticleHdc;
		HDC mParticleBackHdc;
		HBITMAP mParticleBackBuffer;

		HBITMAP mBackBuffer;
		HDC mBackHdc;

		HBITMAP mBackTileBuffer;
		HDC mBackTileHdc;

		UINT mWidth;
		UINT mHeight;
	};
}


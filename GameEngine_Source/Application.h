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

		Application();
		~Application();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
	private:
		void ClearBitmap();
		void CopyHighSpeed();
		void CreateBackBuffer(HWND hwnd,UINT width, UINT height);
	private:
		HWND mHwnd;
		HDC mHdc;

		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;
	};
}


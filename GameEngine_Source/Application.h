#pragma once
#include "CommonInclude.h"

namespace GE
{
	class Application
	{
	public:
		void Initilize(HWND hwnd,UINT width,UINT height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		Application();
		~Application();

	private:
		HWND mHwnd;
		HDC mHdc;

		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;

		class GameObject* mGameObj;
	};
}


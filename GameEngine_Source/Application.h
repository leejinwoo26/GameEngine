#pragma once
#include "CommonInclude.h"

namespace GE
{
	class Application
	{
	public:
		void Initilize(HWND hwnd);
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		Application();
		~Application();

	private:
		HWND mHwnd;
		HDC mHdc;
		class GameObject* mGameObj;
	};
}


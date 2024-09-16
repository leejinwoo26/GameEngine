#include "Application.h"
namespace GE
{
	Application::Application():
		mHwnd(nullptr),
		mHdc(nullptr)
	{

	}
	Application::~Application()
	{

	}

	void Application::Initilize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{

	}
	void Application::LateUpdate()
	{

	}
	void Application::Render()
	{

		Rectangle(mHdc, 100, 100, 200, 200);
	}
}

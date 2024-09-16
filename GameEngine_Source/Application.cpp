#include "Application.h"
#include "GameObject.h"


namespace GE
{
	Application::Application():
		mHwnd(nullptr),
		mHdc(nullptr)
	{
		mGameObj = nullptr;
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
		mGameObj->Update();
	}
	void Application::LateUpdate()
	{
		mGameObj->Render(mHdc);
	}
	void Application::Render()
	{
		mGameObj->Render(mHdc);
	}
}

#include "Application.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"

namespace GE
{
	Application::Application():
		mHwnd(nullptr),
		mHdc(nullptr),
		mWidth(0),
		mHeight(0),
		mBackBuffer(NULL),
		mBackHdc(NULL)
	{
		mGameObj = nullptr;
	}
	Application::~Application()
	{

	}

	void Application::Initilize(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);


		RECT rc = { 0, 0, width, height };

		mWidth = rc.right - rc.left;
		mHeight = rc.bottom - rc.top;

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, nullptr, 0, 0, rc.right - rc.left, rc.bottom - rc.top,0);
		ShowWindow(mHwnd, true);

		mGameObj = new GameObject;
		mGameObj->Initilize();

		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);

		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		mGameObj->Update();
	}

	void Application::LateUpdate()
	{
		mGameObj->Render(mBackHdc);
	}

	void Application::Render()
	{
		Rectangle(mBackHdc, -1, -1, 1600, 900);
		mGameObj->Render(mBackHdc);
		Time::Render(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
}

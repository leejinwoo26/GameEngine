#include "Application.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "Resources.h"
#include "CollisionManager.h"
#include "UiManager.h"
#include "Fmod.h"

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
	}
	Application::~Application()
	{

	}
	void Application::Release()
	{
		SceneManager::Release();
		Resources::Release();
		UiManager::Release();
	}
	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		CreateBackBuffer(hwnd,width, height);

		Fmod::Initialize();
		Input::Initialize();
		Time::Initialize();
		SceneManager::Initialize();
		CollisionManager::Initialize();
		UiManager::Initialize();
	}
	void Application::CreateBackBuffer(HWND hwnd,UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rc = { 0, 0, width, height };

		mWidth = rc.right - rc.left;
		mHeight = rc.bottom - rc.top;

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, nullptr, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0);
		ShowWindow(mHwnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);
	}


	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		SceneManager::Update();
		CollisionManager::Update();
		UiManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
		CollisionManager::LateUpdate();
		UiManager::LateUpdate();
	}

	void Application::Render()
	{
		ClearBitmap();

		SceneManager::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);
		Time::Render(mBackHdc);
		UiManager::Render(mBackHdc);

		CopyHighSpeed();
	}
	void Application::ClearBitmap()
	{
		Rectangle(mBackHdc, -1, -1, 1600, 900);
	}
	void Application::CopyHighSpeed()
	{
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
}

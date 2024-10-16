#include "pch.h"
#include "Application.h"
#include "GameObject.h"
#include "Input.h"
#include "GETime.h"
#include "SceneManager.h"
#include "Resources.h"
#include "CollisionManager.h"
#include "UiManager.h"
#include "Fmod.h"
#include "Renderer.h"
#include "Debug_Text.h"

namespace GE
{
	Application::Application():
		mHwnd(nullptr),
		mHdc(nullptr),
		mWidth(0),
		mHeight(0),
		mBackBuffer(NULL),
		mBackHdc(NULL),
		mBackTileBuffer(NULL),
		mBackTileHdc(NULL)
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

		mParticleHdc = GetDC(mParticleHwnd);
		mParticleBackBuffer = CreateCompatibleBitmap(mParticleHdc, width, height);
		mParticleBackHdc = CreateCompatibleDC(mParticleHdc);
		HBITMAP oldParticleBitmap = (HBITMAP)SelectObject(mParticleBackHdc, mParticleBackBuffer);
		DeleteObject(oldParticleBitmap);



		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);

		mBackTileHdc = CreateCompatibleDC(mBackHdc);

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
		if (mainCamera)
		{
			Vector2 pos = mainCamera->GetCameraPosition();
			//BitBlt(mBackHdc, 0, 0, GetWidth(), GetHeight(), mBackTileHdc, pos.x, pos.y, SRCCOPY);
			Rectangle(mBackHdc, -1, -1, 1600, 900);
			Print_Text(mBackHdc, L"카메라 x ", pos.x, Vector2(0, 100));
			Print_Text(mBackHdc, L"카메라 y ", pos.y, Vector2(0, 150));
		}
		else
		{
			Rectangle(mBackHdc, -1, -1, 1600, 900);
		}
		Rectangle(mParticleBackHdc, -1, -1, 1600, 900);
	}
	void Application::ChangeTileBuffer(const Vector2& size)
	{
		mBackTileBuffer = CreateCompatibleBitmap(mBackHdc, size.x, size.y);
		HBITMAP oldbitmap = (HBITMAP)SelectObject(mBackTileHdc, mBackTileBuffer);
		DeleteObject(oldbitmap);
	}

	void Application::CopyHighSpeed()
	{
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
		BitBlt(mParticleHdc, 0, 0, mWidth, mHeight, mParticleBackHdc, 0, 0, SRCCOPY);
	}
}

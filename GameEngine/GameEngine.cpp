// GameEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameEngine.h"
#include <commdlg.h>  // 파일 대화상자를 위한 헤더
#include "..\\GameEngine_Source\\Application.h"
#include "..\\GameEngine_Source\\CommonInclude.h"
#include "..\\GameEngine_Source\\Texture.h"
#include "..\\GameEngine_Source\\Resources.h"
#include "..\\GameEngine_Source\\TileRenderer.h"
#include "..\\GameEngine_Source\\SceneManager.h"
#include "..\\GameEngine_Lib\\LoadScene.h"
#include "..\\GameEngine_Lib\\ResourcesLoad.h"
#include "..\\GameEngine_Lib\\ParticleScene.h"

#define MAX_LOADSTRING 100

GE::Application app;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name , WNDPROC wndProc , int menuName);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndTileProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AnimationProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AnimationAbout(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(606);
    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc, IDC_GAMEENGINE);
    MyRegisterClass(hInstance, L"TILEWINDOW", WndTileProc, IDC_GAMEENGINE);
    MyRegisterClass(hInstance, L"AnimationWINDOW", AnimationProc, IDR_MENU1);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE));

    MSG msg;

    // 기본 메시지 루프입니다:

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            app.Run();
        }
    }

    app.Release();
    Gdiplus::GdiplusShutdown(gpToken);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name , WNDPROC wndProc , int menuName)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(menuName);
    wcex.lpszClassName  = name;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   const int width = 1600;
   const int height = 900;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   HWND ToolhWnd = CreateWindowW(L"TILEWINDOW", L"TILEWINDOW", WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   HWND AnimationHWnd = CreateWindowW(L"AnimationWINDOW", L"AnimationWINDOW", WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);


   app.Initialize(hWnd,width,height);
   app.SetParticleHwnd(AnimationHWnd);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   ShowWindow(AnimationHWnd, nCmdShow);
   UpdateWindow(AnimationHWnd);
   

   Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);
   
   GE::LoadResources();
   GE::LoadScenes();

   if (GE::SceneManager::GetActiveScene()->GetName() == L"ToolScene")
   {
       //타일 윈도우 크기
       GE::Texture* texture = GE::Resources::Find<GE::Texture>(L"SpringFloor");

       RECT rc = { 0, 0, texture->GetWidth(), texture->GetHeight() };

       UINT mWidth = rc.right - rc.left;
       UINT mHeight = rc.bottom - rc.top;

       AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

       SetWindowPos(ToolhWnd, nullptr, width, 0, mWidth, mHeight, 0);
       ShowWindow(ToolhWnd, nCmdShow);
       UpdateWindow(ToolhWnd);
   }

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        POINT mousePos = { };
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);
        Vector2 mousePosition;
        mousePosition.x = mousePos.x;
        mousePosition.y = mousePos.y;
        int idxX = mousePosition.x /GE::TileRenderer::OriginTileSize.x;
        int idxY = mousePosition.y / GE::TileRenderer::OriginTileSize.y;
        GE::TileRenderer::SelectedIndex = Vector2(idxX, idxY);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        GE::Texture* mTexture = GE::Resources::Find<GE::Texture>(L"SpringFloor");


        TransparentBlt(hdc
            , 0, 0
            , mTexture->GetWidth()
            , mTexture->GetHeight()
            , mTexture->GetHdc()
            , 0, 0
            , mTexture->GetWidth()
            , mTexture->GetHeight()
            , RGB(255, 0, 255));


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK AnimationProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HBITMAP hBitmap = NULL;         // BMP 이미지 핸들
    Gdiplus::Image* pngBitmap = NULL;       // PNG 이미지 객체 (GDI+ 사용)
    
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case ID_32773:
        {
            OPENFILENAME ofn;       // 구조체를 설정하기 위한 변수
            ZeroMemory(&ofn, sizeof(ofn));

            WCHAR fileName[MAX_PATH] = L"";
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = fileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrFilter = L"BMP Files\0*.bmp\0PNG Files\0*.png\0All Files\0*.*\0";
            ofn.nFilterIndex = 1;  // 기본적으로 BMP 파일 필터를 선택
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE)
            {
                // 파일 확장자 확인 후 BMP 또는 PNG 로드
                LPCWSTR extension = wcsrchr(fileName, L'.');
                if (extension && _wcsicmp(extension, L".bmp") == 0)
                {
                    if (hBitmap) DeleteObject(hBitmap);  // 기존 BMP 해제
                    hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);  // BMP 로드
                }
                else if (extension && _wcsicmp(extension, L".png") == 0)
                {
                    if (pngBitmap) delete pngBitmap;  // 기존 PNG 해제
                    pngBitmap = Gdiplus::Image::FromFile(fileName);
                }
                InvalidateRect(hWnd, NULL, TRUE);  // 창을 다시 그리도록 요청
            }
        }
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC partHdc = app.GetParticleHdc();
        partHdc = BeginPaint(hWnd, &ps);
        //if (hBitmap)
        //{
        //    // BMP 그리기
        //    HDC hdcMem = CreateCompatibleDC(ParticleHdc);
        //    SelectObject(hdcMem, hBitmap);
        //    BITMAP bitmap;
        //    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
        //    BitBlt(ParticleHdc, 10, 10, bitmap.bmWidth + 10, bitmap.bmHeight + 10, hdcMem, 0, 0, SRCCOPY);
        //    DeleteDC(hdcMem);
        //}
        //else if (pngBitmap)
        //{
        //    // PNG 그리기 (GDI+ 사용)
        //    Gdiplus::Graphics graphics(ParticleHdc);
        //    graphics.DrawImage(pngBitmap, 10, 10);
        //}
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

INT_PTR CALLBACK AnimationAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetWindowText(hDlg, L"애니메이션"); 
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case IDCANCEL :
            EndDialog(hDlg, LOWORD(wParam));
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

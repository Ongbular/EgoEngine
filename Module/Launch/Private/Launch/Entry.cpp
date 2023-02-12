// EgoEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <string>
#include <format>
#include <filesystem>

#include "resource.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst = nullptr;                                // 현재 인스턴스입니다.
HWND g_hWnd = nullptr;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT RegisterWindowClass(HINSTANCE hInstance, const TCHAR* className);
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& hWnd, const TCHAR* className, const TCHAR* title);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInst = hInstance;

	const std::wstring className{ TEXT("TestLaunchWindow") };
	RegisterWindowClass(hInstance, className.c_str());

	if (FAILED(InitWindow(hInstance, nCmdShow, g_hWnd, className.c_str(), TEXT("EgoEngine"))))
		return 0;
				
	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

HRESULT RegisterWindowClass(HINSTANCE hInstance, const TCHAR* className)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON_WINDOW);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON_WINDOW);

	if (!RegisterClassEx(&wcex))
	{
		const std::wstring errorMessage =
			std::format(TEXT("Failed to register window. Error Code: {}"), GetLastError());
		MessageBox(nullptr, errorMessage.c_str(), TEXT("Window Register Error!"), MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, HWND& hWnd, const TCHAR* className, const TCHAR* title)
{
	// Create window
	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(className, title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr,
		hInstance,
		nullptr);
	if (!hWnd)
		return E_FAIL;

	// ShowWindow(hWnd, nCmdShow);
	if (!AnimateWindow(hWnd, 100, AW_ACTIVATE | AW_CENTER))
	{
		const auto failString = std::format(TEXT("AnimateWindow Failed! Error Code: {}"), GetLastError());
		OutputDebugString(failString.c_str());
	}

	const auto debugString = std::format(TEXT("{} is created!"), title);
	OutputDebugString(debugString.c_str());

	return S_OK;
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

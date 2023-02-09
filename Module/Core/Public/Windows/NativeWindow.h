#pragma once

#define WINDOW_MIN_WIDTH (100)
#define WINDOW_MIN_HEIGHT (100)

class NativeWindow
{
public:
	NON_COPYABLE(NativeWindow)

	NativeWindow(HINSTANCE hInstance, const std::wstring& title, int32 width, int32 height);
	virtual ~NativeWindow() = default;

	virtual void HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;

private:
	virtual void registerWindowClass(const WCHAR* className);

	HWND mHWnd;
	std::wstring mTitle;
	int32 mWidth;
	int32 mHeight;
};

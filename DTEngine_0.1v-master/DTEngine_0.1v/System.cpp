#include "pch.h"
#include "System.h"
#include "World.h"


System::System() : screen_width_(0), screen_height_(0)
{
	InitializeWindows();
}


System::~System()
{
	ShutdownWindows();
}

void System::Run()
{
	MSG msg;

	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			result = Frame();
			if (!result) {
				MessageBox(hwnd_, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
			if (World::GetInstance().GetKeyState(VK_ESCAPE) > 0) {
				done = true;
			}
		}
	}
}

bool System::Frame()
{
	World::GetInstance().Update();
	World::GetInstance().Render();
	return true;
}

LRESULT CALLBACK System::MessageHandle(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

void System::InitializeWindows()
{
	WNDCLASSEX wc;
	DEVMODE dm_screen_settings;
	int pos_x, pos_y;

	application_handle_ = this;
	hinstance_ = GetModuleHandle(NULL);
	application_name_ = L"Engine";

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hinstance_;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm			= wc.hIcon;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= application_name_;
	wc.cbSize			= sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screen_width_	= GetSystemMetrics(SM_CXSCREEN);
	screen_height_	= GetSystemMetrics(SM_CYSCREEN);

	if (kFullScreen) {
		memset(&dm_screen_settings, 0, sizeof(dm_screen_settings));
		dm_screen_settings.dmSize		= sizeof(dm_screen_settings);
		dm_screen_settings.dmPelsWidth = screen_width_;
		dm_screen_settings.dmPelsHeight	= screen_height_;
		dm_screen_settings.dmBitsPerPel = 32;
		dm_screen_settings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dm_screen_settings, CDS_FULLSCREEN);

		pos_x = pos_y = 0;
	}
	else {
		pos_x = (screen_width_ - kScreenWidth / 72 - kScreenWidth)	 / 2;
		pos_y = (screen_height_ - kScreenHeight / 18 - kScreenHeight) / 2;

		screen_width_	= kScreenWidth;
		screen_height_	= kScreenHeight;
	}

	hwnd_ = CreateWindowEx(WS_EX_APPWINDOW, application_name_, application_name_,
		WS_OVERLAPPEDWINDOW/*WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP*/, pos_x, pos_y,
		screen_width_ + screen_width_ / 72, screen_height_ + screen_height_ / 18, NULL, NULL, hinstance_, NULL);

	ShowWindow(hwnd_, SW_SHOW);
	SetForegroundWindow(hwnd_);
	SetFocus(hwnd_);

	ShowCursor(true);

	return;
}

void System::ShutdownWindows()
{
	ShowCursor(true);

	if (kFullScreen) {
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(hwnd_);
	UnregisterClass(application_name_, hinstance_);
	
	return;
}

int System::GetScreenWidth()
{
	return screen_width_;
}

void System::SetScreenWidth(int screen_width)
{
	screen_width_ = screen_width;
}

int System::GetScreenHeight()
{
	return screen_height_;
}

void System::SetScreenHeight(int screen_height)
{
	screen_height_ = screen_height;
}

HWND System::GetHwnd()
{
	return hwnd_;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		application_handle_->MessageHandle(hwnd, umessage, wparam, lparam);
	}
}

System* application_handle_;
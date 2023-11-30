#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Define.h"

class System
{
public:
	System();
	~System();

	void Run();

	LRESULT CALLBACK MessageHandle(HWND, UINT, WPARAM, LPARAM);

	int GetScreenWidth();
	void SetScreenWidth(int screen_width);

	int GetScreenHeight();
	void SetScreenHeight(int screen_width);

	HWND GetHwnd();

private:
	bool Frame();
	void InitializeWindows();
	void ShutdownWindows();

private:
	LPCWSTR application_name_;
	HINSTANCE hinstance_;
	HWND hwnd_;

	int screen_width_, screen_height_;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern System * application_handle_;
#include "stdafx.h"
#include "windows/windows_window.h"
#include "../resource.h"


using namespace Tga2D;

CWindowsWindow::CWindowsWindow(void)
{
}


CWindowsWindow::~CWindowsWindow(void)
{
}

bool CWindowsWindow::Init(Vector2<unsigned int> aWindowSize, HWND*& aHwnd, SEngineCreateParameters* aSetting, HINSTANCE& aHInstanceToFill)
{
	if (!aSetting)
	{
		return false;
	}
	HINSTANCE instance = GetModuleHandle(NULL);
	aHInstanceToFill = instance;
	ZeroMemory(&myWindowClass, sizeof(WNDCLASSEX));
	myWindowClass.cbSize = sizeof(WNDCLASSEX);
	myWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	myWindowClass.lpfnWndProc = WindowProc;
	myWindowClass.hInstance = instance;
	myWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	myWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	myWindowClass.lpszClassName = L"WindowClass1";
	myWindowClass.hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	myWindowClass.hIconSm = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClassEx(&myWindowClass);

	RECT wr = {0, 0, static_cast<long>(aWindowSize.x), static_cast<long>(aWindowSize.y)};    // set the size, but not the position
	//AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	DWORD windowStyle = 0;
	switch (aSetting->myWindowSetting)
	{
	case EWindowSetting_Overlapped:
		windowStyle = WS_OVERLAPPEDWINDOW;
		break;	
	case EWindowSetting_Borderless:
		windowStyle = WS_POPUP | WS_MINIMIZEBOX;
		break;
	default:
		break;
	}

	if (!aHwnd)
	{
		myWindowHandle = CreateWindowEx(WS_EX_CLIENTEDGE,
			L"WindowClass1",    // name of the window class
			aSetting->myApplicationName.c_str(),    // title of the window
			windowStyle,    // window style
			CW_USEDEFAULT,    // x-position of the window
			CW_USEDEFAULT,    // y-position of the window
			wr.right - wr.left,    // width of the window
			wr.bottom - wr.top,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			instance,    // application handle
			NULL);    // used with multiple windows, NULL
		
		ShowWindow(myWindowHandle, true);
		aHwnd = &myWindowHandle;
	}
	else
	{
		myWindowHandle = *aHwnd;
	}




	// Fix to set the window to the actual resolution as the borders will mess with the resolution wanted

	if (aSetting->myWindowSetting == EWindowSetting_Overlapped)
	{
		RECT r;
		GetClientRect(myWindowHandle, &r); //get window rect of control relative to screen
		int horizontal = r.right - r.left;
		int vertical = r.bottom - r.top;

		int diffX = aWindowSize.x - horizontal;
		int diffY = aWindowSize.y - vertical;

		SetResolution(aWindowSize + Tga2D::Vector2ui(diffX, diffY));
	}



	INFO_PRINT("%s %i %i", "Windows created with size ", aWindowSize.x, aWindowSize.y);

	return true;
}

LRESULT CALLBACK CWindowsWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch(message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;

	case WM_SIZE:
		{
			CEngine::GetInstance()->SetWantToUpdateSize();
		}
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hWnd, message, wParam, lParam);
}

void Tga2D::CWindowsWindow::SetResolution(Tga2D::Vector2<unsigned int> aResolution)
{
	::SetWindowPos(myWindowHandle, 0, 0, 0, aResolution.x, aResolution.y, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void Tga2D::CWindowsWindow::Close()
{
	DestroyWindow(myWindowHandle);
}

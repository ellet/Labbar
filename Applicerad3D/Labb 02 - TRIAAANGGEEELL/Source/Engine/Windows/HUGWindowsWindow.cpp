#include "stdafx.h"
#include "HUGWindowsWindow.h"
#include "Engine/HUGEngine.h"
#include "windows.h"

LRESULT CALLBACK HandleWindowsMessage(HWND aWindowHandle, UINT aMessage, WPARAM wParam, LPARAM lParam)
{
	switch (aMessage)
	{
	case WM_SIZE:
		break;
	case WM_ENTERSIZEMOVE:
		break;
	case WM_EXITSIZEMOVE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT tempPaintStruct;
		BeginPaint(aWindowHandle, &tempPaintStruct);
		EndPaint(aWindowHandle, &tempPaintStruct);
	}
	break;
	case WM_CREATE:
		break;
	case WM_CLOSE:
		DestroyWindow(aWindowHandle);
		CHUGEngineSingleton::CloseGame();
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		CHUGEngineSingleton::CloseGame();
		return 0;
		break;
	default:
		return DefWindowProc(aWindowHandle, aMessage, wParam, lParam);
	}
	return DefWindowProc(aWindowHandle, aMessage, wParam, lParam);
}

CHUGWindowsWindow::CHUGWindowsWindow()
{
}

CHUGWindowsWindow::~CHUGWindowsWindow()
{
}

void CHUGWindowsWindow::Init(
	const CU::Vector2ui aWindowSize /*= CU::Vector2ui(1024, 600)*/,
	const std::string & anApplicationName /*= "Default Name"*/)
{
	HINSTANCE myInstanceHandle = GetModuleHandle(NULL);

	std::string className = "Pretty Class Name";
	RegisterWindow(className);

	myWindowHandle = (LONGLONG)CreateWindowEx(
		WS_EX_CLIENTEDGE,
		className.c_str(),
		anApplicationName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, aWindowSize.x, aWindowSize.y,
		NULL, NULL, myInstanceHandle, NULL);

	if (myWindowHandle == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}

	ShowWindow((HWND)myWindowHandle, SW_SHOWNORMAL);
	UpdateWindow((HWND)myWindowHandle);
}

void CHUGWindowsWindow::Update()
{
	MSG message;

	while (PeekMessage(&message, (HWND)(myWindowHandle), 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void* CHUGWindowsWindow::GetHWND()
{
	return &myWindowHandle;
}

void CHUGWindowsWindow::RegisterWindow(const std::string & aClassName)
{
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = HandleWindowsMessage;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = aClassName.c_str();
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
}

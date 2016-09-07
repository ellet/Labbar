#include "stdafx.h"
#include <windows.h>
#include <CU/Includes/CUCommonIncludes.h>
#include <CU/Utility/WindowsFunctions/WindowHelperFunctions.h>

const char g_szClassName[] = "myWindowClass";

const std::string windowclassname = "prettyWindowsClassName";

bool globalShouldRun = true;

// the Window Procedure
LRESULT CALLBACK WindowMessage(HWND aWindowHandle, UINT aMessage, WPARAM wParam, LPARAM lParam)
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
		break;
	case WM_CREATE:
		break;
	case WM_CLOSE:
		DestroyWindow(aWindowHandle);
		globalShouldRun = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		globalShouldRun = false;
		break;
	default:
		return DefWindowProc(aWindowHandle, aMessage, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	
	HWND windowHandle;
	MSG message;

	// Creating the Window
	const std::string ApplicationName = "Pretty Window";
	const CU::Vector2i WindowSize = CU::Vector2i(500, 500);

	windowHandle = CU::WindowsFunctions::CreateWindowsWindow(hInstance, WindowMessage, windowclassname, WindowSize, ApplicationName, nCmdShow);

	// The Message Loop
	while (globalShouldRun == true)
	{
		while (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//GAME CODEEERUUUU
	}

	return static_cast<int>(message.wParam);
}
#include "stdafx.h"
#include "windows/windows_window.h"
#include "../resource.h"
#include "Input/InputCallback.h"


using namespace DX2D;


InputCallback * DX2D::CWindowsWindow::ourInputCallback = nullptr;

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

	RECT wr = {0, 0, aWindowSize.x, aWindowSize.y};    // set the size, but not the position
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


	

	INFO_PRINT("%s %i %i", "Windows created with size ", aWindowSize.x, aWindowSize.y);

	return true;
}

LRESULT CALLBACK CWindowsWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
		case WM_KEYDOWN:
		{
			SB::KeyboardKey keyDown = ConvertVirtualKey(wParam);
			// Bit 0 - 15 is the repeat count
			int repeatCount = static_cast<int>(HIWORD(lParam) & KF_REPEAT);
			if (repeatCount == 0)
			{
				ourInputCallback->KeyPressed(keyDown);
			}
		}
		break;


		case WM_KEYUP:
		{
			SB::KeyboardKey keyUp = ConvertVirtualKey(wParam);
			ourInputCallback->KeyReleased(keyUp);
		}
		break;

		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
		break;

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


SB::KeyboardKey DX2D::CWindowsWindow::ConvertVirtualKey(const WPARAM& aVirtualKey)
{
	switch (aVirtualKey)
	{
	case 0x30: 
		return SB::KeyboardKey::eNum0;
	case 0x31:
		return SB::KeyboardKey::eNum1;
	case 0x32:
		return SB::KeyboardKey::eNum2;
	case 0x33:
		return SB::KeyboardKey::eNum3;
	case 0x34:
		return SB::KeyboardKey::eNum4;
	case 0x35:
		return SB::KeyboardKey::eNum5;
	case 0x36:
		return SB::KeyboardKey::eNum6;
	case 0x37:
		return SB::KeyboardKey::eNum7;
	case 0x38:
		return SB::KeyboardKey::eNum8;
	case 0x39:
		return SB::KeyboardKey::eNum9;
	case 0x41:
		return SB::KeyboardKey::eA;
	case 0x42:
		return SB::KeyboardKey::eB;
	case 0x43:
		return SB::KeyboardKey::eC;
	case 0x44:
		return SB::KeyboardKey::eD;
	case 0x45:
		return SB::KeyboardKey::eE;
	case 0x46:
		return SB::KeyboardKey::eF;
	case 0x47:
		return SB::KeyboardKey::eG;
	case 0x48:
		return SB::KeyboardKey::eH;
	case 0x49:
		return SB::KeyboardKey::eI;
	case 0x4A:
		return SB::KeyboardKey::eJ;
	case 0x4B:
		return SB::KeyboardKey::eK;
	case 0x4C:
		return SB::KeyboardKey::eL;
	case 0x4D:
		return SB::KeyboardKey::eM;
	case 0x4E:
		return SB::KeyboardKey::eN;
	case 0x4F:
		return SB::KeyboardKey::eO;
	case 0x50:
		return SB::KeyboardKey::eP;
	case 0x51:
		return SB::KeyboardKey::eQ;
	case 0x52:
		return SB::KeyboardKey::eR;
	case 0x53:
		return SB::KeyboardKey::eS;
	case 0x54:
		return SB::KeyboardKey::eT;
	case 0x55:
		return SB::KeyboardKey::eU;
	case 0x56:
		return SB::KeyboardKey::eV;
	case 0x57:
		return SB::KeyboardKey::eW;
	case 0x58:
		return SB::KeyboardKey::eX;
	case 0x59:
		return SB::KeyboardKey::eY;
	case 0x5A:
		return SB::KeyboardKey::eZ;
	case 0xDC:
		return SB::KeyboardKey::eConsoleButton;
	case VK_F1:
		return SB::KeyboardKey::eF1;
	case VK_F2:
		return SB::KeyboardKey::eF2;
	case VK_F3:
		return SB::KeyboardKey::eF3;
	case VK_F4:
		return SB::KeyboardKey::eF4;
	case VK_F5:
		return SB::KeyboardKey::eF5;
	case VK_F6:
		return SB::KeyboardKey::eF6;
	case VK_F7:
		return SB::KeyboardKey::eF7;
	case VK_F8:
		return SB::KeyboardKey::eF8;
	case VK_F9:
		return SB::KeyboardKey::eF9;
	case VK_F10:
		return SB::KeyboardKey::eF10;
	case VK_F11:
		return SB::KeyboardKey::eF11;
	case VK_F12:
		return SB::KeyboardKey::eF12;
	case VK_ESCAPE:
		return SB::KeyboardKey::eEscape;
	case VK_RETURN:
		return SB::KeyboardKey::eReturn;
	case VK_SPACE:
		return SB::KeyboardKey::eSpace;
	case VK_CONTROL:
		return SB::KeyboardKey::eControl;
	case VK_SHIFT:
		return SB::KeyboardKey::eShift;
	case VK_LEFT:
		return SB::KeyboardKey::eLeft;
	case VK_RIGHT:
		return SB::KeyboardKey::eRight;
	case VK_UP:
		return SB::KeyboardKey::eUp;
	case VK_DOWN:
		return SB::KeyboardKey::eDown;
	case VK_LMENU:
		return SB::KeyboardKey::eAlt;
	default:
		return SB::KeyboardKey::eNone;
	}
}


void DX2D::CWindowsWindow::SetResolution(DX2D::Vector2<unsigned int> aResolution)
{
	::SetWindowPos(myWindowHandle, 0, 0, 0, aResolution.x, aResolution.y, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void DX2D::CWindowsWindow::Close()
{
	DestroyWindow(myWindowHandle);
}

void DX2D::CWindowsWindow::SetInputCallback(InputCallback & aCallback)
{
	ourInputCallback = &aCallback;
}



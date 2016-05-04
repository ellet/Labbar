// DirectInput.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DirectInput.h"
#include "InputWrapper.h"
#include <sstream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

///////////////////////////////////////////////////
//MYSHIT

InputWrapper globalInputWrapper;
bool globalInitRan = false;

LONG globalLastFrameX = 0;
LONG globalLastFrameY = 0;
LONG globalScrollLastFrameZ = 0;

bool CheckIfMouseButtonDown(enumMouseButtons aButton);
void PrintMouseButtonState(enumMouseButtons aButton, std::string & aStringToChange);

////////////////////////////////////////////////

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIRECTINPUT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTINPUT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTINPUT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DIRECTINPUT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	

   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   globalInitRan = true;

   globalInputWrapper.Initialize(hInst, hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (globalInitRan == true)
	{
		globalInputWrapper.Update();

		std::stringstream debugOutput;
		if (globalInputWrapper.GetMouseDeltaX() != globalLastFrameX)
		{
			globalLastFrameX = globalInputWrapper.GetMouseDeltaX();
			debugOutput << "X: " << globalInputWrapper.GetMouseDeltaX() << std::endl;
			debugOutput << "absX: " << globalInputWrapper.GetMouseAbsolutePositionX() << std::endl;
		}
		if (globalInputWrapper.GetMouseDeltaY() != globalLastFrameY)
		{
			globalLastFrameY = globalInputWrapper.GetMouseDeltaY();
			debugOutput << "Y: " << globalInputWrapper.GetMouseDeltaY() << std::endl;
			debugOutput << "absY: " << globalInputWrapper.GetMouseAbsolutePositionY() << std::endl;
		}

		if (globalInputWrapper.GetWheelDelta() != globalScrollLastFrameZ)
		{
			globalScrollLastFrameZ = globalInputWrapper.GetWheelDelta();
			debugOutput << "Wheel: " << globalInputWrapper.GetWheelDelta() << std::endl;
		}

		if (globalInputWrapper.GetKeyReleased(DIK_ESCAPE))
		{
			globalInputWrapper.SetCursorPosition(10, 10);
		}

		if ((CheckIfMouseButtonDown(enumMouseButtons::eLeft)) ||
			(CheckIfMouseButtonDown(enumMouseButtons::eRight)) ||
			(CheckIfMouseButtonDown(enumMouseButtons::eMiddle)))
		{
			std::string tempString;

			debugOutput << "Right mouse Button is: " << std::endl;

			PrintMouseButtonState(enumMouseButtons::eRight, tempString);

			debugOutput << tempString;

			debugOutput << "Left mouse Button is: " << std::endl;

			PrintMouseButtonState(enumMouseButtons::eLeft, tempString);

			debugOutput << tempString;

			debugOutput << "Middle mouse Button is: " << std::endl;

			PrintMouseButtonState(enumMouseButtons::eMiddle, tempString);

			debugOutput << tempString;	
		}
		
		for (int iKey = 0; iKey < 256; ++iKey)
		{
			if (globalInputWrapper.GetKeyDown(iKey))
			{
				debugOutput << "a key is held down" << std::endl;
				break;
			}
		}

		for (int iKey = 0; iKey < 256; ++iKey)
		{
			if (globalInputWrapper.GetKeyPressed(iKey))
			{
				debugOutput << "a key was just pressed" << std::endl;
				break;
			}
		}

		for (int iKey = 0; iKey < 256; ++iKey)
		{
			if (globalInputWrapper.GetKeyReleased(iKey))
			{
				debugOutput << "a key was just released" << std::endl;
				break;
			}
		}

		OutputDebugStringA(debugOutput.str().c_str());
	}

	

	

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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


bool CheckIfMouseButtonDown(enumMouseButtons aButton)
{
	if (globalInputWrapper.GetMouseButtonPressed(aButton))
	{
		return true;
	}
	else if (globalInputWrapper.GetMouseButtonReleased(aButton))
	{
		return true;
	}
	else if (globalInputWrapper.GetMouseButtonDown(aButton))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PrintMouseButtonState(enumMouseButtons aButton, std::string &aStringToChange)
{
	std::stringstream aInputHolder;

	aInputHolder << "---" << "Pressed: " << globalInputWrapper.GetMouseButtonPressed(aButton)
		<< std::endl << "---";

	aInputHolder << "Released: " << globalInputWrapper.GetMouseButtonReleased(aButton) 
		<< std::endl << "---";

	aInputHolder << "Held: " << globalInputWrapper.GetMouseButtonDown(aButton) << std::endl;

	aStringToChange = aInputHolder.str();
}
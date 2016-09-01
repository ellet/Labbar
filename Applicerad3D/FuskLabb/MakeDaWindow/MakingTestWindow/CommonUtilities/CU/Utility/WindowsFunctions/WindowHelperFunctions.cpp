#include "stdafx.h"
#include "WindowHelperFunctions.h"


namespace CommonUtilities
{
	namespace WindowsFunctions
	{

		HWND CreateWindowsWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName, bool aShowConsoleFlag)
		{
			CU::WindowsFunctions::RegisterWindow(aHINSTANCE, aMessageHandleFunction, aClassName);

			HWND hwnd;

			hwnd = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				aClassName.c_str(),
				"ARARARARARAAR",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, 640, 320,
				NULL, NULL, aHINSTANCE, NULL);

			//SetWindowText(hwnd, "derperperperp");

			if (hwnd == NULL)
			{
				MessageBox(NULL, "Window Creation Failed!", "Error!",
					MB_ICONEXCLAMATION | MB_OK);
				return 0;
			}

			ShowWindow(hwnd, aShowConsoleFlag);
			UpdateWindow(hwnd);

			return hwnd;
		}

		WNDCLASSEX RegisterWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName)
		{
			WNDCLASSEX wc;

			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = 0;
			wc.lpfnWndProc = aMessageHandleFunction;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = aHINSTANCE;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = aClassName.c_str();
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassEx(&wc))
			{
				MessageBox(NULL, "Window Registration Failed!", "Error!",
					MB_ICONEXCLAMATION | MB_OK);
				//return 0;
			}

			return wc;
		}

	}
}
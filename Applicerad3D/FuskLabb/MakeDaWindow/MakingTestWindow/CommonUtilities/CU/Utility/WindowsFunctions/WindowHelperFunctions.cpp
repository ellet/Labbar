#include "stdafx.h"
#include "WindowHelperFunctions.h"


namespace CommonUtilities
{
	namespace WindowsFunctions
	{

		HWND CreateWindowsWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName,
			const CU::Vector2i aWindowSize /*= CU::Vector2i(1024, 600)*/, const std::string & anApplicationName /*= "Default Name"*/, const int aWindowShowState /*= SW_SHOWNORMAL*/)
		{
			CU::WindowsFunctions::RegisterWindow(aHINSTANCE, aMessageHandleFunction, aClassName);

			HWND hwnd;

			hwnd = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				aClassName.c_str(),
				anApplicationName.c_str(),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, aWindowSize.x, aWindowSize.y,
				NULL, NULL, aHINSTANCE, NULL);

			if (hwnd == NULL)
			{
				MessageBox(NULL, "Window Creation Failed!", "Error!",
					MB_ICONEXCLAMATION | MB_OK);
				return 0;
			}

			ShowWindow(hwnd, aWindowShowState);
			UpdateWindow(hwnd);

			return hwnd;
		}

		WNDCLASSEX RegisterWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName)
		{
			WNDCLASSEX windowClass;

			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.style = 0;
			windowClass.lpfnWndProc = aMessageHandleFunction;
			windowClass.cbClsExtra = 0;
			windowClass.cbWndExtra = 0;
			windowClass.hInstance = aHINSTANCE;
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
				//return 0;
			}

			return windowClass;
		}

	}
}
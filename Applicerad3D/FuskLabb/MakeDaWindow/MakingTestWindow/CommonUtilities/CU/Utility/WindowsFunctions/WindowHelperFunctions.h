#pragma once

namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		HWND CreateWindowsWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName, bool aShowConsoleFlag);
		WNDCLASSEX RegisterWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName);
	}
}
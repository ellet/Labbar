#pragma once

namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		HWND CreateWindowsWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName, 
			const CU::Vector2i aWindowSize = CU::Vector2i(1024, 600), const std::string & anApplicationName = "Default Name", const int aWindowShowState = SW_SHOWNORMAL);
		WNDCLASSEX RegisterWindow(HINSTANCE aHINSTANCE, WNDPROC aMessageHandleFunction, const std::string & aClassName);
	}
}
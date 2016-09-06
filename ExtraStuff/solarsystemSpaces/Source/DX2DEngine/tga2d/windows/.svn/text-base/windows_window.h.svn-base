/*
This class handles the creation of the actual window
*/

#pragma once
#include <windows.h>

namespace Tga2D
{
	struct SEngineCreateParameters;
	class CWindowsWindow
	{
	public:
		CWindowsWindow(void);
		~CWindowsWindow(void);
		bool Init(Vector2<unsigned int> aWindowSize, HWND*& aHwnd, SEngineCreateParameters* aSetting, HINSTANCE& aHInstanceToFill);
		HWND GetWindowHandle() const {return myWindowHandle;}
		void SetResolution(Tga2D::Vector2<unsigned int> aResolution);
		void Close();
	private:
		 static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		 HWND myWindowHandle;
		 WNDCLASSEX myWindowClass;
	};
}

#include <windows.h>
#include <CU/Includes/CUCommonIncludes.h>
#include <CU/Utility/WindowsFunctions/WindowHelperFunctions.h>

const char g_szClassName[] = "myWindowClass";

const std::string windowclassname = "monkeyderp";

// Step 4: the Window Procedure
LRESULT CALLBACK derpmesage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	
	HWND hwnd;
	MSG Msg;

	

	// Step 2: Creating the Window

	hwnd = CU::WindowsFunctions::CreateWindowsWindow(hInstance, derpmesage, windowclassname, true);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
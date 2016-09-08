#include <windows.h>

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WindowProcedure(HWND aHWND, UINT aMessage, WPARAM wParam, LPARAM lParam)
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
	case WM_CLOSE:
		DestroyWindow(aHWND);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(aHWND, aMessage, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	HWND hwnd;
	MSG message;

	//Step 1: Registering the Window Class
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = g_szClassName;
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}
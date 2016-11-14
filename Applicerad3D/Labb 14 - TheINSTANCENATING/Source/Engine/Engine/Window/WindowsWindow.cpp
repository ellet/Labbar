#include "stdafx.h"
#include "Engine\Window\WindowsWindow.h"
#include "Engine\Window\WindowMessage.h"
#include "Engine\Window\Cursor\Cursor.h"
#include "Engine\Window\FileDropping\FileExtensions.h"
#include <iostream>
#include <imgui.h>
#include <Windowsx.h>

extern IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);

namespace
	ENGINE_NAMESPACE
{
	LRESULT CALLBACK WindowProc(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
	{
		ImGui_ImplDX11_WndProcHandler(aHwnd, aMessage, aWParam, aLParam);

		WindowsWindow* wnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(aHwnd, GWLP_USERDATA));

		if (wnd != nullptr)
		{
			if (wnd->ReceiveMessage(aHwnd, aMessage, aWParam, aLParam))
			{
				return 0;
			}
		}

		switch (aMessage)
		{
		case WM_DESTROY:
		case WM_QUIT:
			PostQuitMessage(0);
			return 0;

		case WM_SYSCOMMAND:
			if ((aWParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		}

		return DefWindowProc(aHwnd, aMessage, aWParam, aLParam);
	}

	WindowsWindow::WindowsWindow(Cursor & aCursor)
	{
		myCursor = &aCursor;
		myIsCursorConfined = false;
		myIsOpen = false;
		myHasFocus = true;
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::SetTitle(const std::string& aTitle)
	{
		if (IsOpen())
		{
			SetWindowTextA(myHandle, aTitle.c_str());
		}

		Window::SetTitle(aTitle);
	}

	bool WindowsWindow::CanResize() const
	{
		return true;
	}

	void WindowsWindow::SetSize(const Size<int>& aSize)
	{
		if (IsOpen())
		{
			RECT rect;
			GetWindowRect(myHandle, &rect);

			rect.right = rect.left + aSize.width;
			rect.bottom = rect.top + aSize.height;

			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

			SetWindowPos(myHandle, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0);
		}

		Window::SetSize(aSize);
	}

	bool WindowsWindow::PollMessage(WindowMessage& aMessage)
	{
		if (IsOpen())
		{
			MSG msg = { 0 };

			while (PeekMessage(&msg, myHandle, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				LateParseMessage(myHandle, msg.message, msg.wParam, msg.lParam);
			}
		}

		if (myMessageQueue.empty() == true)
		{
			Update();
			return false;
		}

		aMessage = myMessageQueue.front();
		myMessageQueue.pop();
		return true;
	}

	void WindowsWindow::Open()
	{
		if (IsOpen())
		{
			return;
		}

		HINSTANCE mHandle = GetModuleHandle(nullptr);

		DWORD windowStyle = WS_OVERLAPPEDWINDOW;

		RECT rect;
		rect.left = 0;
		rect.right = GetSize().width;
		rect.top = 0;
		rect.bottom = GetSize().height;

		AdjustWindowRect(&rect, windowStyle, false);

		memset(&myWindowClass, 0, sizeof(WNDCLASSEX));
		myWindowClass.cbSize = sizeof(WNDCLASSEX);
		myWindowClass.style = CS_HREDRAW | CS_VREDRAW;
		myWindowClass.lpfnWndProc = WindowProc;
		myWindowClass.hInstance = mHandle;
		myWindowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		myWindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		myWindowClass.lpszClassName = L"WindowClass";
		myWindowClass.hIcon = ::LoadIcon(mHandle, MAKEINTRESOURCE(101));
		myWindowClass.hIconSm = LoadIcon(mHandle, MAKEINTRESOURCE(101));
		RegisterClassEx(&myWindowClass);

		myHandle = CreateWindowExA(WS_EX_ACCEPTFILES, "WindowClass",
			GetTitle().c_str(),
			windowStyle,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left + 4, rect.bottom - rect.top + 4,
			nullptr, nullptr, mHandle, nullptr);

		myIsOpen = true;

		SetWindowLongPtr(myHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		// WM_CREATE is received before GWL_USERDATA is set, therefore queue a create-message manually
		ReceiveMessage(myHandle, WM_CREATE, 0, 0);

		SetVisible(IsVisible());

		// Register for raw mouse input
		RAWINPUTDEVICE rawMouseDevice;
		rawMouseDevice.usUsagePage = 0x01;
		rawMouseDevice.usUsage = 0x02;
		rawMouseDevice.dwFlags = 0;
		rawMouseDevice.hwndTarget = nullptr;

		if (RegisterRawInputDevices(&rawMouseDevice, 1, sizeof(rawMouseDevice)) == false)
		{
			Engine::GetLogger().LogError("Failed to register for raw mouse input!");
		}

		ShowCursor(false);

		Window::Open();
	}

	bool WindowsWindow::IsOpen() const
	{
		return myIsOpen;
	}

	void WindowsWindow::Close()
	{
		if (IsOpen() == false)
		{
			return;
		}

		CloseWindow(myHandle);
		myHandle = nullptr;

		myIsOpen = false;

		Window::Close();
	}

	void WindowsWindow::SetVisible(bool aIsVisible)
	{
		if (IsOpen())
		{
			ShowWindow(myHandle, aIsVisible ? SW_SHOW : SW_HIDE);
		}

		Window::SetVisible(aIsVisible);
	}

	void* WindowsWindow::GetHandle() const
	{
		return myHandle;
	}

	bool WindowsWindow::RequestFocus()
	{
		SetFocus(myHandle);
		return true;
	}

	bool WindowsWindow::HasFocus() const
	{
		return myHasFocus;
	}

	void WindowsWindow::ProcessMouseMoveData(WindowMessage& aMessage, int aX, int aY)
	{
		aMessage.data.mouseEvent.x = aX;
		aMessage.data.mouseEvent.y = aY;
		aMessage.data.mouseEvent.deltaX = aX - myPreviousMouseMoveMessage.data.mouseEvent.x;
		aMessage.data.mouseEvent.deltaY = aY - myPreviousMouseMoveMessage.data.mouseEvent.y;
		
		if (aMessage.data.mouseEvent.deltaX != 0 || aMessage.data.mouseEvent.deltaY != 0)
		{
			PostMaster::Post(MouseMovedMessage(
				aMessage.data.mouseEvent.x, aMessage.data.mouseEvent.y,
				aMessage.data.mouseEvent.deltaX, aMessage.data.mouseEvent.deltaY)
			);

			myPreviousMouseMoveMessage = aMessage;
		}
	}

	bool WindowsWindow::ReceiveMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
	{
		WindowMessage message;

		switch (aMessage)
		{
		case WM_SETCURSOR:
			if (myHasFocus == true)
			{
				SetCursor(myCursor->GetCurrentCursor());
				return true;
			}
			break;
		case WM_SIZE:
			message.type = WindowMessageType::eSizeChanged;
			message.data.resizeEvent.newSize.width = LOWORD(aLParam);
			message.data.resizeEvent.newSize.height = HIWORD(aLParam);
			UpdateSize(message.data.resizeEvent.newSize);
			break;
		case WM_CLOSE:
			message.type = WindowMessageType::eCloseButtonPressed;
			break;
		case WM_ENTERSIZEMOVE:
			message.type = WindowMessageType::eResizeBegins;
			break;
		case WM_EXITSIZEMOVE:
			message.type = WindowMessageType::eResizeEnds;
			break;
		case WM_PAINT:
			message.type = WindowMessageType::ePaint;
			break;
		case WM_CREATE:
			message.type = WindowMessageType::eCreate;
			break;
		case WM_DESTROY:
			message.type = WindowMessageType::eDestroy;
			break;
		case WM_KEYDOWN:
			message.type = WindowMessageType::eKeyDown;
			message.data.keyEvent.key = ConvertVirtualKey(aWParam);
			// Bit 0 - 15 is the repeat count
			message.data.keyEvent.repeatCount = static_cast<int>(static_cast<uint16_t>(aLParam));
			if (message.data.keyEvent.repeatCount == 1)
			{
				PostMaster::Post(AnyKeyDownMessage(message.data.keyEvent.key));
			}
			PostMaster::Post(AnyKeyRepeatMessage(message.data.keyEvent.key, message.data.keyEvent.repeatCount));
			break;
		case WM_KEYUP:
			message.type = WindowMessageType::eKeyUp;
			message.data.keyEvent.key = ConvertVirtualKey(aWParam);
			PostMaster::Post(AnyKeyUpMessage(message.data.keyEvent.key));
			break;

		case WM_INPUT:
			ReadRawInput(aHwnd, aMessage, aWParam, aLParam);
			return true;

		case WM_MOUSEMOVE:
			message.type = WindowMessageType::eMouseMove;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			break;

		case WM_LBUTTONDOWN:
			message.type = WindowMessageType::eMouseButtonDown;
			message.data.mouseEvent.button = MouseButton::eLeft;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(LeftMouseButtonDownMessage(MouseButton::eLeft));
			PostMaster::Post(AnyMouseButtonDownMessage(MouseButton::eLeft));
			break;

		case WM_RBUTTONDOWN:
			message.type = WindowMessageType::eMouseButtonDown;
			message.data.mouseEvent.button = MouseButton::eRight;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(RightMouseButtonDownMessage(MouseButton::eRight));
			PostMaster::Post(AnyMouseButtonDownMessage(MouseButton::eRight));
			break;

		case WM_MBUTTONDOWN:
			message.type = WindowMessageType::eMouseButtonDown;
			message.data.mouseEvent.button = MouseButton::eMiddle;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(MiddleMouseButtonDownMessage(MouseButton::eMiddle));
			PostMaster::Post(AnyMouseButtonDownMessage(MouseButton::eMiddle));
			break;

		case WM_LBUTTONUP:
			message.type = WindowMessageType::eMouseButtonUp;
			message.data.mouseEvent.button = MouseButton::eLeft;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(LeftMouseButtonUpMessage(MouseButton::eLeft));
			PostMaster::Post(AnyMouseButtonUpMessage(MouseButton::eLeft));
			break;

		case WM_RBUTTONUP:
			message.type = WindowMessageType::eMouseButtonUp;
			message.data.mouseEvent.button = MouseButton::eRight;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(RightMouseButtonUpMessage(MouseButton::eRight));
			PostMaster::Post(AnyMouseButtonUpMessage(MouseButton::eRight));
			break;

		case WM_MBUTTONUP:
			message.type = WindowMessageType::eMouseButtonUp;
			message.data.mouseEvent.button = MouseButton::eMiddle;
			ProcessMouseMoveData(message, static_cast<int>(GET_X_LPARAM(aLParam)), static_cast<int>(GET_Y_LPARAM(aLParam)));
			PostMaster::Post(MiddleMouseButtonUpMessage(MouseButton::eMiddle));
			PostMaster::Post(AnyMouseButtonUpMessage(MouseButton::eMiddle));
			break;

		case WM_DROPFILES:
			{
				HDROP hDropInfo = (HDROP)aWParam;
				wchar_t sItem[MAX_PATH];
				std::string PathOfFile;

				for (int i = 0; DragQueryFile(hDropInfo, i, (LPWSTR)sItem, sizeof(sItem)); i++)
				{
					const std::wstring tempPathOfFileDropped(sItem);
					const std::string tempPath(tempPathOfFileDropped.begin(), tempPathOfFileDropped.end());

					PathOfFile = tempPath;
					message.data.FileDropEvent.myFilePath = &PathOfFile;

					
					if (GetFileAttributes(sItem) &FILE_ATTRIBUTE_DIRECTORY)
					{
						message.data.FileDropEvent.myFileExtension = FileExtensionsEnum::eFolder;
					}
					else if (tempPath.find('.') != std::string::npos)
					{
						size_t tempFolderPart = tempPath.find_last_of('.') + 1;

						if (tempFolderPart < tempPath.length())
						{
							const std::string temp = tempPath.substr(tempFolderPart);

							FileExtensionsEnum tempFileExtension = FileEndingFindEnum(temp);

							if (tempFileExtension == FileExtensionsEnum::eNotUsed)
							{
								continue;
							}

							message.data.FileDropEvent.myFileExtension = tempFileExtension;
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}

					message.type = WindowMessageType::eFileDrop;
					PostMaster::Post(message);
				}

				

				
				DragFinish(hDropInfo);
			}
			break;

		case WM_SETFOCUS:
			myHasFocus = true;
			break;

		case WM_KILLFOCUS:
			myHasFocus = false;
			break;

		default:
			memset(&message, 0, sizeof(message));
			break;
		}

		myMessageQueue.push(message);
		return false;
	}

	void WindowsWindow::ReadRawInput(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
	{
		UINT dwSize;

		GetRawInputData(reinterpret_cast<HRAWINPUT>(aLParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));

		LPBYTE lpb = new BYTE[dwSize];
		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(aLParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
		{
			Engine::GetLogger().LogError("GetRawInputData did not return the correct size!");
		}

		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			PostMaster::Post(RawMouseMoveMessage(static_cast<int>(raw->data.mouse.lLastX), static_cast<int>(raw->data.mouse.lLastY)));
		}

		delete[] lpb;
	}

	void WindowsWindow::SetCursorConfined(bool aIsCursorConfined)
	{
		//myIsCursorConfined = aIsCursorConfined;
		myCursor->SetConfinedState(aIsCursorConfined);
	}

	bool WindowsWindow::IsCursorConfined() const
	{
		//return myIsCursorConfined;
		return myCursor->IsConfined();
	}

	void WindowsWindow::SetCursorHidden(bool aIsHidden)
	{
		myCursor->ShouldBeHidden(aIsHidden);
	}

	bool WindowsWindow::IsCursorHidden() const
	{
		return myCursor->IsHidden();
	}

	KeyboardKey WindowsWindow::ConvertVirtualKey(const WPARAM& aVirtualKey)
	{
		switch (aVirtualKey)
		{
		case 0x30:
			return KeyboardKey::eNum0;
		case 0x31:
			return KeyboardKey::eNum1;
		case 0x32:
			return KeyboardKey::eNum2;
		case 0x33:
			return KeyboardKey::eNum3;
		case 0x34:
			return KeyboardKey::eNum4;
		case 0x35:
			return KeyboardKey::eNum5;
		case 0x36:
			return KeyboardKey::eNum6;
		case 0x37:
			return KeyboardKey::eNum7;
		case 0x38:
			return KeyboardKey::eNum8;
		case 0x39:
			return KeyboardKey::eNum9;
		case 0x41:
			return KeyboardKey::eA;
		case 0x42:
			return KeyboardKey::eB;
		case 0x43:
			return KeyboardKey::eC;
		case 0x44:
			return KeyboardKey::eD;
		case 0x45:
			return KeyboardKey::eE;
		case 0x46:
			return KeyboardKey::eF;
		case 0x47:
			return KeyboardKey::eG;
		case 0x48:
			return KeyboardKey::eH;
		case 0x49:
			return KeyboardKey::eI;
		case 0x4A:
			return KeyboardKey::eJ;
		case 0x4B:
			return KeyboardKey::eK;
		case 0x4C:
			return KeyboardKey::eL;
		case 0x4D:
			return KeyboardKey::eM;
		case 0x4E:
			return KeyboardKey::eN;
		case 0x4F:
			return KeyboardKey::eO;
		case 0x50:
			return KeyboardKey::eP;
		case 0x51:
			return KeyboardKey::eQ;
		case 0x52:
			return KeyboardKey::eR;
		case 0x53:
			return KeyboardKey::eS;
		case 0x54:
			return KeyboardKey::eT;
		case 0x55:
			return KeyboardKey::eU;
		case 0x56:
			return KeyboardKey::eV;
		case 0x57:
			return KeyboardKey::eW;
		case 0x58:
			return KeyboardKey::eX;
		case 0x59:
			return KeyboardKey::eY;
		case 0x5A:
			return KeyboardKey::eZ;
		case VK_F1:
			return KeyboardKey::eF1;
		case VK_F2:
			return KeyboardKey::eF2;
		case VK_F3:
			return KeyboardKey::eF3;
		case VK_F4:
			return KeyboardKey::eF4;
		case VK_F5:
			return KeyboardKey::eF5;
		case VK_F6:
			return KeyboardKey::eF6;
		case VK_F7:
			return KeyboardKey::eF7;
		case VK_F8:
			return KeyboardKey::eF8;
		case VK_F9:
			return KeyboardKey::eF9;
		case VK_F10:
			return KeyboardKey::eF10;
		case VK_F11:
			return KeyboardKey::eF11;
		case VK_F12:
			return KeyboardKey::eF12;
		case VK_ESCAPE:
			return KeyboardKey::eEscape;
		case VK_RETURN:
			return KeyboardKey::eReturn;
		case VK_SPACE:
			return KeyboardKey::eSpace;
		case VK_CONTROL:
			return KeyboardKey::eControl;
		case VK_SHIFT:
			return KeyboardKey::eShift;
		case VK_LEFT:
			return KeyboardKey::eLeft;
		case VK_RIGHT:
			return KeyboardKey::eRight;
		case VK_UP:
			return KeyboardKey::eUp;
		case VK_DOWN:
			return KeyboardKey::eDown;
		case VK_LMENU:
			return KeyboardKey::eAlt;
		default:
			return KeyboardKey::eNone;
		}
	}

	void WindowsWindow::LateParseMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
	{
		switch (aMessage)
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			SetCapture(myHandle);
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			SetCapture(nullptr);
			break;
		}
	}

	void WindowsWindow::Update()
	{
		if (myCursor->IsConfined() == true && myHasFocus == true)
		{
			RECT clientRect,
				innerRect;
			GetClientRect(myHandle, &clientRect);
			POINT topLeft = { clientRect.left, clientRect.top };
			POINT bottomRight = { clientRect.right, clientRect.bottom };
			ClientToScreen(myHandle, &topLeft);
			ClientToScreen(myHandle, &bottomRight);

			innerRect.left = topLeft.x;
			innerRect.top = topLeft.y;
			innerRect.right = bottomRight.x;
			innerRect.bottom = bottomRight.y;

			ClipCursor(&innerRect);
		}
		else
		{
			ClipCursor(nullptr);
		}

		bool showCursor = myCursor->IsHidden() == false || myHasFocus == false;
		if (showCursor == false)
		{
			while (ShowCursor(false) >= 0);
		}
		else
		{
			while (ShowCursor(true) <= 1);
		}

	}
}

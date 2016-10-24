#pragma once
#include "Engine\Window\Window.h"
#include <queue>
#include <Windows.h>
#include "Engine\Window\WindowMessage.h"
#undef GetMessage

namespace ENGINE_NAMESPACE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();
		~WindowsWindow();

		virtual void SetTitle(const std::string &aTitle) override;

		virtual bool CanResize() const override;

		virtual void SetSize(const Size<int> &aSize) override;
		virtual bool PollMessage(WindowMessage & aMessage) override;

		virtual void Open() override;

		virtual bool IsOpen() const override;

		virtual void Close() override;

		virtual void SetVisible(bool aIsVisible) override;

		virtual void * GetHandle() const override;

		bool RequestFocus() override;
		bool HasFocus() const override;

		void ProcessMouseMoveData(WindowMessage & aMessage, int aX, int aY);
		bool ReceiveMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam);
		void ReadRawInput(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam);

		void SetCursorConfined(bool aIsCursorConfined) override;
		bool IsCursorConfined() const override;

		void SetCursorHidden(bool aIsHidden) override;
		bool IsCursorHidden() const override;

	private:
		static KeyboardKey ConvertVirtualKey(const WPARAM & aVirtualKey);
		void LateParseMessage(HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam);
		void Update();

		HWND myHandle;
		bool myIsOpen;
		bool myHasFocus;
		WNDCLASSEX myWindowClass;
		std::queue<WindowMessage> myMessageQueue;
		WindowMessage myPreviousMouseMoveMessage;
		bool myIsCursorConfined;
		bool myIsCursorHidden;
	};
}

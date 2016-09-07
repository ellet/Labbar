#pragma once


class CHUGWindowsWindow
{
public:
	CHUGWindowsWindow();
	~CHUGWindowsWindow();

	void Init(const CU::Vector2i aWindowSize = CU::Vector2i(1024, 600), const std::string & anApplicationName = "Default Name", const int aWindowShowState = SW_SHOWNORMAL);

	void Update();

	//static LRESULT CALLBACK HandleWindowsMessage(int aWindowHandle, UINT aMessage, WPARAM wParam, LPARAM lParam);

private:
	void RegisterWindow(const std::string & aClassName);

	int myWindowHandle;
};
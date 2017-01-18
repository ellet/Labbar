#pragma once
#include <tga2d/Engine.h>
#include <fstream>
#include "GameWorld.h"

class InputCallback;

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);

	static void RegisterInputCallback(InputCallback & aCallback);
	static void UnregisterInputCallback(InputCallback & aCallback);

private:
	static SB::KeyboardKey ConvertVirtualKey(const WPARAM& aVirtualKey);
	static SB::GrowingArray<InputCallback *> ourInputCallbacks;

	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitCallBack();
	void UpdateCallBack(const float aDeltaTime);
	void LogCallback(std::string aText);

	CGameWorld myGameWorld;

};

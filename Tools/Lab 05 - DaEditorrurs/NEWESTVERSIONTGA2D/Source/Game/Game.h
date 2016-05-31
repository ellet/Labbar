#pragma once
#include <tga2d/Engine.h>
#include <fstream>
#include "GameWorld.h"


class CGame
{
public:
	CGame();
	~CGame();
	bool Init(/*const std::wstring& aVersion = L"",*/ HWND aHWND = nullptr);
private:
	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	CGameWorld myGameWorld;
	std::ofstream myFileOutput;

};

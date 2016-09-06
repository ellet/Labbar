#pragma once
#include <tga2d/Engine.h>

class CGameWorld;

class CGame
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");
private:
	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	void SingletonInit();

	CGameWorld * myGameWorld;


};

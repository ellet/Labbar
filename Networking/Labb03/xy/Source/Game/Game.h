#pragma once
#include <tga2d/Engine.h>
#include "..\CommonUtilites\TimerManager.h"
#include <memory>


class CGameWorld;
class Client;


class CGame
{
public:
	CGame();
	~CGame();
	void Init();
private:
	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	std::unique_ptr<CGameWorld> myGameWorld;
	CommonUtilities::TimerManager myTimerManager;
	std::unique_ptr<Client> myClient;
};

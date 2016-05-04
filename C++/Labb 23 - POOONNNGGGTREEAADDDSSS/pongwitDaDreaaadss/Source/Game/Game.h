#pragma once
#include <tga2d/Engine.h>
#include "GameWorld.h"
#include <../CommonUtilities/TimeManager.h>
#include <thread>
#include <mutex>

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

	void UpdateThread(std::mutex * aUpdateLock, std::mutex * aDoneUpdateLock);
	void DoUpdate();
	void DoDraw();

	void DrawThread(std::mutex * aDrawLock, std::mutex * aDoneDrawLock);

	CGameWorld myGameWorld;
	TimeManager myTimeManager;

	volatile bool imUpdating;
	volatile bool imRendering;

	std::thread * myUpdateThread;
	std::thread * myDrawThread;

	std::mutex myUpdateLock;
	std::mutex myDrawLock;

	std::mutex myDoneUpdateLock;
	std::mutex myDoneDrawLock;
};

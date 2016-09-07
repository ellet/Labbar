#include "stdafx.h"
#include "HUGEngine.h"
#include "Windows/HUGWindowsWindow.h"

CHUGEngineSingleton * CHUGEngineSingleton::ourInstance = nullptr;

void CHUGEngineSingleton::Create()
{
	ourInstance = new CHUGEngineSingleton();
}

void CHUGEngineSingleton::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
}

void CHUGEngineSingleton::Init(EngineParameters & someParameters)
{
	GetInstance().myShouldRun = true;

	GetInstance().myWindowsWindow = new CHUGWindowsWindow();
	GetInstance().myWindowsWindow->Init(someParameters.myWindowSize, someParameters.myApplicationName);
	GetInstance().myGameUpdateFunction = someParameters.myGameUpdateFunction;

	GetInstance().EngineLoop();
}

void CHUGEngineSingleton::CloseGame()
{
	GetInstance().myShouldRun = false;
}

CHUGEngineSingleton::CHUGEngineSingleton()
{
}

CHUGEngineSingleton::~CHUGEngineSingleton()
{
}

CHUGEngineSingleton & CHUGEngineSingleton::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "HUG Engine singleton instance is nullptr!");
	return *ourInstance;
}

void CHUGEngineSingleton::EngineLoop()
{
	while (GetInstance().myShouldRun == true)
	{
		myWindowsWindow->Update();

		//Game Update
		GetInstance().myGameUpdateFunction();
	}
}

void CHUGEngineSingleton::CreateWindowsWindow()
{
	myWindowsWindow = new CHUGWindowsWindow();
}


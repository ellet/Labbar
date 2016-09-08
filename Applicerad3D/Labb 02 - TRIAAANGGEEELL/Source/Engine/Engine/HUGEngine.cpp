#include "stdafx.h"
#include "HUGEngine.h"
#include "Windows/HUGWindowsWindow.h"
#include "HUGFramework/HUGDXFramework.h"

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

	GetInstance().myFramework->Init(GetInstance().myWindowsWindow->GetHWND(), someParameters.myWindowSize);

	GetInstance().EngineLoop();
}

void CHUGEngineSingleton::CloseGame()
{
	GetInstance().myShouldRun = false;
}

CHUGEngineSingleton::CHUGEngineSingleton()
{
	myFramework = new CHUGDXFramework();
}

CHUGEngineSingleton::~CHUGEngineSingleton()
{
	SAFE_DELETE(myFramework);
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
		GetInstance().myFramework->CleanFrame();

		myWindowsWindow->Update();

		//Game Update
		GetInstance().myGameUpdateFunction();
		//Game Render
		//Render
		

		GetInstance().myFramework->Present();
	}
}

void CHUGEngineSingleton::CreateWindowsWindow()
{
	myWindowsWindow = new CHUGWindowsWindow();
}


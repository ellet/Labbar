#include "stdafx.h"
#include "HUGEngine.h"
#include "Windows/HUGWindowsWindow.h"
#include "HUGFramework/HUGDXFramework.h"
#include "Camera/HUGCamera.h"

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
	GetInstance().myGameInitFunction = someParameters.myGameInitFunction;
	GetInstance().myGameUpdateFunction = someParameters.myGameUpdateFunction;
	GetInstance().myGameRenderFunction = someParameters.myGameRenderFunction;

	GetInstance().myFramework->Init(GetInstance().myWindowsWindow->GetHWND(), someParameters.myWindowSize);

	GetInstance().myGameInitFunction();

	GetInstance().EngineLoop();
}

void CHUGEngineSingleton::ResizeWindow(const CU::Vector2ui aNewWindowSize)
{
	GetInstance().GetFramework().UpdateViewportSize(aNewWindowSize);
}

void CHUGEngineSingleton::CloseGame()
{
	GetInstance().myShouldRun = false;
}

CHUGDXFramework & CHUGEngineSingleton::GetFramework()
{
	return *GetInstance().myFramework;
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

		GetInstance().myGameUpdateFunction();
		GetInstance().myGameRenderFunction();		

		GetInstance().myFramework->Present();
	}
}

void CHUGEngineSingleton::CreateWindowsWindow()
{
	myWindowsWindow = new CHUGWindowsWindow();
}




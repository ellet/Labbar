#include "stdafx.h"
#include "HUGEngine.h"
#include "Windows/HUGWindowsWindow.h"
#include "HUGFramework/HUGDXFramework.h"
#include "Model/ModelManager/HUGModelManager.h"
#include "Camera/HUGCameraManager.h"

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
	GetInstance().myCameraManager->CreateCamera(someParameters.myWindowSize.y, someParameters.myWindowSize.x, { 0.f, 0.0f, -1.5f }, M_PI_2);

	GetInstance().myGameInitFunction();

	GetInstance().EngineLoop();
}

void CHUGEngineSingleton::ResizeWindow(const CU::Vector2ui aNewWindowSize)
{
	GetInstance().GetFramework().UpdateViewportSize(aNewWindowSize);
	GetInstance().GetCameraManager().UpdateProjections(aNewWindowSize);
}

void * CHUGEngineSingleton::GetHWND()
{
	return GetInstance().myWindowsWindow->GetHWND();
}

void CHUGEngineSingleton::CloseGame()
{
	GetInstance().myShouldRun = false;
}

CHUGDXFramework & CHUGEngineSingleton::GetFramework()
{
	return *GetInstance().myFramework;
}

CHUGCameraManager & CHUGEngineSingleton::GetCameraManager()
{
	return *GetInstance().myCameraManager;
}

CDXModel & CHUGEngineSingleton::GetModel(const std::string & aFilePath)
{
	return GetInstance().myModelManager->CreateModel(aFilePath);
}

CDXModel & CHUGEngineSingleton::GetModel()
{
	return GetInstance().myModelManager->CreateCube();
}

CHUGEngineSingleton::CHUGEngineSingleton()
{
	myFramework = new CHUGDXFramework();
	myModelManager = new CHUGModelManager();
	myCameraManager = new CHUGCameraManager();
}

CHUGEngineSingleton::~CHUGEngineSingleton()
{
	SAFE_DELETE(myFramework);
	SAFE_DELETE(myModelManager);
}

CHUGEngineSingleton & CHUGEngineSingleton::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "HUG Engine singleton instance is nullptr!");
	return *ourInstance;
}

void CHUGEngineSingleton::EngineLoop()
{
	while (myShouldRun == true)
	{
		myFramework->CleanFrame();

		myWindowsWindow->Update();

		myGameUpdateFunction();
		myGameRenderFunction();		

		myFramework->Present();
	}
}

void CHUGEngineSingleton::CreateWindowsWindow()
{
	myWindowsWindow = new CHUGWindowsWindow();
}


#include "stdafx.h"
#include <Game/Game.h>
#include <Engine/HUGEngine.h>

void HandleInArgument(const std::string & aStringToHandle)
{
	DL_Debug::Debug::GetInstance()->ActivateFilterlog(aStringToHandle);
}


int main(int argc, char* argv[])
{
	CU::MainSingleton::Create();
	DL_Debug::Debug::Create();
	CU::TimeManager::Create();

	for (int iArgument = 1; iArgument < argc; iArgument++)
	{
		HandleInArgument(argv[iArgument]);
	}

	GET_INPUT.Initialize();
	//DL_Debug::Debug::GetInstance()->ActivateFilterlog("Resource");

	CHUGEngineSingleton::Create();

	CHUGEngineSingleton::EngineParameters engineSettings;
	engineSettings.myApplicationName = "Pretty Application";
	engineSettings.myWindowSize = CU::Vector2ui(1920, 1080);
	
	//Debug::Create(L"Custom_Folder_Containing_Debug_Logs");
	//DL_PRINT("This is a text printed by DL_PRINT");
	int blaha = 8;
	float derpDerp = 1.f;
	std::string thisString = "Apa";
	//DL_DEBUG("This is a debug message printed by DL_DEBUG - Tests:   int : %i   float:  %f  string: %s   ", blaha, derpDerp, thisString.c_str());

	RESOURCE_LOG("This is a debug message printed by DL_DEBUG - Tests:   int : %i   float:  %f  string: %s   ", blaha, derpDerp, thisString.c_str());

	CGame game;
	//std::placeholders make something for Time for Game Update
	std::function<void(void)> gameInit = std::bind<void>(&CGame::Init, &game);
	engineSettings.myGameInitFunction = gameInit;
	std::function<void(void)> gameUpdate = std::bind<void>(&CGame::Update, &game);
	engineSettings.myGameUpdateFunction = gameUpdate;
	std::function<void(void)> gameRender = std::bind<void>(&CGame::Render, &game);
	engineSettings.myGameRenderFunction = gameRender;

	
	CHUGEngineSingleton::Init(engineSettings);


	CHUGEngineSingleton::Destroy();
	return 0;
}
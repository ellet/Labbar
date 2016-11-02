#include "stdafx.h"
#include <Game/Game.h>
#include <Engine/HUGEngine.h>
#include "CU/Utility/CommandLineManager/CommandLineManager.h"

void HandleInArgument(const std::string & aStringToHandle)
{
	DL_Debug::Debug::GetInstance()->ActivateFilterlog(aStringToHandle);
}


int main(int argc, char* argv[])
{
	CU::MainSingleton::Create();
	DL_Debug::Debug::Create();
	CU::TimeManager::Create();

	CU::GrowingArray<std::string>tempInput;
	tempInput.Init(argc - 1);

	for (int iArgument = 1; iArgument < argc; iArgument++)
	{
		tempInput.Add(argv[iArgument]);
	}

	CU::CommandLine::ParseCommandLines(tempInput);

	GET_INPUT.Initialize();
	DL_Debug::Debug::GetInstance()->ActivateFilterlog("Resource");
	DL_Debug::Debug::GetInstance()->ActivateFilterlog("Engine");

	CHUGEngineSingleton::Create();

	CHUGEngineSingleton::EngineParameters engineSettings;
	engineSettings.myApplicationName = "Pretty Application";
	engineSettings.myWindowSize = CU::Vector2ui(1920, 1080);

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
#include "stdafx.h"
#include <Game/Game.h>
#include <Engine/HUGEngine.h>

int main()
{
	CU::MainSingleton::Create();
	DL_Debug::Debug::Create();
	CU::TimeManager::Create();

	GET_INPUT.Initialize();

	CHUGEngineSingleton::Create();

	CHUGEngineSingleton::EngineParameters engineSettings;
	engineSettings.myApplicationName = "Pretty Application";
	engineSettings.myWindowSize = CU::Vector2ui(800, 600);
	
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
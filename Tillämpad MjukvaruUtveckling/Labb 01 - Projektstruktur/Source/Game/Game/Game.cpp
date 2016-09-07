#include "stdafx.h"
#include "Game/Game.h"
#include <Engine/HUGEngine.h>

CGame::CGame()
{
}


CGame::~CGame()
{
}

void CGame::Init()
{
	CHUGEngineSingleton::Create();

	CHUGEngineSingleton::EngineParameters engineSettings;
	engineSettings.myApplicationName = "";
	engineSettings.myWindowSize = CU::Vector2i(800, 600);

	//std::placeholders make something for Time for Game Update
	std::function<void(void)> gameUpdate = std::bind<void>(&CGame::Update, this);
	engineSettings.myGameUpdateFunction = gameUpdate;

	CHUGEngineSingleton::Init(engineSettings);

	CHUGEngineSingleton::Destroy();
}

void CGame::Update()
{
	//std::cout << "derp" << std::endl;
}

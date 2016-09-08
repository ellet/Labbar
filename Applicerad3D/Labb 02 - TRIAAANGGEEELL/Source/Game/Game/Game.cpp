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
	myModel.Init();
}

void CGame::Update()
{
}

void CGame::Render()
{
	myModel.Render();
}

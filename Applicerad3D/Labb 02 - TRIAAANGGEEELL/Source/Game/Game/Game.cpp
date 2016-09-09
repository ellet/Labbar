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
	myQuad.InitAsQuad();
	myTriangle.InitAsTriangle();
}

void CGame::Update()
{
}

void CGame::Render()
{
	myQuad.Render();
	myTriangle.Render();
}

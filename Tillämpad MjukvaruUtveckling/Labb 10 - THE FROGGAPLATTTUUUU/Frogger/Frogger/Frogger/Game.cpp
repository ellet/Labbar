#include "StdAfx.h"
#include "Game.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"
#include "LevelDataHandler.h"

FG::Game::Game()
{
}

FG::Game::~Game()
{
    MainSingleton::GetInstance()->Destroy();
}

void FG::Game::Init(HGE* aHGE)
{
	myHGE = aHGE;
    MainSingleton::Create(myHGE);

	myGameHasStarted = false;
	myGameOverFlag = false;
	myPlayAgainFlag = false;
	myGameOverScreenTimer = 2.0f;

    myFrog.Init(myHGE);

    myWorld.Init(&myFrog);    
    myScoreHandler.Init(&myFrog);
    myTimeHandler.Init(&myFrog);

	myWorld.LoadLevel(LEVEL1);
}
    
bool FG::Game::Update()
{
	if(myGameHasStarted)
	{
		MainSingleton::GetInstance()->GetTimeManager()->Update();
		myFrog.Update();
		myWorld.Update();
		myScoreHandler.Update();
		myTimeHandler.Update();

		CheckForWinLooseConditions();
	}
	else
	{
		if(myHGE->Input_GetKeyState(HGEK_SPACE))
		{
			myGameHasStarted = true;
		}

		if(HandlePlayAgain() == false)
		{
			return false;
		}
	}

    Render();    
    return true;
}

bool FG::Game::HandlePlayAgain()
{
	if(myGameOverFlag)
	{
		myGameOverScreenTimer -= static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());
		if(myGameOverScreenTimer <= 0)
		{
			myPlayAgainFlag = true;
			myGameOverFlag = false;
			myGameOverScreenTimer = 2.0f;
		}
	}

	if(myPlayAgainFlag)
	{
		if(myHGE->Input_GetKeyState(HGEK_Y))
		{	
			myWorld.LoadLevel(LEVEL1);
			myGameHasStarted = true;
			myPlayAgainFlag = false;
			myFrog.ResetFrog();
			myScoreHandler.ReInit();
			myTimeHandler.ResetTime();

		}
		if(myHGE->Input_GetKeyState(HGEK_N))
		{
			return false;
		}
	}

	return true;
}

void FG::Game::CheckForWinLooseConditions()
{
	if(myFrog.GetNumberOfLives() <= 0)
    {
		myGameOverFlag = true;
		myGameHasStarted = false;
	}

	if(myScoreHandler.LevelCompleted())
	{
		CompleteLevel();
	}
}

void FG::Game::CompleteLevel()
{
    myScoreHandler.ReInit();
    myTimeHandler.ResetTime();
    myFrog.Respawn();
    myWorld.LoadLevel(LEVEL2);
}

void FG::Game::Render()
{
    myHGE->Gfx_BeginScene();
	myHGE->Gfx_Clear(0);

	if(myGameOverFlag)
	{
		MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(GAME_OVER_SPRITE)->Render(0,0);
	}
	else if(myPlayAgainFlag)
	{
		MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(PLAY_AGAIN_SPRITE)->Render(0,0);
	}
	else
	{
		if(myGameHasStarted)
		{
			myWorld.Render();
			myFrog.Render();
			myScoreHandler.Render();
			myTimeHandler.Render();
		}
		else
		{
			MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(MAIN_MENU_SPRITE)->Render(0,0);
		}
	}

    myHGE->Gfx_EndScene();
}

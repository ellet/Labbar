#include "StdAfx.h"
#include "Game.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"
#include "LevelDataHandler.h"
#include "Renderer.h"
#include "GiefThreadNAme.h"
#include "PhysicsManager.h"

FG::Game::Game()
{
	myStopRunning = false;
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

	myRenderThread = new std::thread(&Game::Render, this);
	myPhysicsThread = new std::thread(&Game::Physics, this);
}
	
bool FG::Game::Update()
{
	if(myGameHasStarted)
	{
		MainSingleton::GetInstance()->GetTimeManager()->Update();
		myFrog.Update();
		myWorld.Update();
		//MainSingleton::GetInstance()->GetPhysicsManager().Update();
		MainSingleton::GetInstance()->GetPhysicsManager().SwitchBuffers();

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




	UpdateRender();

	

	MainSingleton::GetInstance()->GetRenderer().ChangeBuildBuffer();


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
	SetThreadName("Render");
	//Sleep(10);

	while (myStopRunning == false)
	{

		myHGE->Gfx_BeginScene();
		myHGE->Gfx_Clear(0);

		

		MainSingleton::GetInstance()->GetRenderer().Render();
		MainSingleton::GetInstance()->GetRenderer().ChangeRenderBuffer();

		myHGE->Gfx_EndScene();
	}
}

void FroggerGame::Game::Shutdown()
{
	myStopRunning = true;

	myRenderThread->join();
}

void FroggerGame::Game::Physics()
{
	SetThreadName("Physics");
	//Sleep(10);

	while (myStopRunning == false)
	{

		MainSingleton::GetInstance()->GetPhysicsManager().Update();
	}
}

void FroggerGame::Game::UpdateRender()
{
	if (myGameOverFlag)
	{
		//MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(GAME_OVER_SPRITE)->Render(0, 0);
		MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(GAME_OVER_SPRITE), CommonUtilities::Vector2f(0.f, 0.f));
	}
	else if (myPlayAgainFlag)
	{
		//MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(PLAY_AGAIN_SPRITE)->Render(0, 0);
		MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(PLAY_AGAIN_SPRITE), CommonUtilities::Vector2f(0.f, 0.f));
	}
	else
	{
		if (myGameHasStarted)
		{
			myWorld.Render();
			myFrog.Render();
			myScoreHandler.Render();
			myTimeHandler.Render();
		}
		else
		{
			//MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(MAIN_MENU_SPRITE)->Render(0, 0);
			MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(MAIN_MENU_SPRITE), CommonUtilities::Vector2f(0.f, 0.f));
		}
	}
}

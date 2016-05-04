#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/text/text.h>
#include <tga2d/primitives/custom_shape.h>
#include <tga2d/math/color.h>

#include <InputWrapper\InputWrapper.h>

//using namespace DX2D;
CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::ResetGame()
{
	myPlayer1Score = 0;
	myPlayer2Score = 0;
	myPlayer1.SetPosition(0.05f, 0.5f);
	myPlayer2.SetPosition(0.9f, 0.5f);
	myBall.Reset();
	myGameState = eGameState::ePlaying;
}

void CGameWorld::Init()
{	
	CommonUtilities::InputWrapper::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
	myText = new DX2D::CText("Text/calibril.ttf_sdf");
	myBall.Init();
	myPlayer1.Init(false, myBall);
	myPlayer2.Init(true, myBall);
	ResetGame();
}

void CGameWorld::Update(float aDeltaTime)
{ 
	CommonUtilities::InputWrapper::Update();
	PrintScores();

	switch (myGameState)
	{
	case eGameState::ePlaying:
		UpdateBall(aDeltaTime);
		myPlayer1.Update(aDeltaTime);
		myPlayer2.Update(aDeltaTime);
		CheckGameOverState();
		break;
	case eGameState::eGameOver:
		if (CommonUtilities::InputWrapper::GetKeyDown(DIK_SPACE) == true)
		{
			ResetGame();
			myGameState = eGameState::ePlaying;
		}
		break;
	}
	Render();
}

void CGameWorld::PrintScores()
{
	PrintText(0.05f, 0.1f, "Player 1");
	PrintText(0.05f, 0.15f, std::to_string(myPlayer1Score).c_str());

	PrintText(0.8f, 0.1f, "Player 2");
	PrintText(0.8f, 0.15f, std::to_string(myPlayer2Score).c_str());
}

void CGameWorld::CheckGameOverState()
{
	if (myPlayer1Score >= 3 || myPlayer2Score >= 3)
	{
		myGameState = eGameState::eGameOver;
	}
}

void CGameWorld::UpdateBall(const float aDeltaTime)
{
	myBall.Update(aDeltaTime);
	if (myBall.GetPosition().x <= 0)
	{
		myBall.Reset();
		myPlayer2Score++;
	}
	else if (myBall.GetPosition().x >= 1)
	{
		myBall.Reset();
		myPlayer1Score++;
	}

	if (myPlayer1.Collides(myBall) == true ||
		myPlayer2.Collides(myBall) == true)
	{
		myBall.ReverseDirection();
	}
}

void CGameWorld::Render()
{
	myBall.Draw();
	myPlayer1.Draw();
	myPlayer2.Draw();

	if (myGameState == eGameState::eGameOver)
	{
		PrintText(0.4f, 0.5f, "GAME OVER");
		PrintText(0.3f, 0.55f, "Press SPACE to restart");
		if (myPlayer1Score >= 3)
		{
			PrintText(0.4f, 0.6f, "Player 1 won");
		}
		else
		{
			PrintText(0.4f, 0.6f, "Player 2 won");
		}
	}
}

void CGameWorld::PrintText(const float aX, const float aY, const char* aText)
{
	myText->myPosition.Set(aX, aY);
	myText->myText = aText;
	myText->Render();
}
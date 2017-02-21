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

#include "GameObject.h"
#include "InputComponent.h"
#include "AIComponent.h"
#include "InputUiComponent.h"

using namespace DX2D;
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
	myPlayer1->myPosition.Set(0.05f, 0.5f);
	myPlayer2->myPosition.Set(0.9f, 0.5f);
	myBall.Reset();
	myGameState = eGameState::ePreGame;
}

void CGameWorld::Init()
{	


	myInputWrapper.Init(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND(),
		DX2D::CEngine::GetInstance()->GetWindowSize().x, DX2D::CEngine::GetInstance()->GetWindowSize().y);
	myText = new DX2D::CText("Text/calibril.ttf_sdf");
	myBall.Init();


	myPlayer1 = new CGameObject();
	myPlayer1->CreateComponent<CPaddleComponent>()->Init();
	myPlayer1->CreateComponent<CInputComponent>()->Init(&myInputWrapper);
	myPlayer2 = new CGameObject();
	myPlayer2->CreateComponent<CPaddleComponent>()->Init();
	myPlayer2->CreateComponent<CAIComponent>()->Init(&myBall); // Create network comntroller instead?

	myIpUi = new CGameObject();
	myIpUi->CreateComponent<CInputUiComponent>()->Init(&myInputWrapper, std::bind(&CGameWorld::OnIpEntered, this, std::placeholders::_1));

	ResetGame();
}

void CGameWorld::OnIpEntered(std::string aIP)
{
	myIpUi->GetComponent<CInputUiComponent>()->Reset();
	myGameState = eGameState::ePlaying;
}

void CGameWorld::Update(float aDeltaTime)
{ 
	myInputWrapper.Update();
	PrintScores();

	switch (myGameState)
	{
	case eGameState::ePlaying:
		UpdateBall(aDeltaTime);
		myPlayer1->Update(aDeltaTime);
		myPlayer2->Update(aDeltaTime);
		CheckGameOverState();
		break;
	case eGameState::ePreGame:
		myIpUi->Update(aDeltaTime);
		break;
	case eGameState::eGameOver:
		if (myInputWrapper.GetKeyDown(DIK_SPACE) == true)
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

	if (myPlayer1->GetComponent<CPaddleComponent>()->Collides(myBall) == true ||
		myPlayer2->GetComponent<CPaddleComponent>()->Collides(myBall) == true)
	{
		myBall.ReverseDirection();
	}
}

void CGameWorld::Render()
{
	myBall.Render();
	myPlayer1->Render();
	myPlayer2->Render();

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
	else if (myGameState == eGameState::ePreGame)
	{
		myIpUi->Render();
	}
}

void CGameWorld::PrintText(const float aX, const float aY, const char* aText)
{
	myText->myPosition.Set(aX, aY);
	myText->myText = aText;
	myText->Render();
}

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

#include <GameCode/Components/InputComponent.h>
#include <GameCode/Components/AIComponent.h>
#include <GameCode/Components/InputUiComponent.h>
#include "GameCode/GameObject/GameObject.h"
#include "Messages/NetworkCallback.h"
#include "GameCode/Components/RenderComponent.h"
#include "GameCode/Components/NetworkComponent.h"
#include "Messages/CreateGameObjectMessage.h"
#include "Messages/SyncGameObjectMessage.h"
#include "Messages/CreateDummyNetMessage.h"
#include "Messages/GameStateNetMessage.h"
#include "Messages/ScoreNetMessage.h"

using namespace DX2D;
CGameWorld::CGameWorld()
{
	myPlayer1 = nullptr;
	myPlayer2 = nullptr;
	myBallObject = nullptr;
	myBall = nullptr;
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::ResetGame()
{
	myPlayer1Score = 0;
	myPlayer2Score = 0;

	if (myPlayer1 != nullptr)
	{
		myPlayer1->myPosition.Set(0.05f, 0.5f);
	}
	
	if (myPlayer2 != nullptr)
	{
		myPlayer2->myPosition.Set(0.9f, 0.5f);
	}

	GameStateNetMessage playgame = myClientCallback->myMessageManager.CreateMessage<GameStateNetMessage>();
	playgame.myGameState = eGameState::ePlaying;
	myClientCallback->SendMesseageFromWorld(playgame);
}

void CGameWorld::Init(NetworkCallback & aClientCallback)
{	
	myClientCallback = &aClientCallback;
	myInputWrapper.Init(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND(),
		DX2D::CEngine::GetInstance()->GetWindowSize().x, DX2D::CEngine::GetInstance()->GetWindowSize().y);
	myText = new DX2D::CText("Text/calibril.ttf_sdf");
	

	myIpUi = new CGameObject();
	myIpUi->CreateComponent<CInputUiComponent>()->Init(&myInputWrapper, std::bind(&CGameWorld::OnIpEntered, this, std::placeholders::_1));

	myPlayer1Score = 0;
	myPlayer2Score = 0;

	myGameState = eGameState::ePreGame;
}

void CGameWorld::CreatePlayer(CGameObject & PlayerToCreate)
{
	PlayerToCreate.CreateComponent<CInputComponent>()->Init(&myInputWrapper);
	PlayerToCreate.CreateComponent<RenderComponent>();
	PlayerToCreate.CreateComponent<NetworkComponent>()->SetCallback(*myClientCallback);
	PlayerToCreate.GetComponent<RenderComponent>()->LoadSprite("sprites/paddle.png");
}

void CGameWorld::OnIpEntered(std::string aIp)
{
	myIpUi->GetComponent<CInputUiComponent>()->Reset();
	myGameState = eGameState::ePlaying;

	myClientCallback->Connect(aIp, "Bertil");
}

void CGameWorld::Update(float aDeltaTime)
{ 
	myInputWrapper.Update();
	PrintScores();

	

	switch (myGameState)
	{
	case eGameState::ePlaying:
		if (myPlayer1 == nullptr)
		{
			return;
		}
		myPlayer1->Update(aDeltaTime);
		
		break;
	case eGameState::ePreGame:
		myIpUi->Update(aDeltaTime);
		break;
	case eGameState::eGameOver:
		if (myInputWrapper.GetKeyDown(DIK_SPACE) == true)
		{
			ResetGame();
		}
		break;
	}
}

void CGameWorld::PrintScores()
{
	PrintText(0.05f, 0.1f, "Player 1");
	PrintText(0.05f, 0.15f, std::to_string(myPlayer1Score).c_str());

	PrintText(0.8f, 0.1f, "Player 2");
	PrintText(0.8f, 0.15f, std::to_string(myPlayer2Score).c_str());
}

void CGameWorld::Render()
{
	if (myBallObject != nullptr)
	{
		myBallObject->Render();
	}

	if (myPlayer1 != nullptr)
	{
		myPlayer1->Render();
	}

	if (myPlayer2 != nullptr)
	{
		myPlayer2->Render();
	}

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
	else
	{
		PrintText(0.f, 0.f, "");
		PrintText(0.f, 0.f, "");
		PrintText(0.f, 0.f, "");
	}
}

void CGameWorld::RecieveMessage(CreateGameObjectMessage & aMessageToHandle)
{
	if (aMessageToHandle.myType == GameObjectTypes::ePaddle)
	{
		myPlayer1 = new CGameObject();
		CreatePlayer(*myPlayer1);
		myPlayer1->myID = aMessageToHandle.myID;
	}
	else if (aMessageToHandle.myType == GameObjectTypes::eBall)
	{
		
	}

}

void CGameWorld::RecieveMessage(SyncGameObjectMessage & aMessage)
{
	if (myPlayer1 == nullptr)
	{
		return;
	}

	DX2D::Vector2f position(aMessage.X, aMessage.Y);

	if (myBallObject != nullptr && myBallObject->myID == aMessage.objectID)
	{
		myBallObject->myPosition = position;
	}
	else if (myPlayer1->myID == aMessage.objectID)
	{
		myPlayer1->myPosition = position;
	}
	else if (myPlayer2 != nullptr && myPlayer2->myID == aMessage.objectID)
	{
		myPlayer2->myPosition = position;
	}
	else
	{
		//Error("could not find object with ID" + std::to_string(aMessage.objectID));
	}

}

void CGameWorld::RecieveMessage(CreateDummyNetMessage & aMessageToHandle)
{
	if (aMessageToHandle.myObjectType == GameObjectTypes::eBall)
	{
		if (myBallObject == nullptr)
		{
			myBallObject = new class CGameObject;
			myBallObject->CreateComponent<RenderComponent>();
			myBallObject->GetComponent<RenderComponent>()->LoadSprite("sprites/ball.png");
			myBallObject->myID = aMessageToHandle.myGameObjectID;
		}
		else
		{
			//Error("ball already created");
		}
	}
	else if (aMessageToHandle.myObjectType == GameObjectTypes::ePaddle)
	{
		if (myPlayer2 == nullptr)
		{
			myPlayer2 = new class CGameObject;
			myPlayer2->CreateComponent<RenderComponent>();
			myPlayer2->GetComponent<RenderComponent>()->LoadSprite("sprites/paddle.png");
			myPlayer2->myID = aMessageToHandle.myGameObjectID;
		}
		else
		{
			//Error("Paddle already created");
		}
	}
}

void CGameWorld::RecieveMessage(GameStateNetMessage & aMessageToHandle)
{
	myGameState = aMessageToHandle.myGameState;
}

void CGameWorld::RecieveMessage(ScoreNetMessage & aMessage)
{
	if (aMessage.myIsPlayer1 == true)
	{
		myPlayer1Score = aMessage.myScore;
	}
	else
	{
		myPlayer2Score = aMessage.myScore;
	}
}

void CGameWorld::PrintText(const float aX, const float aY, const char* aText)
{
	myText->myPosition.Set(aX, aY);
	myText->myText = aText;
	myText->Render();
}

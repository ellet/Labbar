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

	
	//myBall->Reset();
	myGameState = eGameState::ePreGame;
}

void CGameWorld::Init(NetworkCallback & aClientCallback)
{	
	myClientCallback = &aClientCallback;
	myInputWrapper.Init(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND(),
		DX2D::CEngine::GetInstance()->GetWindowSize().x, DX2D::CEngine::GetInstance()->GetWindowSize().y);
	myText = new DX2D::CText("Text/calibril.ttf_sdf");

	


	myPlayer2 = new CGameObject();
	CreatePlayer(*myPlayer2);
	//myPlayer2->CreateComponent<CAIComponent>()->Init(myBall); // Create network comntroller instead?
	

	myIpUi = new CGameObject();
	myIpUi->CreateComponent<CInputUiComponent>()->Init(&myInputWrapper, std::bind(&CGameWorld::OnIpEntered, this, std::placeholders::_1));

	ResetGame();
}

void CGameWorld::CreatePlayer(CGameObject & PlayerToCreate)
{
	//PlayerToCreate.CreateComponent<CPaddleComponent>()->Init();
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
		//UpdateBall(aDeltaTime);
		myPlayer1->Update(aDeltaTime);
		/*myPlayer2->Update(aDeltaTime);
		CheckGameOverState();*/
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

//void CGameWorld::UpdateBall(const float aDeltaTime)
//{
//	//myBall.Update(aDeltaTime);
//	myBallObject->Update(aDeltaTime);
//	if (myBall->GetPosition().x <= 0)
//	{
//		myBall->Reset();
//		myPlayer2Score++;
//	}
//	else if (myBall->GetPosition().x >= 1)
//	{
//		myBall->Reset();
//		myPlayer1Score++;
//	}
//
//	if (myPlayer1->GetComponent<CPaddleComponent>()->Collides(*myBall) == true ||
//		myPlayer2->GetComponent<CPaddleComponent>()->Collides(*myBall) == true)
//	{
//		myBall->ReverseDirection();
//	}
//}

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
		myBallObject = new class CGameObject;
		myBallObject->CreateComponent<RenderComponent>();
		myBallObject->GetComponent<RenderComponent>()->LoadSprite("sprites/ball.png");
		myBallObject->myID = aMessageToHandle.myID;
	}

}

void CGameWorld::RecieveMessage(SyncGameObjectMessage & aMessage)
{
	DX2D::Vector2f position(aMessage.X, aMessage.Y);

	if (myBallObject != nullptr && myBallObject->myID == aMessage.objectID)
	{
		myBallObject->myPosition = position;
	}
	else if (myPlayer1 != nullptr && myPlayer1->myID == aMessage.objectID)
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

void CGameWorld::PrintText(const float aX, const float aY, const char* aText)
{
	myText->myPosition.Set(aX, aY);
	myText->myText = aText;
	myText->Render();
}

#include "stdafx.h"
#include "ServerWorld.h"
#include "..\TShared\GameCode\GameObject\GameObject.h"
#include "..\TShared\GameCode\Components\Ball.h"
#include "..\TShared\GameCode\Components\PaddleComponent.h"
#include "..\TShared\GameCode\Components\AIComponent.h"
#include "..\TShared\Messages\GameCodeNetMessage.h"
#include "..\TShared\Messages\NetworkCallback.h"
#include "..\TShared\Messages\CreateGameObjectMessage.h"
#include "..\TShared\Messages\SyncGameObjectMessage.h"


ServerWorld::ServerWorld()
{
	myPlayer1 = nullptr;
	myPlayer2 = nullptr;
	myBallObject = nullptr;
}


ServerWorld::~ServerWorld()
{
}

void ServerWorld::Init()
{
	
	
	myPlayer2 = new CGameObject();
	myPlayer2->CreateComponent<CPaddleComponent>()->Init();
	myPlayer2->CreateComponent<CAIComponent>()->Init(myBall); // Create network comntroller instead?
	//AddGameObject(myPlayer2);

}

void ServerWorld::Update(float aTimeDelta)
{
	switch (myGameState)
	{
	case eGameState::ePlaying:
		UpdateBall(aTimeDelta);
		myPlayer1->Update(aTimeDelta);
		//myPlayer2->Update(aDeltaTime);
		//CheckGameOverState();*/
		break;
	case eGameState::ePreGame:
		break;
	case eGameState::eGameOver:
		/*if (myInputWrapper.GetKeyDown(DIK_SPACE) == true)
		{
			ResetGame();
			myGameState = eGameState::ePlaying;
		}*/
		break;
	}

	if (myPlayer1 != nullptr)
	{
		SyncGameObject(myPlayer1);
	}
	if (myPlayer2 != nullptr)
	{
		SyncGameObject(myPlayer2);
	}
	if (myBallObject != nullptr)
	{
		SyncGameObject(myBallObject);
	}
}


void ServerWorld::HandleInputMessage(GameCodeNetMessage & aMessage)
{
	myPlayer1->BroadCastMessage(&aMessage.myGameMessage);
}




void ServerWorld::SetNetworkCallback(NetworkCallback & aCallback)
{
	myNetworkCallback = &aCallback;
}

void ServerWorld::OnConnect(const unsigned short aUserID)
{
	if (myPlayer1 == nullptr)
	{
		myPlayer1 = new CGameObject();
		myPlayer1->CreateComponent<CPaddleComponent>()->Init();
		myPlayer1->myUserID = aUserID;
		AddGameObject(myPlayer1, GameObjectTypes::ePaddle);

		SendCreationMessage(myPlayer1, GameObjectTypes::ePaddle, aUserID);
		if (myBallObject != nullptr)
		{
			SendCreationMessage(myBallObject, GameObjectTypes::eBall, aUserID);
		}

		if (myPlayer2 != nullptr)
		{
			SendCreationMessage(myPlayer2, GameObjectTypes::ePaddle, aUserID);
		}
	}
	//else if (myPlayer2 == nullptr)
	//{
	//	myPlayer2 = new CGameObject();
	//	myPlayer2->CreateComponent<CPaddleComponent>()->Init();
	//	myPlayer2->myUserID = aUserID;
	//	AddGameObject(myPlayer2, GameObjectTypes::ePaddle);

	//	SendCreationMessage(myPlayer2, GameObjectTypes::ePaddle, aUserID);
	//	if (myBallObject != nullptr)
	//	{
	//		SendCreationMessage(myBallObject, GameObjectTypes::eBall, aUserID);
	//	}
	//}
	//
	if (myGameState == eGameState::ePreGame /*&& myPlayer2 != nullptr*/)
	{
		StartGame();
	}
}

void ServerWorld::StartGame()
{
	myBallObject = new class CGameObject;

	myBall = myBallObject->CreateComponent<CBall>();
	myBall->Init();
	AddGameObject(myBallObject, GameObjectTypes::eBall);
	myBallObject->myUserID = globalServerID;
	
	if (myPlayer1 != nullptr)
	{
		SendCreationMessage(myBallObject, GameObjectTypes::eBall, myPlayer1->myUserID);
	}

	if (myPlayer2 != nullptr)
	{
		SendCreationMessage(myBallObject, GameObjectTypes::eBall, myPlayer2->myUserID);
	}

	ResetGame();
}

void ServerWorld::AddGameObject(CGameObject* aGameObecjt, const GameObjectTypes aObjectType)
{
	myGameObjects.push_back(aGameObecjt);
	myGameObjects.back()->myID = static_cast<unsigned short>(myGameObjects.size() - 1);
}

void ServerWorld::SendCreationMessage(CGameObject * aGameObject, const GameObjectTypes aObjectType, const unsigned short aToID)
{
	CreateGameObjectMessage createObjectMessage = myNetworkCallback->myMessageManager.CreateMessage<CreateGameObjectMessage>();
	createObjectMessage.myID = aGameObject->myID;
	createObjectMessage.myType = aObjectType;

	myNetworkCallback->myMessageManager.SetTargetID(aToID);
	myNetworkCallback->SendMesseageFromWorld(createObjectMessage);
}

void ServerWorld::SyncGameObject(CGameObject * aGameObject)
{
	SyncGameObjectMessage syncMessage = myNetworkCallback->myMessageManager.CreateMessage<SyncGameObjectMessage>();
	syncMessage.X = aGameObject->myPosition.x;
	syncMessage.Y = aGameObject->myPosition.y;
	syncMessage.objectID = aGameObject->myID;

	myNetworkCallback->BroadCastMessageFromWorld(syncMessage);
}

void ServerWorld::ResetGame()
{
	myPlayer1Score = 0;
	myPlayer2Score = 0;
	myPlayer1->myPosition.Set(0.05f, 0.5f);
	myPlayer2->myPosition.Set(0.9f, 0.5f);
	myBall->Reset();
	myGameState = eGameState::ePlaying;
}

void ServerWorld::UpdateBall(const float aDeltaTime)
{
	myBallObject->Update(aDeltaTime);
	if (myBall->GetPosition().x <= 0)
	{
		myBall->Reset();
		myPlayer2Score++;
	}
	else if (myBall->GetPosition().x >= 1)
	{
		myBall->Reset();
		myPlayer1Score++;
	}

	if (myPlayer1->GetComponent<CPaddleComponent>()->Collides(*myBall) == true ||
		myPlayer2->GetComponent<CPaddleComponent>()->Collides(*myBall) == true)
	{
		myBall->ReverseDirection();
	}
}

void ServerWorld::CheckGameOverState()
{
	if (myPlayer1Score >= 3 || myPlayer2Score >= 3)
	{
		myGameState = eGameState::eGameOver;
	}
}

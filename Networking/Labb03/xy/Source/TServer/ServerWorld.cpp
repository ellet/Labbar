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
#include <Messages\CreateDummyNetMessage.h>
#include "..\TShared\Messages\GameStateNetMessage.h"
#include "..\TShared\Messages\ScoreNetMessage.h"


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
}

void ServerWorld::Update(float aTimeDelta)
{
	if (myPlayer1 != nullptr)
	{
		myPlayer1->Update(aTimeDelta);
	}

	if (myPlayer2 != nullptr)
	{
		myPlayer2->Update(aTimeDelta);
	}
	

	switch (myGameState)
	{
	case eGameState::ePlaying:
		UpdateBall(aTimeDelta);
		
		CheckGameOverState();
		break;
	case eGameState::ePreGame:
		break;
	case eGameState::eGameOver:
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

	ScoreNetMessage player1Score = myNetworkCallback->myMessageManager.CreateMessage<ScoreNetMessage>();
	player1Score.myScore = myPlayer1Score;
	player1Score.myIsPlayer1 = true;

	myNetworkCallback->BroadCastMessageFromWorld(player1Score);

	ScoreNetMessage player2Score = myNetworkCallback->myMessageManager.CreateMessage<ScoreNetMessage>();
	player2Score.myScore = myPlayer2Score;
	player2Score.myIsPlayer1 = false;

	myNetworkCallback->BroadCastMessageFromWorld(player2Score);
}


void ServerWorld::HandleInputMessage(GameCodeNetMessage & aMessage)
{
	if (aMessage.GetSenderID() == myPlayer1->myUserID)
	{
		myPlayer1->BroadCastMessage(&aMessage.myGameMessage);
	}
	else if (aMessage.GetSenderID() == myPlayer2->myUserID)
	{
		myPlayer2->BroadCastMessage(&aMessage.myGameMessage);
	}
	else
	{
		Error("user id is not related to a player");
	}
}




void ServerWorld::HandleGameStateMessage(GameStateNetMessage & aMessage)
{
	if (aMessage.myGameState == eGameState::ePlaying && myGameState == eGameState::eGameOver)
	{
		ResetGame();
	}
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

		myPlayer1->myPosition.Set(0.05f, 0.5f);
		

		if (myBallObject != nullptr)
		{
			SendCreateDummyMessage(GameObjectTypes::eBall, myBallObject->myID, myPlayer1->myUserID);
		}

		if (myPlayer2 != nullptr)
		{
			SendCreateDummyMessage(GameObjectTypes::ePaddle, myPlayer2->myID, myPlayer1->myUserID);
		}
	
	}
	else if (myPlayer2 == nullptr)
	{
		myPlayer2 = new CGameObject();
		myPlayer2->CreateComponent<CPaddleComponent>()->Init();
		myPlayer2->myUserID = aUserID;
		AddGameObject(myPlayer2, GameObjectTypes::ePaddle);
		SendCreationMessage(myPlayer2, GameObjectTypes::ePaddle, aUserID);

		myPlayer2->myPosition.Set(0.9f, 0.5f);

		if (myBallObject != nullptr)
		{
			SendCreateDummyMessage(GameObjectTypes::eBall, myBallObject->myID, myPlayer2->myUserID);
		}		

		SendCreateDummyMessage(GameObjectTypes::ePaddle, myPlayer2->myID, myPlayer1->myUserID);

		SendCreateDummyMessage(GameObjectTypes::ePaddle, myPlayer1->myID, myPlayer2->myUserID);
	}

	if (myPlayer1 != nullptr && myPlayer2 != nullptr)
	{
		if (myPlayer1->myUserID == myPlayer2->myUserID)
		{
			Error("player1 and 2 have the same user");
		}
	}
	
	
	if (myGameState == eGameState::ePreGame && myPlayer2 != nullptr && myPlayer1 != nullptr)
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
		SendCreateDummyMessage(GameObjectTypes::eBall, myBallObject->myID, myPlayer1->myUserID);
	}

	if (myPlayer2 == nullptr)
	{
		CreateAI();
	}
	else
	{
		SendCreateDummyMessage(GameObjectTypes::eBall, myBallObject->myID, myPlayer2->myUserID);
	}

	ResetGame();
}

void ServerWorld::ChangeGameState(const eGameState aGameState)
{
	myGameState = aGameState;
	GameStateNetMessage newMessage = myNetworkCallback->myMessageManager.CreateMessage<GameStateNetMessage>();
	newMessage.myGameState = aGameState;

	myNetworkCallback->BroadCastMessageFromWorld(newMessage);
}

void ServerWorld::CreateAI()
{
	myPlayer2 = new CGameObject();
	AddGameObject(myPlayer2, GameObjectTypes::ePaddle);
	myPlayer2->myUserID = globalServerID;
	myPlayer2->CreateComponent<CPaddleComponent>()->Init();
	myPlayer2->CreateComponent<CAIComponent>()->Init(myBall);

	SendCreateDummyMessage(GameObjectTypes::ePaddle, myPlayer2->myID, myPlayer1->myUserID);
}

void ServerWorld::AddGameObject(CGameObject* aGameObecjt, const GameObjectTypes aObjectType)
{
	myGameObjects.push_back(aGameObecjt);
	myGameObjects.back()->myID = static_cast<unsigned short>(myGameObjects.size() - 1);
}

void ServerWorld::SendCreationMessage(CGameObject * aGameObject, const GameObjectTypes aObjectType, const unsigned short aToID)
{
	myNetworkCallback->myMessageManager.SetTargetID(aToID);
	CreateGameObjectMessage createObjectMessage = myNetworkCallback->myMessageManager.CreateMessage<CreateGameObjectMessage>();
	createObjectMessage.myID = aGameObject->myID;
	createObjectMessage.myType = aObjectType;

	
	myNetworkCallback->SendMesseageFromWorld(createObjectMessage);
}

void ServerWorld::SendCreateDummyMessage(const GameObjectTypes aType, const unsigned short aObjectID, const unsigned short aToID)
{
	myNetworkCallback->myMessageManager.SetTargetID(aToID);
	CreateDummyNetMessage dummy = myNetworkCallback->myMessageManager.CreateMessage<CreateDummyNetMessage>();
	dummy.myGameObjectID = aObjectID;
	dummy.myObjectType = aType;

	myNetworkCallback->SendMesseageFromWorld(dummy);
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
	ChangeGameState(eGameState::ePlaying);
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
		ChangeGameState(eGameState::eGameOver);
	}
}

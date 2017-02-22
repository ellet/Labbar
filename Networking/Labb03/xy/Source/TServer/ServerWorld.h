#pragma once
#include <GameCode\GameStates.h>
#include "..\TShared\GameCode\GameObjectTypes.h"
class CBall;
class CGameObject;
class GameCodeNetMessage;
class CreateGameObjectMessage;
class NetworkCallback;
class GameStateNetMessage;

class ServerWorld
{
public:
	ServerWorld();
	~ServerWorld();

	void Init();
	void Update(float aTimeDelta);

	void HandleInputMessage(GameCodeNetMessage & aMessage);
	void HandleGameStateMessage(GameStateNetMessage & aMessage);
	
	void SetNetworkCallback(NetworkCallback & aCallback);

	void OnConnect(const unsigned short aUserID);

private:
	void StartGame();
	void ChangeGameState(const eGameState aGameState);

	void CreateAI();

	void AddGameObject(CGameObject* aGameObecjt, const GameObjectTypes aObjectType);

	void SendCreationMessage(CGameObject * aGameObject, const GameObjectTypes aObjectType, const unsigned short aToID);
	void SendCreateDummyMessage(const GameObjectTypes aType, const unsigned short aObjectID,const unsigned short aToID);
	
	void SyncGameObject(CGameObject * aGameObject);

	void ResetGame();
	void UpdateBall(const float aDeltaTime);
	void CheckGameOverState();

	eGameState myGameState;

	CBall * myBall;
	class CGameObject* myBallObject;
	class CGameObject* myPlayer1;
	class CGameObject* myPlayer2;
	class CGameObject* myIpUi;

	std::vector<CGameObject*> myGameObjects;

	int myPlayer1Score;
	int myPlayer2Score;

	NetworkCallback * myNetworkCallback;
};


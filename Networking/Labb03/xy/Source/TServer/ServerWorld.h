#pragma once
#include <GameCode\GameStates.h>
#include "..\TShared\GameCode\GameObjectTypes.h"
class CBall;
class CGameObject;
class GameCodeNetMessage;
class CreateGameObjectMessage;
class NetworkCallback;

class ServerWorld
{
public:
	ServerWorld();
	~ServerWorld();

	void Init();
	void Update(float aTimeDelta);

	void HandleInputMessage(GameCodeNetMessage & aMessage);
	
	void SetNetworkCallback(NetworkCallback & aCallback);

	void OnConnect(const unsigned short aUserID);

private:
	void StartGame();

	void AddGameObject(CGameObject* aGameObecjt, const GameObjectTypes aObjectType);

	void SendCreationMessage(CGameObject * aGameObject, const GameObjectTypes aObjectType, const unsigned short aToID);
	
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


#pragma once
#include <vector>
#include "..\CommonUtilites\InputWrapper.h"
#include <GameCode\Components\Ball.h>
#include <GameCode\Components\PaddleComponent.h>
#include "GameCode\GameStates.h"
#include <functional>


namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
	
}

class CBall;
class Client;
class NetworkCallback;
class CreateGameObjectMessage;
class SyncGameObjectMessage;
class CreateDummyNetMessage;
class GameStateNetMessage;
class ScoreNetMessage;


class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init(NetworkCallback & aClientCallback);
	void Update(float aTimeDelta);
	void Render();

	void RecieveMessage(CreateGameObjectMessage & aMessageToHandle);
	void RecieveMessage(CreateDummyNetMessage & aMessageToHandle);
	void RecieveMessage(GameStateNetMessage & aMessageToHandle);
	void RecieveMessage(SyncGameObjectMessage & aMessage);
	void RecieveMessage(ScoreNetMessage & aMessage);

private:
	void CreatePlayer(CGameObject & PlayerToCreate);

	void OnIpEntered(std::string aIp);
	void PrintText(const float aX, const float aY, const char* aText);
	void ResetGame();
	
	void PrintScores();

	
	eGameState myGameState;

	CBall * myBall;
	class CGameObject* myBallObject;
	class CGameObject* myPlayer1;
	class CGameObject* myPlayer2;
	class CGameObject* myIpUi;
	int myPlayer1Score;
	int myPlayer2Score;
	DX2D::CText* myText;
	Input::InputWrapper myInputWrapper;
	NetworkCallback * myClientCallback;
	
};

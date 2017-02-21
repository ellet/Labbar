#pragma once
#include <vector>
#include "..\CommonUtilites\InputWrapper.h"
#include "Ball.h"
#include "PaddleComponent.h"

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
}

enum class eGameState
{
	ePreGame,
	ePlaying,
	eGameOver
};

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
private:
	void OnIpEntered(std::string aIP);
	void PrintText(const float aX, const float aY, const char* aText);
	void UpdateGameOverState();
	void UpdatePlayingState();
	void ResetGame();
	void Render();
	void UpdateBall(const float aDeltaTime);
	void CheckGameOverState();
	void PrintScores();

	eGameState myGameState;

	CBall myBall;
	class CGameObject* myPlayer1;
	class CGameObject* myPlayer2;
	class CGameObject* myIpUi;
	int myPlayer1Score;
	int myPlayer2Score;
	DX2D::CText* myText;	
	Input::InputWrapper myInputWrapper;

	
};
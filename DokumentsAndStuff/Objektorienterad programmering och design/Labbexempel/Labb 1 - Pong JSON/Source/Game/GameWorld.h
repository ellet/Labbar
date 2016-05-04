#pragma once

#include "..\CommonUtilites\InputWrapper.h"
#include "Ball.h"
#include "Paddle.h"

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
}

enum class eGameState
{
	eMainMenu,
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
	void PrintText(const float aX, const float aY, const char* aText);
	void UpdateGameOverState();
	void UpdatePlayingState();
	void ResetGame();
	void Render();
	void UpdateBall(const float aDeltaTime);
	void CheckGameOverState();
	void PrintScores();

	eGameState myGameState;

	Ball myBall;
	Paddle myPlayer1;
	Paddle myPlayer2;
	int myPlayer1Score;
	int myPlayer2Score;
	DX2D::CText* myText;	
	Input::InputWrapper myInputWrapper;
	std::vector<DX2D::CSprite*> myMainMenuSprites;
	
};
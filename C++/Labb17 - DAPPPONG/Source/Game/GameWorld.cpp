#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <Macros.h>
#include <sstream>


//using namespace DX2D;
CGameWorld::CGameWorld()
{
	myGameObjects.resize(static_cast<size_t>(enumGameObjects::enumLength));
	myLeftSideScore = 0;
	myRightSideScore = 0;
	myPlayerHasWonBool = false;
	
	myScoreText = nullptr;
	myTestPointer = nullptr;
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myScoreText);
	SAFE_DELETE(myTestPointer);
}

void CGameWorld::Init()
{
	myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].Init("sprites/paddle.png");
	myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetPosition(0.1f, 0.1f);

	myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].Init("sprites/paddle.png");
	myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetPosition(0.9f, 0.1f);

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].Init("sprites/ball.png");
	ResetBall();
	
	
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetUseFriciton(false);
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetClampToScreen(true);

	myScoreText = new DX2D::CText("Text/calibril.ttf_sdf");
	myScoreText->myText = "0 - 0";
	myScoreText->myPosition = DX2D::Vector2f(0.5f, 0.02f);
	myScoreText->myColor.Set(1, 1, 1, 1.0f);
	myScoreText->mySize = 0.4f;

	myTestPointer = new DX2D::CText("Text/calibril.ttf_sdf");
	myTestPointer->myText = "test stuff";
	myTestPointer->myPosition = DX2D::Vector2f(0.5f, 0.4f);
	myTestPointer->myColor.Set(1, 1, 1, 1.0f);
	myTestPointer->mySize = 0.4f;

	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));
}


void CGameWorld::Update(float aTimeDelta)
{ 
	myInput.Update();
	
	std::ostringstream ScoreTextMaker;

	if (myPlayerHasWonBool == false)
	{
		if (myInput.GetKeyDown(DIK_DOWNARROW))
		{
			myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetMovement(270);//, 0.003f);
		}

		if (myInput.GetKeyDown(DIK_UPARROW))
		{
			myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetMovement(90);//, 0.003f);
		}

		if (myInput.GetKeyDown(DIK_S))
		{
			myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetMovement(270);//, 0.003f);
		}

		if (myInput.GetKeyDown(DIK_W))
		{
			myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetMovement(90);//, 0.003f);
		}

		for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
		{
			myGameObjects[iGameObjects].Update(aTimeDelta);
		}

		const size_t TempBallIndex = static_cast<size_t>(enumGameObjects::eBall);
		for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
		{
			if (iGameObjects != TempBallIndex)
			{
				myGameObjects[TempBallIndex].CheckCollision(myGameObjects[iGameObjects].GetCollisionRectangle());
			}
		}

		if (myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].GetPostion().x > 1.f)
		{
			myLeftSideScore += 1;
			ResetBall();
		}
		else if (myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].GetPostion().x < 0.f)
		{
			myRightSideScore += 1;
			ResetBall();
		}

		if (myLeftSideScore > 2 || myRightSideScore > 2)
		{
			myPlayerHasWonBool = true;
		}
		
		ScoreTextMaker << myLeftSideScore;
		ScoreTextMaker << " - ";
		ScoreTextMaker << myRightSideScore;
	}
	else
	{
		if (myLeftSideScore > 2)
		{
			ScoreTextMaker << "Left side player has won";
		}
		else
		{
			ScoreTextMaker << "Right side player has won";
		}

		if (myInput.GetKeyPressed(DIK_RETURN))
		{
			myLeftSideScore = 0;
			myRightSideScore = 0;
			myPlayerHasWonBool = false;
		}
	}

	if (myInput.GetKeyPressed(DIK_1))
	{
		myTestPointer->myText = "Test 1";
		myTestPointer->Render();
	}

	if (myInput.GetKeyPressed(DIK_2))
	{
		myTestPointer->myText = "Test 2";
		myTestPointer->Render();
	}

	if (myInput.GetKeyPressed(DIK_3))
	{
		myTestPointer->myText = "Test 3";
		myTestPointer->Render();
	}

	myScoreText->myText = ScoreTextMaker.str();
}

void CGameWorld::Draw()
{
	for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
	{
		myGameObjects[iGameObjects].Draw();
	}

	//myScoreText->Render();
}

void CGameWorld::ResetBall()
{
	const int leftOrRight = (rand() % 2);
	float randomAngle = static_cast<float>(rand() % 90);
	int randomPosition = (rand() % 75);

	if (randomPosition <= 50)
	{
		randomPosition += 25;
	}

	const float normalizedPosition = static_cast<float>(randomPosition) / 100.f;

	if (leftOrRight == 0)
	{
		randomAngle += 135.f;
	}
	else
	{
		randomAngle += 315.f;
	}

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetPosition(0.5f, normalizedPosition);
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetMovement(randomAngle, 0.35f, true);
}
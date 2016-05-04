#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <tga2d/sprite/sprite.h>
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
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myScoreText);

	SAFE_DELETE(myBackground);

	delete[] mySprites;
	mySprites = nullptr;
}

void CGameWorld::Init()
{
	myRecursionLevel = 3;

	//myGameObjects[static_cast<size_t>(enumGameObjects::eBackGround)].Init("sprites/test.png", true);
	//myGameObjects[static_cast<size_t>(enumGameObjects::eBackGround)].SetPosition(0.1f, 0.1f);

	myBackground = new DX2D::CSprite("sprites/test.png");

	myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].Init("sprites/paddle.png", enumGameObjects::eFirstPaddle, true);
	myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetPosition(0.1f, 0.1f);

	myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].Init("sprites/paddle.png", enumGameObjects::eSecondPadde, true);
	myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetPosition(0.9f - myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].GetScale().x, 0.1f);

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].Init("sprites/ball.png", enumGameObjects::eBall, true);
	ResetBall();
	
	//mySprites = new DX2D::CSprite[static_cast<size_t>(pow((static_cast<float>(enumGameObjects::enumLength)), myRecursionLevel))];
	size_t objectCount = 0;
	size_t tempRecursionLevel = myRecursionLevel;
	
	for (; tempRecursionLevel > 0; --tempRecursionLevel)
	{
		objectCount += static_cast<size_t>(pow((static_cast<float>(enumGameObjects::enumLength)), tempRecursionLevel));
	}
		

	mySprites = new DX2D::CSprite[objectCount];
	
	for (size_t iGameObject = 0; iGameObject < objectCount; ++iGameObject)
	{
		mySprites[iGameObject] = DX2D::CSprite("sprites/test.png");
	}

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetUseFriciton(false);
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetClampToScreen(true);

	myScoreText = new DX2D::CText("Text/calibril.ttf_sdf");
	myScoreText->myText = "0 - 0";
	myScoreText->myPosition = DX2D::Vector2f(0.5f, 0.02f);
	myScoreText->myColor.Set(1, 1, 1, 1.0f);
	myScoreText->mySize = 0.4f;


	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));
}


void CGameWorld::Update(float aTimeDelta)
{ 
	myInput.Update();
	
	std::ostringstream ScoreTextMaker;

	if (myPlayerHasWonBool == false)
	{
#pragma region Input

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

#pragma endregion

		const size_t TempBallIndex = static_cast<size_t>(enumGameObjects::eBall);
		for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
		{
			if (iGameObjects != TempBallIndex)
			{
				if (myGameObjects[TempBallIndex].CheckCollision(myGameObjects[iGameObjects].GetCollisionRectangle()))
				{
					//myGameObjects[iGameObjects].DoCollision();
				}
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

	myScoreText->myText = ScoreTextMaker.str();
}

void CGameWorld::Draw()
{
	myBackground->Render();

	size_t spritesUsed = 0;

	for (size_t iWorldObjects = 0; iWorldObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iWorldObjects)
	{
		const DX2D::Vector4f CurrentWorldScale = DrawWorldBackgroundInObject(myGameObjects[iWorldObjects], mySprites[spritesUsed], DX2D::Vector4f(0.f, 0.f, 1.f, 1.f));
		++spritesUsed;

		for (size_t iGoingDeeperObjects = 0; iGoingDeeperObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGoingDeeperObjects)
		{
			const DX2D::Vector4f DeeperWorldScale = DrawWorldBackgroundInObject(myGameObjects[iGoingDeeperObjects], mySprites[spritesUsed], CurrentWorldScale);
			++spritesUsed;

			for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
			{
				DrawSpriteInOtherWorld(myGameObjects[iGameObjects], myGameObjects[iGoingDeeperObjects], mySprites[spritesUsed], DeeperWorldScale);
				++spritesUsed;
			}
		}

		myGameObjects[iWorldObjects].Draw();
	}

	for (size_t iGameObject = 0; iGameObject <= spritesUsed ; ++iGameObject)
	{
		mySprites[iGameObject].Render();
	}

	myScoreText->Render();
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

DX2D::Vector4f CGameWorld::DrawWorldBackgroundInObject(const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw, DX2D::Vector4f aWorldScale)
{
	DX2D::Vector2ui discardWorldSize = aWorldToDrawIn.GetMySprite().GetImageSize();
	DX2D::Vector2f worldSize = DX2D::Vector2f(static_cast<float>(discardWorldSize.x), static_cast<float>(discardWorldSize.y));

	DX2D::Vector2ui discardSpriteSize = myBackground->GetImageSize();
	DX2D::Vector2f spriteSize = DX2D::Vector2f(static_cast<float>(discardSpriteSize.x), static_cast<float>(discardSpriteSize.y));

	DX2D::Vector2f spriteScaleNeeded = DX2D::Vector2f((worldSize.x / spriteSize.x), (worldSize.y / spriteSize.y));
	spriteScaleNeeded.x *= aWorldScale.z;
	spriteScaleNeeded.y *= aWorldScale.w;
	//spriteSize = DX2D::Vector2f(spriteSize.x * spriteScaleNeeded.x, spriteSize.y * spriteScaleNeeded.y);

	DX2D::Vector2f worldPosition = aWorldToDrawIn.GetPostion();
	worldPosition.x = aWorldScale.x + (worldPosition.x * aWorldScale.z);
	worldPosition.y = aWorldScale.y + (worldPosition.y * aWorldScale.w);

	aSpriteToDraw.SetSize(spriteScaleNeeded);
	aSpriteToDraw.SetPosition(worldPosition);
	return DX2D::Vector4f(worldPosition.x, worldPosition.y, spriteScaleNeeded.x, spriteScaleNeeded.y);
}



void CGameWorld::DrawSpriteInOtherWorld(const GameObject & aObjectToDraw, const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw, DX2D::Vector4f aWorldScale)
{
	DX2D::Vector2ui worldSize = aWorldToDrawIn.GetMySprite().GetImageSize();
	DX2D::Vector2ui objectSpriteSize = aObjectToDraw.GetMySprite().GetImageSize();
	DX2D::Vector2ui spriteSize = myBackground->GetImageSize();

	DX2D::Vector2f objectSpriteSizef(static_cast<float>(objectSpriteSize.x), static_cast<float>(objectSpriteSize.y));
	DX2D::Vector2f spriteSizef(static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y));


	DX2D::Vector2f scaleToSetSprite(((objectSpriteSizef.x / spriteSizef.x) * 1.f), ((objectSpriteSizef.y / spriteSizef.y) * 1.f));
	spriteSizef = DX2D::Vector2f(spriteSizef.x * scaleToSetSprite.x, spriteSizef.y * scaleToSetSprite.y);

	DX2D::Vector2f worldSizef(static_cast<float>(worldSize.x), static_cast<float>(worldSize.y));


	//DX2D::Vector2f aWorldScale = aWorldToDrawIn.GetScale();
	DX2D::Vector2f ScaleToDraw = aObjectToDraw.GetScale();

	ScaleToDraw.x *= aWorldScale.z;
	ScaleToDraw.y *= aWorldScale.w;
	
	//DX2D::Vector2f sizeOfChild(((spriteSizef.x / worldSizef.x) * ScaleToDraw.x), ((spriteSizef.y / worldSizef.y) * ScaleToDraw.y));

	aSpriteToDraw.SetSize(ScaleToDraw);

	const DX2D::Vector2f positionOfObject = aObjectToDraw.GetPostion();
	const DX2D::Vector2f thisWorldZero = DX2D::Vector2f(aWorldScale.x, aWorldScale.y);
	

	DX2D::Vector2f PositionToSet(thisWorldZero.x + (positionOfObject.x * aWorldScale.z), thisWorldZero.y + (positionOfObject.y * aWorldScale.w));

	aSpriteToDraw.SetPosition(PositionToSet);
}



//void CGameWorld::DrawSpriteInOtherWorld(const GameObject & aObjectToDraw, const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw, DX2D::Vector2f aWorldScale)
//{
//	DX2D::Vector2ui worldSize = aWorldToDrawIn.GetMySprite().GetImageSize();
//	DX2D::Vector2ui objectSpriteSize = aObjectToDraw.GetMySprite().GetImageSize();
//	DX2D::Vector2ui spriteSize = myBackground->GetImageSize();
//
//	DX2D::Vector2f objectSpriteSizef(static_cast<float>(objectSpriteSize.x), static_cast<float>(objectSpriteSize.y));
//	DX2D::Vector2f spriteSizef(static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y));
//	
//	
//	DX2D::Vector2f scaleToSetSprite(((objectSpriteSizef.x / spriteSizef.x) * 1.f), ((objectSpriteSizef.y / spriteSizef.y) * 1.f));
//	spriteSizef = DX2D::Vector2f(spriteSizef.x * scaleToSetSprite.x, spriteSizef.y * scaleToSetSprite.y);
//
//	DX2D::Vector2f worldSizef(static_cast<float>(worldSize.x), static_cast<float>(worldSize.y));
//	
//
//	DX2D::Vector2f ScaleToDraw = aObjectToDraw.GetScale();
//
//	ScaleToDraw.x *= aWorldScale.x;
//	ScaleToDraw.y *= aWorldScale.y; 
//	DX2D::Vector2f sizeOfChild(((spriteSizef.x / worldSizef.x) * ScaleToDraw.x), ((spriteSizef.y / worldSizef.y) * ScaleToDraw.y));
//
//	aSpriteToDraw.SetSize(sizeOfChild);
//
//	const DX2D::Vector2f positionOfObject = aObjectToDraw.GetPostion();
//	const DX2D::Vector2f thisWorldZero = aWorldToDrawIn.GetPostion();
//
//	DX2D::Vector2f PositionToSet(thisWorldZero.x + (positionOfObject.x * aWorldScale.x), thisWorldZero.y + (positionOfObject.y * aWorldScale.y));
//
//	aSpriteToDraw.SetPosition(PositionToSet);
//}
#pragma once
#include "GameObjects\GameObject.h"
#include <../CommonUtilities/InputWrapper.h>
#include <vector>

namespace DX2D
{
	class CText;
	class CSpriteBatch;
	class CSprite;
}



class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();
	void Init();
	void Update(float aTimeDelta);
	void Draw();

private:

	//DX2D::Vector4f DrawWorldBackgroundInObject(const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw, DX2D::Vector4f aWorldScale);

	//void DrawSpriteInOtherWorld(const GameObject & aObjectToDraw, const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw, DX2D::Vector4f aWorldScale);
	//void DrawSpriteInOtherWorld(const GameObject & aObjectToDraw, const GameObject & aWorldToDrawIn, DX2D::CSprite & aSpriteToDraw);
	void SetSprites(const GameObject & aObjectToDraw, DX2D::Vector4f aWorldData, unsigned int aDepth);
	void FancyFunction();

	void ResetBall();

	std::vector<GameObject> myGameObjects;
	
	size_t myLeftSideScore;
	size_t myRightSideScore;

	DX2D::CText* myScoreText;
	DX2D::CSprite* mySprites;
	DX2D::CSprite* myBackground;

	size_t myRecursionLevel;

	InputWrapper myInput;

	unsigned int mySpriteID;

	bool myPlayerHasWonBool;
};
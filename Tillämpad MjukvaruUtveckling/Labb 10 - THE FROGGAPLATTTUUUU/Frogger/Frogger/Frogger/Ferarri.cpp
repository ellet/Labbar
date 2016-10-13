#include "StdAfx.h"
#include "Ferarri.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::Ferarri::Ferarri()
{
}

FG::Ferarri::~Ferarri()
{
}

void FG::Ferarri::Init(CU::Vector2f aPosition, float aSpeed)
{
	Vehicle::Init(aPosition, FERARRI);

	mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(FERARRI_SPRITE);
	myDirection = CU::Vector2i(-1,0);

	myMovementSpeed = aSpeed;

	myWidth = 2;
}

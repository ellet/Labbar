#include "StdAfx.h"
#include "Car.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::Car::Car()
{
}

FG::Car::~Car()
{
}

void FG::Car::Init(CU::Vector2f aPosition, float aSpeed)
{
	Vehicle::Init(aPosition, CAR);

	mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(CAR_SPRITE);
	myDirection = CU::Vector2i(-1,0);

	myMovementSpeed = aSpeed;

	myWidth = 2;
}

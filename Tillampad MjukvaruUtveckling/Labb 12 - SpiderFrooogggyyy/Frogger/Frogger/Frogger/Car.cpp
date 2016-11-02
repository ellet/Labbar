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
	//myDirection = CU::Vector2i(-1,0);

	//myMovementSpeed = aSpeed;

	SetVelocity(CommonUtilities::Vector2f(-1.f * aSpeed, 0.f * aSpeed));


//	myWidth = 2;
	SetSize(CommonUtilities::Vector2f(32.f * 2.f, 32.f));
}

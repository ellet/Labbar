#include "StdAfx.h"
#include "Truck.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::Truck::Truck()
{
}

FG::Truck::~Truck()
{
}

void FG::Truck::Init(CU::Vector2f aPosition, float aSpeed)
{
	Vehicle::Init(aPosition, TRUCK);

	mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(TRUCK_SPRITE);
	//myDirection = CU::Vector2i(1,0);

	//myMovementSpeed = aSpeed;

	SetVelocity(CommonUtilities::Vector2f(1.f * aSpeed, 0.f * aSpeed));

	//myWidth = 3;
	SetSize(CommonUtilities::Vector2f(32.f * 3.f, 32.f));
}

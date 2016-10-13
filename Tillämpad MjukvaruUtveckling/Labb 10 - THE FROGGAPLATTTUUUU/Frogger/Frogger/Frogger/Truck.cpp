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
	myDirection = CU::Vector2i(1,0);

	myMovementSpeed = aSpeed;

	myWidth = 3;
}

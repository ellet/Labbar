#include "StdAfx.h"
#include "Bus.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::Bus::Bus()
{
}

FG::Bus::~Bus()
{
}

void FG::Bus::Init(CU::Vector2f aPosition, float aSpeed)
{
	Vehicle::Init(aPosition, BUS);

	mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(BUS_SPRITE);
	//myDirection = CU::Vector2i(-1,0);

	//myMovementSpeed = aSpeed;

	SetVelocity(CommonUtilities::Vector2f(-1.f * aSpeed, 0.f * aSpeed));


	//myWidth = 4;
	SetSize(CommonUtilities::Vector2f(32.f * 4.f, 32.f));
}

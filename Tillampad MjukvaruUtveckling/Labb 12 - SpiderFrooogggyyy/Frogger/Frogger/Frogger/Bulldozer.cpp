#include "StdAfx.h"
#include "Bulldozer.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"
#include "Renderer.h"

FG::Bulldozer::Bulldozer()
{
}

FG::Bulldozer::~Bulldozer()
{
}

void FG::Bulldozer::Init(CU::Vector2f aPosition, float aSpeed)
{
	Vehicle::Init(aPosition, BULLDOZER); 
	mySprites[0] = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(BULLDOZER1_SPRITE);
	mySprites[1] = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(BULLDOZER2_SPRITE);
	mySprite = mySprites[0];
	//myDirection = CU::Vector2i(1,0);

	//myMovementSpeed = aSpeed;

	SetVelocity(CommonUtilities::Vector2f(1.f * aSpeed, 0.f * aSpeed));


	mySpriteTimer = 0.1f;

	myCurrentSprite = 0;

	//myWidth = 2;
	SetSize(CommonUtilities::Vector2f(32.f * 2.f, 32.f));
}

void FG::Bulldozer::Update()
{
	Vehicle::Update();

	mySpriteTimer -= myDeltaTime;
	if(mySpriteTimer <= 0)
	{
		myCurrentSprite ^= 1;
		mySpriteTimer = 0.1f;
	}
}

void FG::Bulldozer::Render()
{
	//mySprites[myCurrentSprite]->Render(myPosition.myX, myPosition.myY);
	MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*mySprites[myCurrentSprite], GetPosition());
}

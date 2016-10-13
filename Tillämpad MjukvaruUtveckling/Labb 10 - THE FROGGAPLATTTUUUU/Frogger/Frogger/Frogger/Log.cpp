#include "StdAfx.h"
#include "Log.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::Log::Log()
{
}

FG::Log::~Log()
{
}

void FG::Log::Init(CU::Vector2f aPosition, WaterEntityTypes aWaterEntityType, float aSpeed)
{
	if(aWaterEntityType == SMALL_LOG)
    {
        mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(LOG_SMALL_SPRITE);
	    myLength = 3;
    }
    if(aWaterEntityType == MEDIUM_LOG)
    {
        mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(LOG_MEDIUM_SPRITE);
	    myLength = 4;
    }
    if(aWaterEntityType == BIG_LOG)
    {
        mySprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(LOG_LARGE_SPRITE);
	    myLength = 5;
    }

	myWidth = myLength * 32.0f;
    WaterEntity::Init(aPosition, aWaterEntityType);

	myDirection = CU::Vector2i(1,0); 
	myMovementSpeed = aSpeed;
}

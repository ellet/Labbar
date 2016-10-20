#include "StdAfx.h"
#include "Turtle.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"
#include "Renderer.h"

FG::Turtle::Turtle()
{
}

FG::Turtle::~Turtle()
{
}

void FG::Turtle::Init(CU::Vector2f aPosition, WaterEntityTypes aWaterEntityType, bool aIsSubmerging, float aSpeed)
{
	mySprites[0] = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(TURTLE_SPRITE);
    mySprites[1] = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(TURTLE_SUB1_SPRITE);
    mySprites[2] = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(TURTLE_SUB2_SPRITE);
	mySprite = mySprites[0];

    myCurrentSprite = 0;
    myIsSubmerging = aIsSubmerging;   
    myIsCurrentlyDiving = false;

	SetVelocity(CommonUtilities::Vector2f(-1.f * aSpeed, 0.f * aSpeed));
	mySubmergeTime = 2.0f;

    if(aWaterEntityType == BIG_TURTLE)
    {
	    myLength = 3;
    }
    else
    {
	    myLength = 2;
    }

	//myWidth = 32.0f * myLength;
	SetSize(CommonUtilities::Vector2f( 32.0f * myLength, 32.f));
	WaterEntity::Init(aPosition, aWaterEntityType);

    mySubmergeTimer = mySubmergeTime;
    mySubmergeAnimationTime = 1.0f;
}

void FG::Turtle::ReInit()
{
    switch(rand() % 2)
    {                    
        case 0: myIsSubmerging = true; break;
        case 1: myIsSubmerging = false; break;
    }

    myCurrentSprite = 0;

    WaterEntity::ReInit();
}

void FG::Turtle::Update()
{
	WaterEntity::Update();

    if(myIsSubmerging)
    {
        HandleSubmerge();
    }
}

void FG::Turtle::HandleSubmerge()
{
    if(myIsCurrentlyDiving == false)
    {
        mySubmergeTimer -= myDeltaTime;
        if(mySubmergeTimer <= 0)
        {         
            myIsCurrentlyDiving = true;
            mySubmergeTimer = mySubmergeTime;
        }
    }

    Submerge();
}

void FG::Turtle::Submerge()
{
    if(myIsCurrentlyDiving == true)
    {
        if(myIsUnderWater == false)
        {
            mySubmergeAnimationTime -= myDeltaTime;
            if(mySubmergeAnimationTime < 1.0f * 0.6f)
            {
                myCurrentSprite = 1;
            }
            if(mySubmergeAnimationTime < 1.0f * 0.3f)
            {
                myCurrentSprite = 2;
            }
            if(mySubmergeAnimationTime <= 0)
            {
                myCurrentSprite = -1;
                myIsUnderWater = true;
                myIsCurrentlyDiving = false;
                mySubmergeAnimationTime = 1.0f;
            }
        }
        else
        {
            mySubmergeAnimationTime -= myDeltaTime;
            if(mySubmergeAnimationTime < 1.0f * 0.6f)
            {
                myCurrentSprite = 2;
            }
            if(mySubmergeAnimationTime < 1.0f * 0.3f)
            {
                myCurrentSprite = 1;
            }
            if(mySubmergeAnimationTime <= 0)
            {
                myCurrentSprite = 0;
                myIsUnderWater = false;
                myIsCurrentlyDiving = false;
                mySubmergeAnimationTime = 1.0f;
            }
        }
    }
}
	
void FG::Turtle::Render()
{
	if(myCurrentSprite != -1)
	{
		CU::Vector2f pos = GetPosition();
		pos.myX -= (GetSize().myX * 0.5f);
		int index = 0;

		do
		{
			//mySprites[myCurrentSprite]->Render(pos.myX+16, pos.myY);
			MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*mySprites[myCurrentSprite], CommonUtilities::Vector2f( pos.myX + 16, pos.myY));
			pos.myX += TILESIZE;
			index++;

		}while(index < myLength);
	}
}

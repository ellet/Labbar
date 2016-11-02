#include "Dot.h"

#include "TI_TimeManager.h"

Dot::Dot()
{
}

Dot::~Dot()
{
}

void Dot::Init( CU::Vector2f aPosition, bool isBigDot )
{
	myIsBigDot = isBigDot;
	if(isBigDot == true)
	{
		myVisualRep.Init("Data/bigDot.png");
	}
	else
	{
		myVisualRep.Init("Data/smalDot.png");
	}
	
	myPosition = aPosition;
	myTimer = 0;
	myIsVisible = true;

}

void Dot::Update()
{
	if(myIsBigDot == true)
	{
		myTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();

		if(myTimer >= 0.3)
		{
			myIsVisible^=1;
			myTimer = 0;
		}
	}
}

void Dot::Render()
{
	Update();
	if(myIsVisible == true)
	{
		myVisualRep.Render(myPosition);
	}
}

bool Dot::GetIsBigDot()
{
	return myIsBigDot;
}

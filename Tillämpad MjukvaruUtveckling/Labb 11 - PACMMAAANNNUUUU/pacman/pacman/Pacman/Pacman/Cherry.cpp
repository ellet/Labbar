#include "Cherry.h"

#include "Player.h"
#include "ScoreCounter.h"
#include "TI_TimeManager.h"

Cherry::Cherry()
{
	myTimer = 0.f;
}

Cherry::~Cherry()
{
}

void Cherry::Init()
{
	myVisualRep.Init("Data/cherry.png");
	myIsVisible = false;
	myPosition.Set(325,400);
}

void Cherry::Update(Player& aPlayer, ScoreCounter& aScoreCounter)
{
	if(myIsVisible == true)
	{
		CU::Vector2f lengthVector = aPlayer.GetPosition();
		lengthVector -= aPlayer.GetSize();
		lengthVector -= myPosition;

		if(lengthVector.Length() < 12)
		{
			aScoreCounter.AddScore(100);
			myIsVisible = false;
		}	
	}
	else
	{
		myTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();
		if(myTimer > 20)
		{
			myTimer = 0;
			myIsVisible = true;
		}
	}

}

void Cherry::Render()
{
	if(myIsVisible == true)
	{
		myVisualRep.Render(myPosition);
	}
}
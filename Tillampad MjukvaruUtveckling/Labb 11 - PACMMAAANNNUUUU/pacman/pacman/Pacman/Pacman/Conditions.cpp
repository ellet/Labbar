#include "Conditions.h"

#include "TI_TimeManager.h"

Conditions::Conditions()
{
}

Conditions::~Conditions()
{
}

void Conditions::Init()
{
	myFont = new hgeFont("Data/font1.fnt");
	//myFont->SetScale(1.5);

	myIsVisible = false;
	myGetReadyTimer = 0.0f;
	myLastPlayerLife = 3;

	myTimer = 0.0f;

}

bool Conditions::YouLose(int aLife)
{
	if(aLife < 0)
	{
		myTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_02).GetTime();
		myText = "GAME OVER";
		myIsVisible = true;

		if(myTimer > 5.0f)
		{
			return true;
		}
	}
	return false;
}

bool Conditions::YouWin(int someDotLeft)
{
	if(someDotLeft < 1)
	{
		TI_Time::TimeManager::GetInstance()->SetClockPauseState(TI_Time::GAME_CLOCK_01,true);
		myTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_02).GetTime();
		myText = "YOU WON!!";
		myIsVisible = true;
		if(myTimer > 5.0f)
		{
			return true;
		}
	}
	return false;
}

void Conditions::Render()
{
	if(myIsVisible == true)
	{
		myFont->printf(300,300,HGETEXT_LEFT,"%s",myText);
	}

	myFont->printf(200,10,HGETEXT_LEFT,"Lives: %d",myLastPlayerLife);
}

bool Conditions::GetReady(int aLife)
{
	if(aLife < myLastPlayerLife && aLife > -1)
	{
		myGetReadyTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_02).GetTime();

		if(myGetReadyTimer > 3)
		{
			myLastPlayerLife = aLife;
			myGetReadyTimer = 0.0f;
			TI_Time::TimeManager::GetInstance()->SetClockPauseState(TI_Time::GAME_CLOCK_01,false);

			return true;
		}
		else
		{
			myIsVisible = true;
			myText = "GET READY";
			return false;
		}
	}
	else
	{
		myIsVisible = false;
		return false;
	}
	

}
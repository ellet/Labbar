#include "StdAfx.h"
#include "TimeHandler.h"
#include "MainSingleton.h"
#include "TimeManager.h"
#include "SpriteContainer.h"
#include "Frog.h"

FG::TimeHandler::TimeHandler()
{
}

FG::TimeHandler::~TimeHandler()
{
}

void FG::TimeHandler::Init(Frog* aFrog)
{
	myTimer = TIME_FOR_EACH_FROG;
	myFrog = aFrog;

	myFont = new hgeFont("Fonts/font1.fnt");
    DWORD color = ARGB(255,255,255,255);
    myFont->SetColor(color);
    myFont->SetScale(0.5f);    
}
    
void FG::TimeHandler::ResetTime()
{
	myTimer = TIME_FOR_EACH_FROG;
}
    
void FG::TimeHandler::Update()
{
    myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime().GetTime());

	if(myFrog->IsDead() == false)
	{
		myTimer -= myDeltaTime;
	}

	if(myFrog->HasRespawned())
	{
		ResetTime();
	}

	if(myFrog->HasFoundHome())
	{
		ResetTime();
	}

	if(myTimer <= 0)
	{
		myFrog->KillFrog();
		ResetTime();
	}
}
    
void FG::TimeHandler::Render()
{
	char time[7] = "Time: ";
    myFont->Render(100, 448, HGETEXT_LEFT, time);

	hgeSprite* sprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(TIME_BAR);

	float length = myTimer / TIME_FOR_EACH_FROG;

	DWORD color = ARGB(255,0,255,0);

	if(length < 0.6f)
	{
		color = ARGB(255,255,255,0);
	}
	if(length < 0.2f)
	{
		color = ARGB(255,255,0,0);
	}
    sprite->SetColor(color);


	sprite->RenderStretch(140.0f, 450.0f, 140.0f + (300.0f * length), 460.0f);
}

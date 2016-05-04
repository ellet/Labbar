#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>

#include "Board.h"
#include "Renderer.h"
#include "InputWrapper/InputWrapper.h"


//using namespace DX2D;
CGameWorld::CGameWorld()
	:myBoard(3)
{
	myRenderLock = new std::mutex;
}


CGameWorld::~CGameWorld()
{
}


void CGameWorld::Init()
{
	mySpriteHorse = new DX2D::CSprite("sprites/hestfan.png");
	mySpriteTile = new DX2D::CSprite("sprites/tiletfan.png");
	myExplainForMartinWhatButtonHeShouldPressToShutdownTheProgramAndNotFailUsBecauseThatWouldBeVeryUnecessaryForUsToFailBecauseOfThatStupidReasonWhenWeSpendSoMuchTimeOnTheLabb = new DX2D::CSprite("sprites/MARTINNEEDSEXPLANATIONS.png");
	myExplainForMartinWhatButtonHeShouldPressToShutdownTheProgramAndNotFailUsBecauseThatWouldBeVeryUnecessaryForUsToFailBecauseOfThatStupidReasonWhenWeSpendSoMuchTimeOnTheLabb->SetPosition(DX2D::Vector2f(0.6f, 0.1f));
	//LogicThread();
	
	myLogicThread = new std::thread([this] (){ this->LogicThread(*myRenderLock); });
}



void CGameWorld::Update(float /*aTimeDelta*/)
{ 
	CU::InputWrapper::Update();
	Renderer::DrawBoard(*mySpriteHorse, *mySpriteTile, *myRenderLock);
	myExplainForMartinWhatButtonHeShouldPressToShutdownTheProgramAndNotFailUsBecauseThatWouldBeVeryUnecessaryForUsToFailBecauseOfThatStupidReasonWhenWeSpendSoMuchTimeOnTheLabb->Render();
	
	if (CU::InputWrapper::GetKeyPressed(DIK_ESCAPE) == true)
	{
		std::exit(0);
	}
}

void CGameWorld::LogicThread(std::mutex & aMutex)
{
	short currentSize = 3;
	while (true)
	{
		myBoard.SetBoardSize(currentSize);
		++currentSize;
		myBoard.AddMaximumHorsies(0, 0, aMutex);
		Renderer::AddFinalBoard(myBoard);
	}
}
#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include <Rend/StaticSprite.h>
#include <Rend/RenderConverter.h>

#include <PartionGrid/PartionGrid.h>

CGameWorld::CGameWorld()
{
	myGrid = new PartionGrid();
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myGrid);
}


void CGameWorld::Init()
{
	testInt = 100;

	CU::GrowingArray<CU::Vector2f> tempPositions;



	tempPositions.Init(33);
	tempPositions.Add(CU::Vector2f(80.f, 100.f));
	tempPositions.Add(CU::Vector2f(80.f, 260.f));
	tempPositions.Add(CU::Vector2f(80.f, 420.f));
	tempPositions.Add(CU::Vector2f(80.f, 580.f));
	tempPositions.Add(CU::Vector2f(80.f, 750.f));
	tempPositions.Add(CU::Vector2f(160.f, 160.f));
	tempPositions.Add(CU::Vector2f(160.f, 320.f));
	tempPositions.Add(CU::Vector2f(160.f, 480.f));
	tempPositions.Add(CU::Vector2f(160.f, 640.f));
	tempPositions.Add(CU::Vector2f(260.f, 80.f));
	tempPositions.Add(CU::Vector2f(260.f, 240.f));
	tempPositions.Add(CU::Vector2f(260.f, 400.f));
	tempPositions.Add(CU::Vector2f(260.f, 560.f));
	tempPositions.Add(CU::Vector2f(260.f, 640.f));
	tempPositions.Add(CU::Vector2f(380.f, 160.f));
	tempPositions.Add(CU::Vector2f(380.f, 320.f));
	tempPositions.Add(CU::Vector2f(380.f, 480.f));
	tempPositions.Add(CU::Vector2f(380.f, 600.f));
	tempPositions.Add(CU::Vector2f(380.f, 720.f));
	tempPositions.Add(CU::Vector2f(500.f, 60.f));
	tempPositions.Add(CU::Vector2f(500.f, 260.f));
	tempPositions.Add(CU::Vector2f(500.f, 420.f));
	tempPositions.Add(CU::Vector2f(500.f, 580.f));
	tempPositions.Add(CU::Vector2f(500.f, 740.f));
	tempPositions.Add(CU::Vector2f(600.f, 120.f));
	tempPositions.Add(CU::Vector2f(600.f, 280.f));
	tempPositions.Add(CU::Vector2f(600.f, 440.f));
	tempPositions.Add(CU::Vector2f(600.f, 640.f));
	tempPositions.Add(CU::Vector2f(720.f, 60.f));
	tempPositions.Add(CU::Vector2f(720.f, 220.f));
	tempPositions.Add(CU::Vector2f(720.f, 380.f));
	tempPositions.Add(CU::Vector2f(720.f, 540.f));
	tempPositions.Add(CU::Vector2f(720.f, 720.f));


	myGrid->Init(tempPositions);
}



void CGameWorld::Update(float /*aTimeDelta*/)
{
	if (GetInput::GetMouseButtonReleased(CU::enumMouseButtons::eLeft) == true)
	{
		myGrid->SetPointOfViewPosition(GetInput::GetMouseWindowPosition());
	}

	myGrid->Update();
}

void CGameWorld::Draw() const
{
	myGrid->Draw();

	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}

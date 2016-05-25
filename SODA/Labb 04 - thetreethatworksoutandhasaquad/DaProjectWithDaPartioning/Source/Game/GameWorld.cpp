#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include <Rend/StaticSprite.h>
#include <Rend/RenderConverter.h>


#include <QuadTree/QuadTree.h>


CGameWorld::CGameWorld()
{
	myPrettyTree = new QuadTree();
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myPrettyTree);
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

	myPrettyTree->Init(tempPositions);


	myPrettyTree->BuildTree(CU::Vector2f(400.f, 400.f), 4);
	myPrettyTree->AddAllObjects();
}



void CGameWorld::Update(const CU::Time & aTime)
{
	if (GetInput::GetMouseButtonDown(CU::enumMouseButtons::eLeft) == true)
	{
		myPrettyTree->SetPointOfView(GetInput::GetMouseWindowPosition());
	}

	if (GetInput::GetMouseButtonDown(CU::enumMouseButtons::eRight) == true)
	{
		myPrettyTree->SetPointOfViewRotation(GetInput::GetMouseWindowPosition());
	}

	myPrettyTree->Update(aTime);
	
}

void CGameWorld::Draw() const
{
	myPrettyTree->Draw();
	

	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}

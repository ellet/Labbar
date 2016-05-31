#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include <Rend/StaticSprite.h>
#include <Rend/RenderConverter.h>


#include <QuadTree/OctoTree.h>


CGameWorld::CGameWorld()
{
	myPrettyTree = new OctoTree();
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myPrettyTree);
}


void CGameWorld::Init()
{
	testInt = 100;

	CU::GrowingArray<CU::Vector3f> tempPositions;
	Randomizer rehndomizher;
	unsigned short numberOfObjects = 1000;
	tempPositions.Init(numberOfObjects);

	for (unsigned short iObject = 0; iObject < numberOfObjects; ++iObject)
	{
		CU::Vector3f randomPos;
		randomPos.x = rehndomizher.GetRandomValue(0.f, 800.f);
		randomPos.y = rehndomizher.GetRandomValue(0.f, 800.f);
		randomPos.z = rehndomizher.GetRandomValue(0.f, 800.f);
		tempPositions.Add(randomPos);
	}

	myPrettyTree->Init(tempPositions);

	myPrettyTree->BuildTree(CU::Vector3f(400.f, 400.f, 400.f), 5);
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
		myPrettyTree->SetPointOfViewRotation(CU::Vector3f(GetInput::GetMouseWindowPosition().x, GetInput::GetMouseWindowPosition().y, 0.f));
	}

	CU::Vector3f addedRotation = CU::Vector3f::Zero;

	if (GetInput::GetKeyDown(DIK_DOWNARROW) == true)
	{
		addedRotation.x = 50.f * aTime.GetSeconds();
	}
	if (GetInput::GetKeyDown(DIK_RIGHTARROW) == true)
	{
		addedRotation.y = 50.f * aTime.GetSeconds();
	}
	if (GetInput::GetKeyDown(DIK_UPARROW) == true)
	{
		addedRotation.x = -50.f * aTime.GetSeconds();
	}
	if (GetInput::GetKeyDown(DIK_LEFTARROW) == true)
	{
		addedRotation.y = -50.f * aTime.GetSeconds();
	}
	if (GetInput::GetKeyDown(DIK_PGUP) == true)
	{
		addedRotation.z = 50.f * aTime.GetSeconds();
	}
	if (GetInput::GetKeyDown(DIK_PGDN) == true)
	{
		addedRotation.z = -50.f * aTime.GetSeconds();
	}

	if (GetInput::GetKeyDown(DIK_NUMPADMINUS) == true)
	{
		myPrettyTree->SetLooseNess(-1.f * aTime.GetSeconds());
		myPrettyTree->AddAllObjects();
	}

	if (GetInput::GetKeyDown(DIK_NUMPADPLUS) == true)
	{
		myPrettyTree->SetLooseNess(1.f * aTime.GetSeconds());
		myPrettyTree->AddAllObjects();
	}

	myPrettyTree->SetPointOfViewRotation(addedRotation);
	myPrettyTree->Update(aTime);
}

void CGameWorld::Draw() const
{
	myPrettyTree->Draw();
	

	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}

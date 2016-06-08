#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include <Rend/StaticSprite.h>
#include <Rend/RenderConverter.h>
#include <amp.h>


#include <KDtree/KristDemokratTree.h>


const CU::Vector2f WorldSize = CU::Vector2f(1024, 768);

CGameWorld::CGameWorld()
{
	myPrettyTree = new KDTree();
	myHashtagDeep = 1;
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myPrettyTree);
}


void CGameWorld::Init()
{
	CU::GrowingArray<CU::Vector2f> tempPositions;
	CU::GrowingArray<float> tempRadius;
	Randomizer rehndomizher;
	unsigned short numberOfObjects = 25;
	tempPositions.Init(numberOfObjects);
	tempRadius.Init(numberOfObjects);

	for (unsigned short iObject = 0; iObject < numberOfObjects; ++iObject)
	{
		CU::Vector2f randomPos;
		randomPos.x = rehndomizher.GetRandomValue(0, WorldSize.x);
		randomPos.y = rehndomizher.GetRandomValue(0.f, WorldSize.y);
		tempPositions.Add(randomPos);
		tempRadius.Add(rehndomizher.GetRandomValue(4.f, 16.f));
	}

	myPrettyTree->Init(tempPositions, tempRadius);

	myPrettyTree->BuildTree(CU::Vector2f(WorldSize.x, WorldSize.y), myHashtagDeep);
}



void CGameWorld::Update(const CU::Time & aTime)
{
	//if (GetInput::GetMouseButtonPressed(CU::enumMouseButtons::eRight) == true)
	if (GetInput::GetKeyReleased(DIK_LCONTROL) == true)
	{
		myMouseStartPosition = GetInput::GetMouseWindowPosition();
	}

	if (GetInput::GetMouseButtonDown(CU::enumMouseButtons::eRight) == true)
	{
		myPrettyTree->SetupPointOfView(myMouseStartPosition, GetInput::GetMouseWindowPosition());
	}
	
	myPrettyTree->Update(aTime);

	if (GetInput::GetKeyReleased(DIK_UPARROW) == true)
	{
		myHashtagDeep += 1;
		if (myHashtagDeep > 10)
		{
			myHashtagDeep = 10;
		}
		
		myPrettyTree->BuildTree(CU::Vector2f(WorldSize.x, WorldSize.y), myHashtagDeep);
	}

	if (GetInput::GetKeyReleased(DIK_DOWNARROW) == true)
	{
		myHashtagDeep -= 1;
		if (myHashtagDeep < 1)
		{
			myHashtagDeep = 1;
		}
		
		myPrettyTree->BuildTree(CU::Vector2f(WorldSize.x, WorldSize.y), myHashtagDeep);
	}
}

void CGameWorld::Draw() const
{
	myPrettyTree->Draw();

	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}

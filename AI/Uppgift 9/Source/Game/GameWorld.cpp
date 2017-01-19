#include "stdafx.h"
#include "GameWorld.h"
#include "Controllers\PlayerController.h"
#include "Controllers\TeamBasedGameController.h"
#include "PathFinderGame\WorldTiles.h"
#include "imgui.h"

CGameWorld::CGameWorld()
{
	
}


CGameWorld::~CGameWorld()
{
	
}


void CGameWorld::Init()
{
	
	myTiles = new WorldTiles(33.f, 10, 18);
	
}



void CGameWorld::Update(float aDeltaTime)
{
	ImGui::Begin("test");

	//ImVec2 test(200.f, 200.f);
	if (ImGui::Button("resetGrid") == true)
	{

	}

	ImGui::End();

	if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
	{
		myTiles->SetTileType(TileTypes::eRoad, myInput.GetMousePosition());
	}
}

void CGameWorld::Render() const
{
	myTiles->Render();
}

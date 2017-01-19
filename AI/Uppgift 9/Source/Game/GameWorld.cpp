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
	
	myTiles = new WorldTiles(33.f, 35, 35);

	myPlayerSprite.Init("Sprites/PlayerUnit.dds");
	myPlayerSprite.SetPosition({ 100.f, 100.f });
	
	
}



void CGameWorld::Update(float aDeltaTime)
{
	ImGui::Begin("test");

	//ImVec2 test(200.f, 200.f);
	if (ImGui::Button("resetGrid") == true)
	{

	}

	ImGui::End();

	if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eRight) == true)
	{
		myPlayerSprite.SetPosition(myInput.GetMousePosition());
	}

	if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
	{
		SB::GrowingArray<SB::Vector2f> tempPath;
		myTiles->CreatePath(myPlayerSprite.GetPosition(), myInput.GetMousePosition(), tempPath);
	}
}

void CGameWorld::Render() const
{
	myTiles->Render();
	myPlayerSprite.Render();
}

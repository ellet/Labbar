#include "stdafx.h"
#include "GameWorld.h"
#include "Controllers\PlayerController.h"
#include "Controllers\TeamBasedGameController.h"
#include "PathFinderGame\WorldTiles.h"
#include "imgui.h"
#include "Controllers\FollowPathController.h"


CGameWorld::CGameWorld()
{
	
}


CGameWorld::~CGameWorld()
{
	
}


void CGameWorld::Init()
{
	
	myTiles = new WorldTiles(33.f, 35, 30);

	myPlayer.SetSprite("Sprites/PlayerUnit.dds");
	myPlayer.SetPosition({ 100.f, 100.f });
	myPlayerController = &myPlayer.SetController<FollowPathController>();
}



void CGameWorld::Update(float aDeltaTime)
{
	ImGui::Begin("test");

	//ImVec2 test(200.f, 200.f);
	if (ImGui::Button("resetGrid") == true)
	{

	}

	ImGui::End();

	myPlayer.Update(aDeltaTime);

	if (ImGui::IsMouseHoveringAnyWindow() == false)
	{
		if (myInput.GetIfMouseButtonDown(SB::MouseKey::eRight) == true)
		{
			//myPlayerSprite.SetPosition(myInput.GetMousePosition());
		}

		if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
		{
			myPathToShow.RemoveAll();
			myTiles->CreatePath(myPlayer.GetPosition(), myInput.GetMousePosition(), myPathToShow);
			myPlayerController->SetPath(myPathToShow);
		}
	}

	if (myPathToShow.Size() > 1)
	{
		SB::Vector2f startPos = myPathToShow[0];
		SB::Vector2f endPos;
		for (unsigned short iPos = 1; iPos < myPathToShow.Size(); ++iPos)
		{
			endPos = myPathToShow[iPos];
			BDRenderer::RenderLine(startPos, endPos);
			startPos = endPos;
		}
	}
}

void CGameWorld::Render() const
{
	myTiles->Render();
	myPlayer.Render();
}

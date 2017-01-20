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

	myPlayerController->SetSpeedModifier(myTiles->GetTileCost(myPlayerController->GetPosition()));
	myPlayer.Update(aDeltaTime);

	static bool drawMapMode = true;

	if (ImGui::Button("SwitchMode") == true)
	{
		drawMapMode = !drawMapMode;
	}

	static int currentTileDrop;

	if (drawMapMode == true)
	{
		ImGui::RadioButton("Field", &currentTileDrop, static_cast<int>(TileTypes::eField));
		ImGui::RadioButton("Rock", &currentTileDrop, static_cast<int>(TileTypes::eRock));
		ImGui::RadioButton("Swamp", &currentTileDrop, static_cast<int>(TileTypes::eSvamp));
		ImGui::RadioButton("Road", &currentTileDrop, static_cast<int>(TileTypes::eRoad));
	}

	if (ImGui::IsMouseHoveringAnyWindow() == false)
	{
		if (myInput.GetIfMouseButtonDown(SB::MouseKey::eRight) == true)
		{
			//myPlayerSprite.SetPosition(myInput.GetMousePosition());
		}

		if (drawMapMode == true)
		{
			if (myInput.GetIfMouseButtonDown(SB::MouseKey::eLeft) == true)
			{
				myTiles->SetTileType(static_cast<TileTypes>(currentTileDrop), myInput.GetMousePosition());

			}
		}
		else
		{
			if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
			{
				myPathToShow.RemoveAll();
				myTiles->CreatePath(myPlayer.GetPosition(), myInput.GetMousePosition(), myPathToShow);
				myPlayerController->SetPath(myPathToShow);
			
			}
		}
	}

	static int item = static_cast<int>(DebugRenderModes::eNone);
	ImGui::Combo("RenderMode", &item, "Show Tile Cost\0Show Current Path Cost\0Only RenderMap\0\0");

	myTiles->SetRenderMode(static_cast<DebugRenderModes>(item));

	/*if (myPathToShow.Size() > 1)
	{
		SB::Vector2f startPos = myPathToShow[0];
		SB::Vector2f endPos;
		for (unsigned short iPos = 1; iPos < myPathToShow.Size(); ++iPos)
		{
			endPos = myPathToShow[iPos];
			BDRenderer::RenderLine(startPos, endPos);
			startPos = endPos;
		}
	}*/
}

void CGameWorld::Render() const
{
	myTiles->Render();
	myPlayer.Render();
}

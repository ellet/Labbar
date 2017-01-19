#pragma once
#include "Input\InputListener.h"
#include "Actors\Actor.h"
#include "PathFinderGame\Tile.h"
#include "Rendering\BDText.h"

class BDSprite;
class TeamBasedGameController;
class WorldTiles;
class FollowPathController;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render() const;

private:
	SB::GrowingArray<SB::Vector2f> myPathToShow;

	InputListener myInput;
	
	Actor myPlayer;
	FollowPathController * myPlayerController;

	WorldTiles * myTiles;
};
#pragma once
#include "Input\InputListener.h"
#include "Actors\Actor.h"
#include "PathFinderGame\Tile.h"


class BDSprite;
class TeamBasedGameController;
class WorldTiles;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render() const;

private:
	InputListener myInput;
	
	WorldTiles * myTiles;
};
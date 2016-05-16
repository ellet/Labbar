#pragma once

#include "GameObjects/Tile/Tile.h"

class Randomizer;

class Church
{
public:
	Church();
	~Church();

	void ApplyChurch(TileGrid & aWorld);

	void RecursiveReligion(TileGrid & aWorld, const CU::Vector2ui & aPosition, const float aMorale);

	static void InitRandomReligion(const size_t aSeed);

private:
	bool ApplyMorale(TileGrid & aWorld, const CU::Vector2ui & aPosition, const float aMorale);
	static Randomizer * ourRandomizer;
};
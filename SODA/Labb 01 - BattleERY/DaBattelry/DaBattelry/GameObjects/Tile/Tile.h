#pragma once
#include <CU/Utility/Randomizer/Randomizer.h>

struct Tile
{
public:
	Tile()
	{
		myDefenseBonus = ourRandomizer->GetRandomValue(0.f, 2.f);
		myAttackBonus = ourRandomizer->GetRandomValue(0.f, 4.f);
		myMoraleBonus = 0;

		myUnitIndex = USHRT_MAX;

		myHasChurch = false;
	}
	~Tile()
	{}

	static void CreateRandomizer()
	{
		ourRandomizer = new Randomizer();
	}

	bool SetMorale(const float aMoraleAmount)
	{
		if (aMoraleAmount > myMoraleBonus)
		{
			myMoraleBonus = aMoraleAmount;
			return true;
		}
		return false;
	}

	void SetTileEmpty()
	{
		myUnitIndex = USHRT_MAX;
	}

	void BECOMENOTHEATHEN()
	{
		myHasChurch = true;
	}

	bool ISHEATHEN()
	{
		return !myHasChurch;
	}

	bool CheckIfEmpty()
	{
		if (myUnitIndex == USHRT_MAX)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static Randomizer * ourRandomizer;

	float myDefenseBonus;
	float myAttackBonus;
	float myMoraleBonus;	
	bool myHasChurch;

	unsigned short myUnitIndex;
};

typedef CU::GridArray<Tile, unsigned int> TileGrid;

__declspec(selectany) Randomizer * Tile::ourRandomizer;


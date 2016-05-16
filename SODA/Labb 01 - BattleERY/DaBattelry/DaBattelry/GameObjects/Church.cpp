#include "stdafx.h"
#include "Church.h"


Randomizer * Church::ourRandomizer;

Church::Church()
{
}


Church::~Church()
{
}

void Church::ApplyChurch(TileGrid & aWorld)
{
	bool imPlaced = false;
	while (imPlaced == false)
	{
		unsigned int randomPosY = static_cast<unsigned int>(ourRandomizer->GetRandomValue(0.f, static_cast<float>(aWorld.Height()) - 1.f));
		unsigned int randomPosX = static_cast<unsigned int>(ourRandomizer->GetRandomValue(0.f, static_cast<float>(aWorld.Width()) - 1.f));

		CU::Vector2ui position(randomPosX, randomPosY);

		if (aWorld.Access(randomPosX, randomPosY).ISHEATHEN() == true)
		{
			RecursiveReligion(aWorld, position, 1.f);
			aWorld.Access(randomPosX, randomPosY).BECOMENOTHEATHEN();
			imPlaced = true;
		}
	}
}

void Church::RecursiveReligion(TileGrid & aWorld, const CU::Vector2ui & aPosition, const float aMorale)
{
	if (aMorale <= 0.07f)
	{
		return;
	}
	if (ApplyMorale(aWorld, aPosition - CU::Vector2ui::UnitX, aMorale) == true)
	{
		RecursiveReligion(aWorld, aPosition - CU::Vector2ui::UnitX, aMorale / 2.f);
	}

	if (ApplyMorale(aWorld, aPosition - CU::Vector2ui::UnitY, aMorale) == true)
	{
		RecursiveReligion(aWorld, aPosition - CU::Vector2ui::UnitY, aMorale / 2.f);
	}

	if (ApplyMorale(aWorld, aPosition + CU::Vector2ui::UnitY, aMorale) == true)
	{
		RecursiveReligion(aWorld, aPosition + CU::Vector2ui::UnitY, aMorale / 2.f);
	}

	if (ApplyMorale(aWorld, aPosition + CU::Vector2ui::UnitX, aMorale) == true)
	{
		RecursiveReligion(aWorld, aPosition + CU::Vector2ui::UnitX, aMorale / 2.f);
	}
}

 void Church::InitRandomReligion(const size_t aSeed)
{
	ourRandomizer = new Randomizer(aSeed);
}

bool Church::ApplyMorale(TileGrid & aWorld, const CU::Vector2ui & aPosition, const float aMorale)
{
	if (aPosition.x < aWorld.Width() || aPosition.y < aWorld.Height())
	{
		return false;
	}
	return (aWorld.Access(aPosition.x, aPosition.y).SetMorale(aMorale) == true);
}
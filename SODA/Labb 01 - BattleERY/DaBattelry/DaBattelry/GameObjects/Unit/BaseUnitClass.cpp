#include "stdafx.h"
#include "BaseUnitClass.h"
#include <CU/Utility/Randomizer/Randomizer.h>
#include "Printing/PrinterClass.h"
#include <CU/GrowingArray/GrowingArray.h>


CU::GrowingArray<CU::Vector2ui> BaseUnitClass::ourBasePositions;

TileGrid * BaseUnitClass::ourWorld = nullptr;

CU::GrowingArray<BaseUnitClass*> * BaseUnitClass::ourBuddies = nullptr;

Randomizer * BaseUnitClass::ourRandomizer = nullptr;

BaseUnitClass::BaseUnitClass(const unsigned short aIndex, const unsigned short aFactionID)
{
	myFaction = aFactionID;
	myIndex = aIndex;
	myIsAlive = true;

	CU::Vector2ui tempPosition;
	do
	{
		tempPosition = RandomizePosition();
	} while (GetTile(tempPosition).CheckIfEmpty() == false);

	PutUnitOnTile(tempPosition);

	
}


BaseUnitClass::~BaseUnitClass()
{
}

CU::Vector2ui BaseUnitClass::RandomizePosition()
{
	CU::Vector2ui tempPos;
	tempPos.x = static_cast<unsigned int>(ourRandomizer->GetRandomValue(0.f, static_cast<float>(ourWorld->Width() -1)));
	tempPos.y = static_cast<unsigned int>(ourRandomizer->GetRandomValue(0.f, static_cast<float>(ourWorld->Height() -1)));

	return tempPos;
}

void BaseUnitClass::PutUnitOnTile(const CU::Vector2ui & aPosition)
{
	DL_ASSERT(ourWorld->Access(aPosition.x, aPosition.y).CheckIfEmpty() == true, "Unit Put On None EmptyTile");
	GetTile(aPosition).myUnitIndex = myIndex;
	myPosition = aPosition;
}

void BaseUnitClass::Slain()
{
	myIsAlive = false;
	GetCurrentTile().SetTileEmpty();
}

Tile& BaseUnitClass::GetCurrentTile()
{
	return ourWorld->Access(myPosition.x, myPosition.y);
}

Tile& BaseUnitClass::GetTile(const CU::Vector2ui & aPosition)
{
	return ourWorld->Access(aPosition.x, aPosition.y);
}

float BaseUnitClass::CalculateMorale()
{
	return (1.f + GetCurrentTile().myMoraleBonus + CalculateBaseMorale());
}

float BaseUnitClass::CalculateBaseMorale()
{
	int xPos = static_cast<int>(myPosition.x);
	int yPos = static_cast<int>(myPosition.y);
	int xBasePos = static_cast<int>(ourBasePositions[myFaction].x);
	int yBasePos = static_cast<int>(ourBasePositions[myFaction].y);
	unsigned int xDistance = (abs(xBasePos - xPos));
	unsigned int yDistance = (abs(yBasePos - yPos));
	if ((yDistance + xDistance) > 20)
	{
		return 0.f;
	}
	return (1 - ((yDistance + xDistance) * 0.05f));
}

float BaseUnitClass::CalculateDamage()
{
	return (1.f + GetCurrentTile().myAttackBonus) * GetCurrentTile().myMoraleBonus;
}

float BaseUnitClass::CalculateDefense()
{
	return (1.f + GetCurrentTile().myDefenseBonus) * GetCurrentTile().myMoraleBonus;
}

void BaseUnitClass::SetWorld(TileGrid * aWorld, const size_t aSeed)
{
	ourWorld = aWorld;
	ourRandomizer = new Randomizer(aSeed);
}

void BaseUnitClass::SetBuddies(CU::GrowingArray<BaseUnitClass*>* anArmy)
{
	ourBuddies = anArmy;
}

void BaseUnitClass::Update()
{
	if (myIsAlive == false)
	{ 
  		return;
	}

	unsigned short numberOfChecks = 0;
	do
	{
		CU::Vector2ui newPosition;
		do
		{
			unsigned short direction;
			direction = static_cast<unsigned short>(ourRandomizer->GetRandomValue(0.f, 3.f));

			newPosition = myPosition;

			switch (direction)
			{
			case 0:
				newPosition.x += 1;
				break;
			case 1:
				newPosition.y -= 1;
				break;
			case 2:
				newPosition.x -= 1;
				break;
			case 3:
				newPosition.y += 1;
				break;
			default:
				bool thisIsFalse = false;
				DL_ASSERT(thisIsFalse, "YOU FAACKED AAAPP - Default Unit find direction");
				break;
			}
		} while (newPosition.x >= ourWorld->Width() || newPosition.y >= ourWorld->Height());


		if (HandleMovement(newPosition) == true)
		{
			break;
		}

		++numberOfChecks;
	} while (numberOfChecks <= 5);

}

void BaseUnitClass::CountIsAlive()
{
	if (myIsAlive == true)
	{
		PT::CountAliveBodies(myFaction);
	}
}



void BaseUnitClass::HandleCombat(BaseUnitClass * aFoe)
{
	if (((GetAttackRating() - aFoe->GetDefenseRating()) * GetMoraleRating()) >=
		((aFoe->GetAttackRating() - GetDefenseRating()) * aFoe->GetMoraleRating()))
	{
		aFoe->Slain();
	}
	else
	{
		Slain();
	}
	PT::PerformedCombat();
}

bool BaseUnitClass::HandleMovement(const CU::Vector2ui & aNewPosition)
{
	if (GetTile(aNewPosition).CheckIfEmpty() == true)
	{
		Move(aNewPosition);
		PT::MovedUnit();
		return true;
	}
	else
	{
		if ((*ourBuddies)[GetTile(aNewPosition).myUnitIndex]->myFaction == myFaction)
		{
			return false;
		}

 		HandleCombat((*ourBuddies)[GetTile(aNewPosition).myUnitIndex]);
		return true;
	}
}

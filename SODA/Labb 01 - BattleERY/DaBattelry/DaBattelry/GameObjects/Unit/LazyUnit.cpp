#include "stdafx.h"
#include "LazyUnit.h"


LazyUnit::LazyUnit(const unsigned short aIndex, const unsigned short aFactionID)
	: BaseUnitClass(aIndex, aFactionID)
{
}


LazyUnit::~LazyUnit()
{
}

float LazyUnit::GetAttackRating()
{
	return CalculateDamage();
}

float LazyUnit::GetDefenseRating()
{
	return CalculateDefense();
}

float LazyUnit::GetMoraleRating()
{
	return CalculateMorale();
}

void LazyUnit::Move(const CU::Vector2ui & aNewPosition)
{
	GetCurrentTile().SetTileEmpty();
	PutUnitOnTile(aNewPosition);
}

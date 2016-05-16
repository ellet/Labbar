#include "stdafx.h"
#include "DefaultUnit.h"


DefaultUnit::DefaultUnit(const unsigned short aIndex, const unsigned short aFactionID)
	: BaseUnitClass(aIndex, aFactionID)
{
	myDamage = CalculateDamage();
	myDefense = CalculateDefense();
	myMorale = CalculateMorale();
}


DefaultUnit::~DefaultUnit()
{
}

float DefaultUnit::GetAttackRating()
{
	return myDamage;
}

float DefaultUnit::GetDefenseRating()
{
	return myDefense;
}

float DefaultUnit::GetMoraleRating()
{
	return myMorale;
}

void DefaultUnit::Move(const CU::Vector2ui & aNewPosition)
{
	GetCurrentTile().SetTileEmpty();
	
	PutUnitOnTile(aNewPosition);
	
	myDamage = CalculateDamage();
	myDefense = CalculateDamage();
	myMorale = CalculateMorale();
}



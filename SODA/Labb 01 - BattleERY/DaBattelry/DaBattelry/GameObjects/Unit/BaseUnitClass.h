#pragma once
#include "GameObjects/Tile/Tile.h"

class Randomizer;

class BaseUnitClass
{
public:
	BaseUnitClass(const unsigned short aIndex, const unsigned short aFactionID);
	virtual ~BaseUnitClass();

	virtual float GetAttackRating() = 0;

	virtual float GetDefenseRating() = 0;

	virtual float GetMoraleRating() = 0;

	virtual void Move(const CU::Vector2ui & aNewPosition) = 0;

	static void SetWorld(TileGrid * aWorld, const size_t aSeed);
	static void SetBuddies(CU::GrowingArray<BaseUnitClass*> * anArmy);

	void Update();

	void CountIsAlive();

	static CU::GrowingArray<CU::Vector2ui> ourBasePositions;
protected:
	void HandleCombat(BaseUnitClass * aFoe);
	bool HandleMovement(const CU::Vector2ui & aNewPosition);
	CU::Vector2ui RandomizePosition();
	void PutUnitOnTile(const CU::Vector2ui & aPosition);
	void Slain();
	Tile& GetCurrentTile();
	Tile& GetTile(const CU::Vector2ui & aPosition);

	float CalculateMorale();
	float CalculateBaseMorale();
	float CalculateDamage();
	float CalculateDefense();

	static TileGrid * ourWorld;
	static CU::GrowingArray<BaseUnitClass*> * ourBuddies;
	static Randomizer * ourRandomizer;

	unsigned short myIndex;
	unsigned short myFaction;
	CU::Vector2ui myPosition;
	bool myIsAlive;
};
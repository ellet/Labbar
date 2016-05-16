#pragma once

#include "GameObjects/Tile/Tile.h"

class BaseUnitClass;

enum class enumUnitTypeMode
{
	eDefault,
	eLazy,
	enumLength
};

struct GameSettings
{
	GameSettings()
	{
		myUnitSettingType = enumUnitTypeMode::eDefault;
		myUnitsPerFaction = 2000;
		myAmountOfFactions = 8;
		myNumberOfTurns = 20000;
		myAmountOfCurches = 100;
		myRandomizerSeed = 1;
	}

	enumUnitTypeMode myUnitSettingType;

	unsigned short myUnitsPerFaction;
	unsigned short myAmountOfFactions;
	unsigned short myNumberOfTurns;
	unsigned short myAmountOfCurches;
	unsigned short myRandomizerSeed;
};

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void SetUpGame();

	void RunGame();

	void Init(const CU::Vector2ui & aGridSize);

	void DoTurn();

	void SetUnitType(const enumUnitTypeMode aMode);

private:
	void InitWorld(const CU::Vector2ui & aGridSize);
	void InitUnits();
	void InitChurches();
	void InitBases();
	CU::Timer myTimer;
	CU::Time myStartOfBattle;

	GameSettings myGameSettings;
	Randomizer myRandomizer;

	TileGrid myWorld;
	CU::GrowingArray<BaseUnitClass*> myUnits;
};
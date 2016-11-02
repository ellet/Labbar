#include "StdAfx.h"
#include "LevelDataHandler.h"

FG::LevelDataHandler::LevelDataHandler()
{
}

FG::LevelDataHandler::~LevelDataHandler()
{
}

void FG::LevelDataHandler::Init()
{
	InitVehicleData();
	InitWaterEntityData();
}

void FG::LevelDataHandler::InitVehicleData()
{
	//LEVEL1
	myLevelData[LEVEL1].myVehicleData[CAR].myMovementSpeed = 70.0f;
	myLevelData[LEVEL1].myVehicleData[CAR].myMaxVehicles = 5;
	myLevelData[LEVEL1].myVehicleData[CAR].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myVehicleData[CAR].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myVehicleData[BULLDOZER].myMovementSpeed = 50.0f;
	myLevelData[LEVEL1].myVehicleData[BULLDOZER].myMaxVehicles = 5;
	myLevelData[LEVEL1].myVehicleData[BULLDOZER].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myVehicleData[BULLDOZER].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myVehicleData[FERARRI].myMovementSpeed = 100.0f;
	myLevelData[LEVEL1].myVehicleData[FERARRI].myMaxVehicles = 6;
	myLevelData[LEVEL1].myVehicleData[FERARRI].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myVehicleData[FERARRI].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myVehicleData[TRUCK].myMovementSpeed = 50.0f;
	myLevelData[LEVEL1].myVehicleData[TRUCK].myMaxVehicles = 3;
	myLevelData[LEVEL1].myVehicleData[TRUCK].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myVehicleData[TRUCK].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myVehicleData[BUS].myMovementSpeed = 80.0f;
	myLevelData[LEVEL1].myVehicleData[BUS].myMaxVehicles = 2;
	myLevelData[LEVEL1].myVehicleData[BUS].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myVehicleData[BUS].myRandomSpawnDimensions.myY = 5;

	//LEVEL2
	myLevelData[LEVEL2].myVehicleData[CAR].myMovementSpeed = 150.0f;
	myLevelData[LEVEL2].myVehicleData[CAR].myMaxVehicles = 5;
	myLevelData[LEVEL2].myVehicleData[CAR].myRandomSpawnDimensions.myX = 1;
	myLevelData[LEVEL2].myVehicleData[CAR].myRandomSpawnDimensions.myY = 1;

	myLevelData[LEVEL2].myVehicleData[BULLDOZER].myMovementSpeed = 60.0f;
	myLevelData[LEVEL2].myVehicleData[BULLDOZER].myMaxVehicles = 5;
	myLevelData[LEVEL2].myVehicleData[BULLDOZER].myRandomSpawnDimensions.myX = 1;
	myLevelData[LEVEL2].myVehicleData[BULLDOZER].myRandomSpawnDimensions.myY = 1;

	myLevelData[LEVEL2].myVehicleData[FERARRI].myMovementSpeed = 300.0f;
	myLevelData[LEVEL2].myVehicleData[FERARRI].myMaxVehicles = 6;
	myLevelData[LEVEL2].myVehicleData[FERARRI].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myVehicleData[FERARRI].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myVehicleData[TRUCK].myMovementSpeed = 50.0f;
	myLevelData[LEVEL2].myVehicleData[TRUCK].myMaxVehicles = 3;
	myLevelData[LEVEL2].myVehicleData[TRUCK].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myVehicleData[TRUCK].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myVehicleData[BUS].myMovementSpeed = 120.0f;
	myLevelData[LEVEL2].myVehicleData[BUS].myMaxVehicles = 2;
	myLevelData[LEVEL2].myVehicleData[BUS].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myVehicleData[BUS].myRandomSpawnDimensions.myY = 5;
}
	
void FG::LevelDataHandler::InitWaterEntityData()
{
	//LEVEL1
	myLevelData[LEVEL1].myWaterEntityData[SMALL_TURTLE].myMovementSpeed = 40.0f;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_TURTLE].myMaxWaterEntitys = 4;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_TURTLE].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_TURTLE].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myWaterEntityData[BIG_TURTLE].myMovementSpeed = 60.0f;
	myLevelData[LEVEL1].myWaterEntityData[BIG_TURTLE].myMaxWaterEntitys = 3;
	myLevelData[LEVEL1].myWaterEntityData[BIG_TURTLE].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myWaterEntityData[BIG_TURTLE].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myWaterEntityData[SMALL_LOG].myMovementSpeed = 60.0f;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_LOG].myMaxWaterEntitys = 3;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_LOG].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myWaterEntityData[SMALL_LOG].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myWaterEntityData[MEDIUM_LOG].myMovementSpeed = 40.0f;
	myLevelData[LEVEL1].myWaterEntityData[MEDIUM_LOG].myMaxWaterEntitys = 3;
	myLevelData[LEVEL1].myWaterEntityData[MEDIUM_LOG].myRandomSpawnDimensions.myX = 3;
	myLevelData[LEVEL1].myWaterEntityData[MEDIUM_LOG].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL1].myWaterEntityData[BIG_LOG].myMovementSpeed = 80.0f;
	myLevelData[LEVEL1].myWaterEntityData[BIG_LOG].myMaxWaterEntitys = 2;
	myLevelData[LEVEL1].myWaterEntityData[BIG_LOG].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL1].myWaterEntityData[BIG_LOG].myRandomSpawnDimensions.myY = 5;

	//LEVEL2
	myLevelData[LEVEL2].myWaterEntityData[SMALL_TURTLE].myMovementSpeed = 40.0f;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_TURTLE].myMaxWaterEntitys = 4;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_TURTLE].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_TURTLE].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myWaterEntityData[BIG_TURTLE].myMovementSpeed = 80.0f;
	myLevelData[LEVEL2].myWaterEntityData[BIG_TURTLE].myMaxWaterEntitys = 3;
	myLevelData[LEVEL2].myWaterEntityData[BIG_TURTLE].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myWaterEntityData[BIG_TURTLE].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myWaterEntityData[SMALL_LOG].myMovementSpeed = 60.0f;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_LOG].myMaxWaterEntitys = 3;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_LOG].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myWaterEntityData[SMALL_LOG].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myWaterEntityData[MEDIUM_LOG].myMovementSpeed = 60.0f;
	myLevelData[LEVEL2].myWaterEntityData[MEDIUM_LOG].myMaxWaterEntitys = 3;
	myLevelData[LEVEL2].myWaterEntityData[MEDIUM_LOG].myRandomSpawnDimensions.myX = 3;
	myLevelData[LEVEL2].myWaterEntityData[MEDIUM_LOG].myRandomSpawnDimensions.myY = 5;

	myLevelData[LEVEL2].myWaterEntityData[BIG_LOG].myMovementSpeed = 100.0f;
	myLevelData[LEVEL2].myWaterEntityData[BIG_LOG].myMaxWaterEntitys = 2;
	myLevelData[LEVEL2].myWaterEntityData[BIG_LOG].myRandomSpawnDimensions.myX = 2;
	myLevelData[LEVEL2].myWaterEntityData[BIG_LOG].myRandomSpawnDimensions.myY = 5;
}
	
FG::LevelData* FG::LevelDataHandler::GetLevelData(Level aLevel)
{
	return &myLevelData[aLevel];
}

#ifndef LEVEL_DATA_HANDLER_HEADER
#define LEVEL_DATA_HANDLER_HEADER

#include "namespaces.h"
#include "Vector2.h"
#include "StaticArray.h"
#include "defines.h"

namespace FroggerGame
{
	enum Level
	{
		LEVEL1 = 0,
		LEVEL2 = 1,
	};

	struct VehicleData
	{
		float myMovementSpeed;
		int myMaxVehicles;
		CU::Vector2i myRandomSpawnDimensions;
	};

	struct WaterEntityData
	{
		float myMovementSpeed;
		int myMaxWaterEntitys;
		CU::Vector2i myRandomSpawnDimensions;
	};

	struct LevelData
	{	
		CU::StaticArray<VehicleData, NUM_VEHICLE_TYPES> myVehicleData;
		CU::StaticArray<WaterEntityData, NUM_VEHICLE_TYPES> myWaterEntityData;
	};

	class LevelDataHandler
	{

	public:

		LevelDataHandler();
		~LevelDataHandler();
		void Init();
		LevelData* GetLevelData(Level aLevel);
		
	private:

		void InitVehicleData();
		void InitWaterEntityData();

		CU::StaticArray<LevelData, 2> myLevelData;


	};
};

#endif

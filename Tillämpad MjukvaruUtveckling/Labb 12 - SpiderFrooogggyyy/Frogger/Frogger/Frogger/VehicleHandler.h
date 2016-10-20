#ifndef VEHICLE_HANDLER_HEADER
#define VEHICLE_HANDLER_HEADER

#include "namespaces.h"
#include "Car.h"
#include "GrowingArray.h"
#include "StaticArray.h"
#include "LevelDataHandler.h"

namespace FroggerGame
{   
	struct VehicleRandomSpawnRange
	{
		int myMin;
		int myMax;        
	};

	class Frog;

	class VehicleHandler
	{

	public:

		VehicleHandler();
		~VehicleHandler();
		void Init(LevelData* someLevelData);
		void ReInit(LevelData* someLevelData);
		void Update(Frog* aFrog);
		void Render();

		void CheckForCollision(Frog* aFrog);

	private:

		void InitVehicles();
		void SpawnVehicle(VehicleTypes aType);
		Vehicle* FindAndRemoveAvailableType(VehicleTypes aType);
		

		CU::GrowingArray<Vehicle*> myAvailableVehicles;
		CU::GrowingArray<Vehicle*> myVehiclesInGame;

		CU::StaticArray<float, NUM_VEHICLE_TYPES> mySpawnTimers;
		float myDeltaTime;
		LevelData* myLevelData;
	};
};

#endif

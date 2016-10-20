#ifndef FROGGER_WATER_ENTITY_HANDLER
#define FROGGER_WATER_ENTITY_HANDLER

#include "namespaces.h"
#include "..\hgelibs\include\hge.h"
#include "GrowingArray.h"
#include "StaticArray.h"
#include "defines.h"
#include "Vector2.h"
#include "LevelDataHandler.h"

namespace FroggerGame
{
    struct WaterEntityRandomSpawnRange
    {
        int myMin;
        int myMax;        
    };

	class WaterEntity;
	class Frog;

	class WaterEntityHandler
	{

	public:

		WaterEntityHandler();
		~WaterEntityHandler();
		void Init(LevelData* someLevelData);
		void ReInit(LevelData* someLevelData);
		void Update(Frog* aFrog);
		void Render();

		void CheckForCollision(Frog* aFrog);

		WaterEntity* CheckForCollisionForDesiredPosition(CU::Vector2f aDesiredPosition, bool& aHasCollided);

	private:

        void InitWaterEntitys();
        void SpawnWaterEntity(WaterEntityTypes aType);
        WaterEntity* FindAndRemoveAvailableType(WaterEntityTypes aType);
		

        CU::GrowingArray<WaterEntity*> myAvailableWaterEntitys;
        CU::GrowingArray<WaterEntity*> myWaterEntitysIngame;

        CU::StaticArray<float, NUM_WATER_ENTITY_TYPES> mySpawnTimers;
        float myDeltaTime;
		LevelData* myLevelData;

	};
};

#endif

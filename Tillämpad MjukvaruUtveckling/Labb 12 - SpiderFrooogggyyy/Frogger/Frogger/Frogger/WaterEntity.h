#ifndef FROGGER_WATER_ENTITY_HEADER
#define FROGGER_WATER_ENTITY_HEADER

#include "namespaces.h"
#include "Vector2.h"
#include "..\hgelibs\include\hge.h"
#include "..\hgelibs\include\hgesprite.h"
#include "defines.h"
#include "GrowingArray.h"
#include "Entity.h"

namespace FroggerGame
{
	struct Tile;

	class WaterEntity : public Entity
	{

	public:

		WaterEntity();
		~WaterEntity();
		void Init(CU::Vector2f aPosition, WaterEntityTypes aType);
		virtual void ReInit();
		virtual void Update();
		virtual void Render();

		//CU::Vector2i GetDirection();
		//float GetSpeed();

		inline WaterEntityTypes GetType() {return(myType);}
		inline bool IsOutside() {return(myIsOutside);}

		bool HasCollided(CU::Vector2f aPosition, float aWidth);
		bool IsUnderWater();
		CU::Vector2f GetDesiredPositionFromTiles(CU::Vector2f aPosition);

	protected:

		//void UpdateMovement();
		void UpdateTiles();
		void CheckIfOutside();
		void InitTiles();

		CU::GrowingArray<CU::Vector2f> myTiles;

		WaterEntityTypes myType;
		//CU::Vector2f myPosition;
		//CU::Vector2i myDirection;
		CU::Vector2f myStartPosition;
		//float myMovementSpeed;
		float myDeltaTime;
		//float myWidth;
		int myLength;
		bool myIsOutside;
        bool myIsUnderWater;
		hgeSprite* mySprite;
	};
};

#endif

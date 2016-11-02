#ifndef FROGGER_VEHICLE_HEADER
#define FROGGER_VEHICLE_HEADER

#include "namespaces.h"
#include "Vector2.h"
#include "..\hgelibs\include\hge.h"
#include "..\hgelibs\include\hgesprite.h"
#include "defines.h"
#include "Entity.h"

namespace FroggerGame
{
	struct Tile;

	class Vehicle : public Entity
	{

	public:

		Vehicle();
		~Vehicle();
		void Init(CU::Vector2f aPosition, VehicleTypes aType);
		void ReInit();
		virtual void Update();
		virtual void Render();

		inline VehicleTypes GetType() {return(myType);}
		inline bool IsOutside() {return(myIsOutside);}

		bool HasCollided(CU::Vector2f aPosition, float aWidth);

	protected:

		//void UpdateMovement();
		void CheckIfOutside();

		//Tile* myCurrentTile;
		VehicleTypes myType;
		//CU::Vector2f myPosition;
		//CU::Vector2i myDirection;
		CU::Vector2f myStartPosition;
		//float myMovementSpeed;
		float myDeltaTime;
		//float myWidth;
		bool myIsOutside;
		hgeSprite* mySprite;
	};
};

#endif
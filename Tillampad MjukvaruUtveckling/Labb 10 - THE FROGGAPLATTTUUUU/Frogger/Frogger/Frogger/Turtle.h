#ifndef FROGGER_TURTLE_HEADER
#define FROGGER_TURTLE_HEADER

#include "namespaces.h"
#include "defines.h"
#include "WaterEntity.h"
#include "StaticArray.h"

namespace FroggerGame
{
	class Turtle : public WaterEntity
	{

	public:

		Turtle();
		~Turtle();
		void Init(CU::Vector2f aPosition, WaterEntityTypes aWaterEntityType, bool aIsSubmerging, float aSpeed);
        void ReInit();
		void Update();
		void Render();

	private:

        void HandleSubmerge();
        void Submerge();

		CU::StaticArray<hgeSprite*, 3> mySprites;
        bool myIsSubmerging; 
        bool myIsCurrentlyDiving;
        float mySubmergeTimer;
        float mySubmergeTime;
        float mySubmergeAnimationTime;
        int myCurrentSprite;
	};
};

#endif
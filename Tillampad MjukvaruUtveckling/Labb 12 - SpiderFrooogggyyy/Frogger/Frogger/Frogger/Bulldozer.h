#ifndef FROGGER_BULLDOZER_HEADER
#define FROGGER_BULLDOZER_HEADER

#include "namespaces.h"
#include "Vehicle.h"
#include "StaticArray.h"

namespace FroggerGame
{
	class Bulldozer : public Vehicle
	{

	public:

		Bulldozer();
		~Bulldozer();
		void Init(CU::Vector2f aPosition, float aSpeed);
		void Update();
		void Render();

	private:

		CU::StaticArray<hgeSprite*, 2> mySprites;
		float mySpriteTimer;
		int myCurrentSprite;
	};
};

#endif

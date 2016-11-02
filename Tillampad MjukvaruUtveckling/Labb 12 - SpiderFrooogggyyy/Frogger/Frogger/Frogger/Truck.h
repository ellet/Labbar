#ifndef FROGGER_TRUCK_HEADER
#define FROGGER_TRUCK_HEADER

#include "namespaces.h"
#include "Vehicle.h"

namespace FroggerGame
{
	class Truck : public Vehicle
	{

	public:

		Truck();
		~Truck();
		void Init(CU::Vector2f aPosition, float aSpeed);

	private:

	};
};

#endif

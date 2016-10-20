#ifndef FROGGER_CAR_HEADER
#define FROGGER_CAR_HEADER

#include "namespaces.h"
#include "Vehicle.h"

namespace FroggerGame
{
	class Car : public Vehicle
	{

	public:

		Car();
		~Car();
		void Init(CU::Vector2f aPosition, float aSpeed);

	private:

		
	};
};

#endif

#ifndef FROGGER_BUS_HEADER
#define FROGGER_BUS_HEADER

#include "namespaces.h"
#include "Vehicle.h"

namespace FroggerGame
{
	class Bus : public Vehicle
	{

	public:

		Bus();
		~Bus();
		void Init(CU::Vector2f aPosition, float aSpeed);

	private:

		
	};
};

#endif

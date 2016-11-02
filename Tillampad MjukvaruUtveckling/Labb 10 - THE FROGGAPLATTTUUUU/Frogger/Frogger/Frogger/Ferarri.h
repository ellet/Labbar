#ifndef FROGGER_FERARRI_HEADER
#define FROGGER_FERARRI_HEADER

#include "namespaces.h"
#include "Vehicle.h"

namespace FroggerGame
{
	class Ferarri : public Vehicle
	{

	public:

		Ferarri();
		~Ferarri();
		void Init(CU::Vector2f aPosition, float aSpeed);

	private:

		
	};
};

#endif

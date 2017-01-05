#pragma once
#include "Physics/Objects/Actors/BaseActor.h"

namespace physx
{
	class PxRigidDynamic;
}

namespace SP
{

	class DynamicActor : public BaseActor
	{
	public:
		DynamicActor();
		DynamicActor(const SB::Vector3f & aPosition);
		~DynamicActor();

		void SetVelocity(const SB::Vector3f & aVelocity);

	private:
		physx::PxRigidDynamic * myDynamicActor;
	};

}

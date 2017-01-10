#pragma once
#include "foundation\PxErrorCallback.h"

namespace SP
{
	class PhysicsErrorCallback : public physx::PxErrorCallback
	{
	public:
		PhysicsErrorCallback();
		~PhysicsErrorCallback();

		virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line) override;
	};

}

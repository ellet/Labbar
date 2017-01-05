#include "stdafx.h"
#include "PhysicsErrorCallback.h"

namespace SP
{

	PhysicsErrorCallback::PhysicsErrorCallback()
	{
	}


	PhysicsErrorCallback::~PhysicsErrorCallback()
	{
	}

	void PhysicsErrorCallback::reportError(PxErrorCode::Enum /*code*/, const char* message, const char* file, int line)
	{
		const std::string outputString = SB::FormatString("Physx Error : {0}, in file: {1}, on line {2}.", message, file, line);
		Error(outputString.c_str());
	}

}

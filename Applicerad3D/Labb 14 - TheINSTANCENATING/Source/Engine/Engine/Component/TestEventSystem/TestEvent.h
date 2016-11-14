#pragma once

namespace ENGINE_NAMESPACE
{

	struct TestEvent
	{
		TestEvent(const Vector3f & aTestPos = Vector3f::One) : myTestPos(aTestPos)
		{
		}

		Vector3f myTestPos;
	};

}
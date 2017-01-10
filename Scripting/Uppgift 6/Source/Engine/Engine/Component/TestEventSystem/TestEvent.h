#pragma once

namespace SB
{

	struct TestEvent
	{
		TestEvent(const Vector3f & aTestPos = Vector3f::One) : myTestPos(aTestPos)
		{
		}

		Vector3f myTestPos;
	};

}
#pragma once

namespace SB
{
	struct CollisionData;

	struct CollisionEvent
	{
		CollisionEvent(const CollisionData & aCollisionData) : myCollisionData(&aCollisionData)
		{
		}

		const CollisionData * myCollisionData;
	};

}
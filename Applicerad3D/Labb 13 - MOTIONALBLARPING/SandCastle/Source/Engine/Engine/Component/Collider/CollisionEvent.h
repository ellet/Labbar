#pragma once

namespace ENGINE_NAMESPACE
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
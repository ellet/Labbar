#pragma once

namespace SB
{
	class GameObject;

	struct TriggerCollisionEvent
	{
		TriggerCollisionEvent(const GameObject & aGameObject) : myGameObject(&aGameObject)
		{
		}

		const GameObject * myGameObject;
	};
}

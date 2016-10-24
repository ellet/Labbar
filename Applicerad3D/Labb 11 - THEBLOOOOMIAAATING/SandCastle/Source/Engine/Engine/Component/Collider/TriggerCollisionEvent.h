#pragma once

namespace ENGINE_NAMESPACE
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
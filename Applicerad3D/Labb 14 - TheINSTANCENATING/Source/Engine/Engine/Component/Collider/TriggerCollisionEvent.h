#pragma once

namespace ENGINE_NAMESPACE
{
	class GameObject;
	class SphereCollider;

	struct TriggerCollisionEvent
	{
		TriggerCollisionEvent(const GameObject & aGameObject, const SphereCollider & aCollider, const unsigned short aColliderIndex) : myGameObject(&aGameObject), mySphereCollider(&aCollider), myColliderIndex(aColliderIndex)
		{
		}

		const GameObject * myGameObject;
		const SphereCollider * mySphereCollider;
		unsigned short myColliderIndex;
	};
}
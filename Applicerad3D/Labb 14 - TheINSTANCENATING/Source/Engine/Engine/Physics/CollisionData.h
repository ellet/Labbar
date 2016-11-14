#pragma once

namespace ENGINE_NAMESPACE
{
	class SphereCollider;
	class GameObject;

	struct CollisionData
	{
		CollisionData()
		{
			myDirection = Vector3f::Zero;
			myCollisionPoint = Vector3f::Zero;
			mySpeed = 0.f;
			myColliderIndex = 0;
			myGameObject = nullptr;
		}

		Vector3f myDirection;
		Vector3f myCollisionPoint;
		float mySpeed;
		unsigned short myColliderIndex;
		const GameObject* myGameObject;
	};
}
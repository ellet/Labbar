#pragma once

namespace ENGINE_NAMESPACE
{
	class SphereCollider;
	class GameObject;

	struct CollisionData
	{
		Vector3f myDirection;
		Vector3f myCollisionPoint;
		const GameObject* myGameObject;
	};
}
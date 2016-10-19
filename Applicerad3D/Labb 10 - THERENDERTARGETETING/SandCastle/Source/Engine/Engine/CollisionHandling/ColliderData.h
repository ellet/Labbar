#pragma once

namespace ENGINE_NAMESPACE
{
	class SphereCollider;
	class GameObject;

	struct ColliderData
	{
		bool operator == (const ColliderData& aOtherData)
		{
			return myCollider == aOtherData.myCollider;
		}

		const unsigned int * myCollisionFilter;
		const unsigned int * myLayedID;
		const SphereCollider * myCollider;
		const GameObject * myGameObject;
	};
}
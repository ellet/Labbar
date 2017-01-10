#pragma once

namespace SB
{
	enum class ColliderTypes
	{
		eSphereCollider,
		eCapsuleCollider,
		enumlength
	};


	class SphereCollider;
	class CapsuleCollider;
	class RayCollider;

	class BaseCollider
	{
	public:
		BaseCollider();
		virtual ~BaseCollider();

		virtual void UpdatePosition(const Vector3f & aUpdatePosition) = 0;
		virtual void SetRadius(const float aRadius) = 0;
		virtual float GetRadius() const = 0;


		virtual bool CheckCollisionAgainstCollider(const BaseCollider & aCollider) const = 0;

		virtual bool CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const;

		virtual bool CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const;

		virtual bool CheckCollisionAgainstRay(const RayCollider & aRayCollider) const;
	};


}
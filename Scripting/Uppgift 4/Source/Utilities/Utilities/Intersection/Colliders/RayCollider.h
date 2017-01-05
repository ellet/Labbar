#pragma once

namespace SB
{

	class RayCollider
		: public BaseCollider
	{
	public:
		RayCollider();
		~RayCollider();

		RayCollider(const Vector3f & aPosition, const Vector3f & aDirection) : myPosition(aPosition), myDirection(aDirection)
		{}

		void SetPosition(const Vector3f & aPostion);
		const Vector3f & GetPosition() const;

		LineSegmentShape GetRayAsLineSegment(const float aLength = 3.f) const;

		void SetDirection(const Vector3f & aDirection);
		const Vector3f & GetDirection() const;


		virtual void UpdatePosition(const Vector3f & aUpdatePosition) override;


		virtual void SetRadius(const float aRadius) override;


		virtual float GetRadius() const override;



		virtual bool CheckCollisionAgainstCollider(const BaseCollider & aCollider) const override;

		virtual bool CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const override;

		virtual bool CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const override;

		virtual bool CheckCollisionAgainstRay(const RayCollider & aRayCollider) const override;

	private:
		Vector3f myPosition;
		Vector3f myDirection;
	};

}

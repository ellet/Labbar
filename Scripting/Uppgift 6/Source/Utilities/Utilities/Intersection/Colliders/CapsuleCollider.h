#pragma once

namespace SB
{
	class CapsuleCollider
		: public BaseCollider
	{		
	public:
		CapsuleCollider();
		~CapsuleCollider();

		CapsuleCollider(const Vector3f & aPosition, const Vector3f & aDirectionAndLength, const float aRadius) : myPosition(aPosition), myDirectionAndLength(aDirectionAndLength), myRadius(aRadius)
		{}


		virtual bool CheckCollisionAgainstCollider(const BaseCollider & aCollider) const override;

		virtual bool CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const override;

		virtual bool CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const override;

		virtual bool CheckCollisionAgainstRay(const RayCollider & aRayCollider) const override;

		virtual void UpdatePosition(const Vector3f & aUpdatePosition) override;
		//void SetPosition(const Vector3f & aPostion);
		const Vector3f & GetPosition() const;
		Vector3f GetSecondPosition() const;

		LineSegmentShape GetCapsuleAsLineSegment() const;
		CapsuleShape GetCapsuleAsCapsuleShape() const;

		void SetLengthAndDirection(const Vector3f & aLenghtAndDirection);
		const Vector3f & GetLengthAndDirection() const;

		virtual float GetRadius() const override;
		virtual void SetRadius(const float aRadius) override;

		//void SetDirection(const Vector3f & aDirection);
		const Vector3f GetDirection() const;


	private:
		Vector3f myPosition;
		Vector3f myDirectionAndLength;
		float myRadius;
	};

}

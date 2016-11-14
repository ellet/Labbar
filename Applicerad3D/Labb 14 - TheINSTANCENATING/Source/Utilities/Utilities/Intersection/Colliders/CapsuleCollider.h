#pragma once

namespace ENGINE_NAMESPACE
{
	class CapsuleCollider
	{		
	public:
		CapsuleCollider();
		~CapsuleCollider();

		CapsuleCollider(const Vector3f & aPosition, const Vector3f & aDirectionAndLength, const float aRadius) : myPosition(aPosition), myDirectionAndLength(aDirectionAndLength), myRadius(aRadius)
		{}

		void SetPosition(const Vector3f & aPostion);
		const Vector3f & GetPosition() const;
		Vector3f GetSecondPosition() const;

		LineSegmentShape GetCapsuleAsLineSegment() const;
		CapsuleShape GetCapsuleAsCapsuleShape() const;

		void SetLengthAndDirection(const Vector3f & aLenghtAndDirection);
		const Vector3f & GetLengthAndDirection() const;

		//void SetDirection(const Vector3f & aDirection);
		const Vector3f GetDirection() const;
		float GetRadius() const;

	private:
		Vector3f myPosition;
		Vector3f myDirectionAndLength;
		float myRadius;
	};

}

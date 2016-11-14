#pragma once

namespace ENGINE_NAMESPACE
{

	class RayCollider
	{
	public:
		RayCollider();
		~RayCollider();

		RayCollider(const Vector3f & aPosition, const Vector3f & aDirection) : myPosition(aPosition), myDirection(aDirection)
		{}

		void SetPosition(const Vector3f & aPostion);
		const Vector3f & GetPosition() const;

		LineSegmentShape GetRayAsLineSegment(const float aLength = 3.f);

		void SetDirection(const Vector3f & aDirection);
		const Vector3f & GetDirection() const;

	private:
		Vector3f myPosition;
		Vector3f myDirection;
	};

}

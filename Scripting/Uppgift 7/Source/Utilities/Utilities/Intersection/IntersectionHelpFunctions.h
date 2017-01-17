#pragma once

namespace SB
{

	namespace Intersection
	{

		float DistanceFromLineSegmentToRay(const LineSegmentShape & aLineSegment, const RayCollider & aRayCollider, Vector3f & aCollisionPoint);

		float DistanceFromPointToRay(const RayCollider & aRayCollider, const Vector3f & aPoint);
		
		float DistanceFromPointToLineSegment(const LineSegmentShape & aLineSegment, const Vector3f & aPoint);

		float DistanceFromLineSegmtToLineSegment(
			const LineSegmentShape & aFirstLineSegment,			const LineSegmentShape &	aSecondLineSegment,
			float &					aDistanceAlongFirstLine,	float &						aDistanceAlongSecondLine,
			Vector3f &				aClosestPointOnFirstLine,	Vector3f &					aClosestPointOnSecondLine
		);
	}

}


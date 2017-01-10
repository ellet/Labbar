#include "stdafx.h"
#include "IntersectionHelpFunctions.h"

namespace SB
{

	namespace Intersection
	{
	
		float DistanceFromLineSegmentToRay(const LineSegmentShape & aLineSegment, const RayCollider & aRayCollider, Vector3f & aCollisionPoint)
		{
			float distanceFirst;
			float distanceSecond;
			Vector3f closestPointFirst;
			Vector3f closestPointSecond;
			
			return DistanceFromLineSegmtToLineSegment(aLineSegment, aRayCollider.GetRayAsLineSegment(1000.f), distanceFirst, distanceSecond, closestPointFirst, aCollisionPoint);
		}

		float DistanceFromPointToRay(const RayCollider & aRayCollider, const Vector3f & aPoint)
		{
			// not tested;
			return aRayCollider.GetDirection().Cross(aPoint).Length();
		}

		float DistanceFromPointToLineSegment(const LineSegmentShape & aLineSegment, const Vector3f & aPoint)
		{
			Vector3f ab = aLineSegment.mySecondPosition - aLineSegment.myFirstPosition;
			Vector3f ac = aPoint - aLineSegment.myFirstPosition;
			Vector3f bc = aPoint - aLineSegment.mySecondPosition;

			float e = ac.Dot(ab);

			// Handle cases where c projects outside ab

			if (e <= 0.0f)
			{
				return ac.Dot(ac);
			}

			float f = ab.Dot(ab);

			if (e >= f)
			{
				return bc.Dot(bc);
			}

			// Handle cases where c projects onto ab

			return ac.Dot(ac) - e * e / f;
		}


		float DistanceFromLineSegmtToLineSegment(
			const LineSegmentShape &	aFirstLineSegment,			const LineSegmentShape &	aSecondLineSegment,
			float &						aDistanceAlongFirstLine,	float &						aDistanceAlongSecondLine,
			Vector3f &					aClosestPointOnFirstLine,	Vector3f &					aClosestPointOnSecondLine
		)
		{
			Vector3f d1 = aFirstLineSegment.mySecondPosition - aFirstLineSegment.myFirstPosition; // Direction vector of segment S1

			Vector3f d2 = aSecondLineSegment.mySecondPosition - aSecondLineSegment.myFirstPosition; // Direction vector of segment S2

			Vector3f r = aFirstLineSegment.myFirstPosition - aSecondLineSegment.myFirstPosition;

			float a = Vector3f::Dot(d1, d1); // Squared length of segment S1, always nonnegative

			float e = Vector3f::Dot(d2, d2); // Squared length of segment S2, always nonnegative

			float f = Vector3f::Dot(d2, r);

			// Check if either or both segments degenerate into points

			if (a <= M_EPSILONF && e <= M_EPSILONF)
			{

				// Both segments degenerate into points

				aDistanceAlongFirstLine = aDistanceAlongSecondLine = 0.0f;

				aClosestPointOnFirstLine = aFirstLineSegment.myFirstPosition;

				aClosestPointOnSecondLine = aSecondLineSegment.myFirstPosition;


				return Vector3f::Dot(aClosestPointOnFirstLine - aClosestPointOnFirstLine, aClosestPointOnFirstLine - aClosestPointOnFirstLine);

			}

			if (a <= M_EPSILONF)
			{

				// First segment degenerates into a point

				aDistanceAlongFirstLine = 0.0f;

				aDistanceAlongSecondLine = f / e; // s = 0 => t = (b*s + f) / e = f / e

				aDistanceAlongSecondLine = CLAMP(aDistanceAlongSecondLine, 0.0f, 1.0f);

			}
			else
			{

				float c = Vector3f::Dot(d1, r);

				if (e <= M_EPSILONF)
				{

					// Second segment degenerates into a point

					aDistanceAlongSecondLine = 0.0f;

					aDistanceAlongFirstLine = -c / a;

					aDistanceAlongFirstLine = CLAMP(aDistanceAlongFirstLine, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c / a

				}
				else {

					// The general nondegenerate case starts here

					float b = Vector3f::Dot(d1, d2);

					float denom = a*e - b*b; // Always nonnegative

											 // If segments not parallel, compute closest point on L1 to L2 and

											 // clamp to segment S1. Else pick arbitrary s (here 0)

					if (denom != 0.0f) {

						aDistanceAlongFirstLine = CLAMP((b*f - c*e) / denom, 0.0f, 1.0f);

					}
					else aDistanceAlongFirstLine = 0.0f;

					// Compute point on L2 closest to S1(s) using

					// t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e

					aDistanceAlongSecondLine = (b* aDistanceAlongFirstLine + f) / e;

					// If t in [0,1] done. Else clamp t, recompute s for the new value

					// of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a

					// and clamp s to [0, 1]

					if (aDistanceAlongSecondLine < 0.0f)
					{

						aDistanceAlongSecondLine = 0.0f;

						aDistanceAlongFirstLine = CLAMP(-c / a, 0.0f, 1.0f);

					}
					else if (aDistanceAlongSecondLine > 1.0f) {

						aDistanceAlongSecondLine = 1.0f;

						aDistanceAlongFirstLine = CLAMP((b - c) / a, 0.0f, 1.0f);

					}

				}

			}

			aClosestPointOnFirstLine = aFirstLineSegment.myFirstPosition + d1 * aDistanceAlongFirstLine;

			aClosestPointOnSecondLine = aSecondLineSegment.myFirstPosition + d2 * aDistanceAlongSecondLine;

			return Vector3f::Dot(aClosestPointOnFirstLine - aClosestPointOnSecondLine, aClosestPointOnFirstLine - aClosestPointOnSecondLine);
		}







	}

}
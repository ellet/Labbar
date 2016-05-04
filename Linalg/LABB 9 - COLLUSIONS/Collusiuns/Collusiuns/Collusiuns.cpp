// Collusiuns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "intersection.h"
#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
	Intersection::Sphere sphere;
	Intersection::AABB aabb;
	Intersection::LineSegment3D line;
	Intersection::Fov90Frustum frust(1, 100);

	Vector3<float> intersectionPoint;
	sphere.myCenterPosition = Vector3<float>(100, 100, 100);
	sphere.myRadius = 10;
	sphere.myRadiusSquared = 100;

	aabb.myCenterPos = Vector3<float>(10, 10, 10);
	aabb.myExtents = Vector3<float>(10, 10, 10);
	aabb.myMinPos = Vector3<float>(0, 0, 0);
	aabb.myMaxPos = Vector3<float>(20, 20, 20);


	assert(Intersection::PointInsideSphere(sphere, Vector3<float>(100, 100, 100)) == true);
	assert(Intersection::PointInsideSphere(sphere, Vector3<float>(100, 102, 110)) == false);

	assert(Intersection::PointInsideAABB(aabb, Vector3<float>(100, 100, 100)) == false);
	assert(Intersection::PointInsideAABB(aabb, Vector3<float>(10, 2, 10)) == true);
	assert(Intersection::PointInsideAABB(aabb, Vector3<float>(10, 21, 10)) == false);


	line.myStartPos = Vector3<float>(0, 0, 0);
	line.myEndPos = Vector3<float>(200, 200, 200);


	assert(Intersection::LineVsSphere(line, sphere, intersectionPoint) == true);

	assert(Intersection::SweptSphereVsSphere(line, 0, sphere) == true);
	assert(Intersection::SweptSphereVsSphere(line, 10, sphere) == true);

	line.myEndPos = Vector3<float>(90, 90, 90);

	assert(Intersection::LineVsSphere(line, sphere, intersectionPoint) == false);

	assert(Intersection::SweptSphereVsSphere(line, 10, sphere) == true);
	assert(Intersection::SweptSphereVsSphere(line, 20, sphere) == true);


	line.myEndPos = Vector3<float>(100, 100, 100);

	assert(Intersection::SweptSphereVsSphere(line, 10, sphere) == true);
	assert(Intersection::SweptSphereVsSphere(line, 20, sphere) == true);

	line.myStartPos = Vector3<float>(90, 90, 90);


	assert(Intersection::SweptSphereVsAABB(line, 10, aabb) == false);
	assert(Intersection::SweptSphereVsAABB(line, 20, aabb) == false);
	assert(Intersection::SweptSphereVsAABB(line, 150, aabb) == true);

	line.myStartPos = Vector3<float>(-5, -5, -5);

	assert(Intersection::SweptSphereVsAABB(line, 10, aabb) == true);
	assert(Intersection::SweptSphereVsAABB(line, 20, aabb) == true);
	assert(Intersection::SweptSphereVsAABB(line, 0, aabb) == true);
	assert(Intersection::LineVsAABB(line, aabb, intersectionPoint) == true);

	line.myStartPos = Vector3<float>(-50, -50, -50);
	line.myEndPos = Vector3<float>(-5, -5, -5);


	assert(Intersection::SweptSphereVsAABB(line, 10, aabb) == true);
	assert(Intersection::SweptSphereVsAABB(line, 20, aabb) == true);
	assert(Intersection::SweptSphereVsAABB(line, 0, aabb) == false);
	assert(Intersection::LineVsAABB(line, aabb, intersectionPoint) == false);


	assert(Intersection::SphereVsFrustum(sphere, frust) == true);


	sphere.myCenterPosition = Vector3<float>(-1, -1, -1);
	sphere.myRadius = 10;
	sphere.myRadiusSquared = sphere.myRadius*sphere.myRadius;

	assert(Intersection::SphereVsFrustum(sphere, frust) == true);


	sphere.myCenterPosition = Vector3<float>(-1, -1, -1);
	sphere.myRadius = 0;
	sphere.myRadiusSquared = sphere.myRadius*sphere.myRadius;

	assert(Intersection::SphereVsFrustum(sphere, frust) == false);

	sphere.myCenterPosition = Vector3<float>(-1, -1, 120);
	sphere.myRadius = 10;
	sphere.myRadiusSquared = sphere.myRadius*sphere.myRadius;

	assert(Intersection::SphereVsFrustum(sphere, frust) == false);

	sphere.myCenterPosition = Vector3<float>(-1, -60, 55);
	sphere.myRadius = 10;
	sphere.myRadiusSquared = sphere.myRadius*sphere.myRadius;

	assert(Intersection::SphereVsFrustum(sphere, frust) == true);

	sphere.myCenterPosition = Vector3<float>(-1, -60, 55);
	sphere.myRadius = 0;
	sphere.myRadiusSquared = sphere.myRadius*sphere.myRadius;

	assert(Intersection::SphereVsFrustum(sphere, frust) == false);


	Intersection::LineSegment2D line1, line2;

	line1.myStartPos = Vector2<float>(0, 0);
	line1.myEndPos = Vector2<float>(10, 0);

	line2.myStartPos = Vector2<float>(19, 0);
	line2.myEndPos = Vector2<float>(11, 0);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == false);
	line2.myStartPos = Vector2<float>(-19, 0);
	line2.myEndPos = Vector2<float>(-1, 0);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == false);

	line2.myStartPos = Vector2<float>(-19, 0);
	line2.myEndPos = Vector2<float>(1, 0);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == true);

	line2.myStartPos = Vector2<float>(5, 0);
	line2.myEndPos = Vector2<float>(1, 0);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == true);

	line2.myStartPos = Vector2<float>(5, 5);
	line2.myEndPos = Vector2<float>(5, -5);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == true);

	line2.myStartPos = Vector2<float>(5, 5);
	line2.myEndPos = Vector2<float>(5, 1);

	assert(Intersection::LineVsLine(line1, line2, intersectionPoint) == false);

	/*COOL SHIT*/

	Intersection::AABB coolTESTBOX;
	coolTESTBOX.myCenterPos = Vector3f(0.5f, 0.5f, 0.5f);
	coolTESTBOX.myMinPos = Vector3f::Zero;
	coolTESTBOX.myMaxPos = Vector3f::One;

	Intersection::LineSegment3D COOLSPHERELINE;

	COOLSPHERELINE.myStartPos = Vector3f(-1.0f, 0.f, 0.5f);
	COOLSPHERELINE.myEndPos = Vector3f(-1.0f, 1.f, 0.5f);

	float CoolSPHERERADIUS;
	CoolSPHERERADIUS = 1.1f;

	assert(Intersection::SweptSphereVsAABB(COOLSPHERELINE, CoolSPHERERADIUS, coolTESTBOX) == true && "FUCKING TEST FAIL");


	COOLSPHERELINE.myStartPos = Vector3f(-1.1f, -1.1f, -1.1f);
	COOLSPHERELINE.myEndPos = Vector3f(-5.5f, -5.5f, -5.5f);

	assert(Intersection::SweptSphereVsAABB(COOLSPHERELINE, CoolSPHERERADIUS, coolTESTBOX) == false && "FUCKING TEST SHOULD FAIL WHY NOT FAIL))!");

	return 0;
}




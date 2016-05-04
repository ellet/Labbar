#pragma once
#include <GrowingArray/GrowingArray.h>
#include <Vectors/Vector.h>
#include <Macros/Macros.h>

CommonUtilities::GrowingArray<Vector3f> CreatePlane(Vector2ui& aXYAmount, float aZOffset)
{
	CommonUtilities::GrowingArray<Vector3f> plane;
	unsigned short size = (static_cast<unsigned short>(aXYAmount.x * aXYAmount.y));
	plane.Init(size);

	float xSubdivision = (2 / static_cast<float>(aXYAmount.x));
	float ySubdivision = (2 / static_cast<float>(aXYAmount.y));

	for (size_t columns = 0; columns < aXYAmount.x; ++columns)
	{
		for (size_t rows = 0; rows < aXYAmount.y; ++rows)
		{
			plane.Add(Vector3f(((static_cast<float>(columns)* xSubdivision) - 1 + (xSubdivision / 2)), ((static_cast<float>(rows)* ySubdivision) - 1 + (ySubdivision / 2)), aZOffset));
		}
	}

	return plane;
}


CommonUtilities::GrowingArray<Vector3f> CreateCube(Vector2ui& aXYAmount)
{
	CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<Vector3f>> otherPlanes;

	CommonUtilities::GrowingArray<Vector3f> cube;
	otherPlanes.Init(5);

	cube.Init(20);
	//cube = CreatePlane(Vector2ui(aXYAmount.x, aXYAmount.y), 1.f);
	cube = CreatePlane(aXYAmount, 1.f);


	for (unsigned short i = 0; i < 4; ++i)
	{
		otherPlanes.Add(cube);
	}


	Matrix33f rotation = rotation.CreateRotateAroundY(DEGRESS_TO_RADIANSF(90.f));

	//rotatate one plane
	for (unsigned short i = 0; i < otherPlanes[0].Size(); ++i)
	{
		otherPlanes[0][i] = (otherPlanes[0][i] * rotation);
		cube.Add(otherPlanes[0][i]);
	}

	rotation = rotation.CreateRotateAroundY(DEGRESS_TO_RADIANSF(-90.f));

	//rotatate one plane
	for (unsigned short i = 0; i < otherPlanes[1].Size(); ++i)
	{
		otherPlanes[1][i] = (otherPlanes[1][i] * rotation);
		cube.Add(otherPlanes[1][i]);
	}

	rotation = rotation.CreateRotateAroundX(DEGRESS_TO_RADIANSF(90.f));

	//rotatate one plane
	for (unsigned short i = 0; i < otherPlanes[2].Size(); ++i)
	{
		otherPlanes[2][i] = (otherPlanes[2][i] * rotation);
		cube.Add(otherPlanes[2][i]);
	}

	rotation = rotation.CreateRotateAroundX(DEGRESS_TO_RADIANSF(-90.f));

	//rotatate one plane
	for (unsigned short i = 0; i < otherPlanes[3].Size(); ++i)
	{
		otherPlanes[3][i] = (otherPlanes[3][i] * rotation);
		cube.Add(otherPlanes[3][i]);
	}

	//otherPlanes.Add(CreatePlane(Vector2ui(aXYAmount.x, aXYAmount.y), -1.f));
	otherPlanes.Add(CreatePlane(aXYAmount, -1.f));

	for (unsigned short i = 0; i < otherPlanes[4].Size(); ++i)
	{
		cube.Add(otherPlanes[4][i]);
	}


	return cube;
}

CommonUtilities::GrowingArray<Vector3f> CreateRing(size_t anAmount)
{
	float pi = static_cast<float>( M_PI);
	CommonUtilities::GrowingArray<Vector3f> ring;
	ring.Init(static_cast<unsigned short>(anAmount));
	float angle = (2 * pi / static_cast<float>(anAmount));
	float y; //= std::sin(angle); 
	float x; //= std::cos(angle);

	//ring.Add(Vector3f(x, y, 0.f));

	for (size_t i = 0; i < anAmount; ++i)
	{
		y = std::sin(i * angle);
		x = std::cos(i * angle);
		ring.Add(Vector3f(x, y, 0.f));
	}

	return ring;
}

CommonUtilities::GrowingArray<Vector3f> CreateSphere(size_t aNumberOfRings, size_t aNumberOfSegments)
{
	
	CommonUtilities::GrowingArray<Vector3f> sphere;
	sphere.Init(static_cast<unsigned short>(aNumberOfRings * aNumberOfSegments));
	CommonUtilities::GrowingArray<Vector3f> ring = CreateRing(aNumberOfSegments);

	float pi = static_cast<float>(M_PI);
	float angle = (pi / static_cast<float>(aNumberOfRings));
	Matrix33f rotation = rotation.CreateRotateAroundY(angle);

	for (size_t i = 0; i < aNumberOfRings; ++i)
	{
		for (unsigned short pointstoRotate = 0; pointstoRotate < aNumberOfSegments; ++pointstoRotate)
		{
			sphere.Add((ring[pointstoRotate] * rotation.CreateRotateAroundY(angle *i)));
		}
	}

	return sphere;
}

CommonUtilities::GrowingArray<Vector3f> CreateTorus(size_t aNumberOfRings, size_t aNumberOfSegments, float aCenterSize = 3.f)
{

	CommonUtilities::GrowingArray<Vector3f> torus;
	torus.Init(static_cast<unsigned short>(aNumberOfRings * aNumberOfSegments));
	CommonUtilities::GrowingArray<Vector3f> ring = CreateRing(aNumberOfSegments);
	
	float scale = aCenterSize;

	for (unsigned short i = 0; i < ring.Size(); ++i)
	{
		ring[i].x += scale-1;
		ring[i] /= scale;
	}

	float pi = static_cast<float>(M_PI);
	float angle = (2 * pi / static_cast<float>(aNumberOfRings));
	Matrix33f rotation = rotation.CreateRotateAroundY(angle);

	for (size_t i = 0; i < aNumberOfRings; ++i)
	{
		for (size_t pointstoRotate = 0; pointstoRotate < aNumberOfSegments; ++pointstoRotate)
		{
			torus.Add((ring[static_cast<unsigned short>(pointstoRotate)] * rotation.CreateRotateAroundY(angle *i)));
		}
	}


	return torus;
}
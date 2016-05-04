#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vectors\vector2.h"
#include "Vectors\vector3.h"
#include "LinesAndPlanes\line.h"
#include "LinesAndPlanes\plane.h"
#include "LinesAndPlanes\line_volume.h"
#include "LinesAndPlanes\plane_volume.h"
#include "GrowingArray\GrowingArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template class Vector2< float >;
template class Line< float >;
template class Plane< float >;

namespace LinesAndPlanesTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Plane<float> myTestPlane(Point3<float>(0, 0, 0), Point3<float>(1, 0, 0), Point3<float>(0, 0, 1));

			Assert::IsFalse(myTestPlane.IsInside(Point3<float>(0, 1, 0)));
		}

		TEST_METHOD(TestRemove)
		{
			Plane<float> myTestPlane(Point3<float>(0, 0, 0), Point3<float>(1, 0, 0), Point3<float>(0, 0, 1));

			Assert::IsFalse(myTestPlane.IsInside(Point3<float>(0, 1, 0)));
		}

		TEST_METHOD(TestCollision_Lines_Volume)
		{
			CommonUtilities::GrowingArray<Line<float>> arrayWithCubeIn;
			arrayWithCubeIn.Init(4);
			LineVolume<float> myVolumeOfLines(arrayWithCubeIn);

			myVolumeOfLines.AddLine(Line<float>(Point2f::Zero, Point2<float>(0.f,1.f)));
			myVolumeOfLines.AddLine(Line<float>(Point2<float>(0.f, 1.f), Point2<float>(1.f, 1.f)));
			myVolumeOfLines.AddLine(Line<float>(Point2<float>(1.f, 1.f), Point2<float>(1.f, 0.f)));
			myVolumeOfLines.AddLine(Line<float>(Point2<float>(1.f, 0.f), Point2f::Zero));

			Assert::IsTrue(myVolumeOfLines.Inside(Point2<float>(0.5f, 0.5f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point2<float>(0.1f, 0.1f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point2<float>(1.0f, 1.0f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point2<float>(0.0f, 0.0f)));

			Assert::IsFalse(myVolumeOfLines.Inside(Point2<float>(1.5f, 1.5f)));
			Assert::IsFalse(myVolumeOfLines.Inside(Point2<float>(-1.5f, -1.5f)));
		}

		TEST_METHOD(TestCollision_Planes_Volume)
		{
			CommonUtilities::GrowingArray<Plane<float>> arrayWithCubeIn;
			arrayWithCubeIn.Init(6);
			PlaneVolume<float> myVolumeOfLines(arrayWithCubeIn);

			myVolumeOfLines.AddPlane(Plane<float>(Point3f::Zero, Point3<float>(-1.f, 0.f, 0.f)));
			myVolumeOfLines.AddPlane(Plane<float>(Point3f::Zero, Point3<float>(0.f, -1.f, 0.f)));
			myVolumeOfLines.AddPlane(Plane<float>(Point3f::Zero, Point3<float>(0.f, 0.f, -1.f)));

			myVolumeOfLines.AddPlane(Plane<float>(Point3f::One, Point3<float>(1.f, 0.f, 0.f)));
			myVolumeOfLines.AddPlane(Plane<float>(Point3f::One, Point3<float>(0.f, 1.f, 0.f)));
			myVolumeOfLines.AddPlane(Plane<float>(Point3f::One, Point3<float>(0.f, 0.f, 1.f)));
			

			Assert::IsTrue(myVolumeOfLines.Inside(Point3<float>(0.5f, 0.5f, 0.5f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point3<float>(0.0f, 0.0f, 0.0f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point3<float>(1.f, 1.f, 1.f)));
			Assert::IsTrue(myVolumeOfLines.Inside(Point3<float>(0.1f, 0.5f, 0.5f)));

			Assert::IsFalse(myVolumeOfLines.Inside(Point3<float>(-0.1f, 0.5f, 0.5f)));
			Assert::IsFalse(myVolumeOfLines.Inside(Point3<float>(-50.5f, 7503.5f, 25.5f)));
			Assert::IsFalse(myVolumeOfLines.Inside(Point3<float>(1.1f, 0.5f, 275.5f)));
			
		}
	};
}
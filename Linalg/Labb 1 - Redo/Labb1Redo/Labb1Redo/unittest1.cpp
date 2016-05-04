#include "stdafx.h"
#include "CppUnitTest.h"

#include "Vectors\Vector.h"
//#include "Vectors\vector2.h"
//#include "Vectors\vector3.h"
//#include "Vectors\vector4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Labb1Redo
{		
	TEST_CLASS(UnitTest1)
	{
	public:

#pragma region Vector2
		
		TEST_METHOD(Vector2Default_Constructor)
		{
			Vector2f testVector;

			Assert::AreEqual(testVector.x, 0.f);
			Assert::AreEqual(testVector.y, 0.f);
		}

		TEST_METHOD(Vector2_Assignment_Operator)
		{
			Vector2f testVector1;
			Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;

			testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
		}

		TEST_METHOD(Vector2_Flip_Operator)
		{
			float firstX = 157.7f;
			float firstY = 358.8f;

			Vector2f testVector1(firstX, firstY);
			testVector1 = -testVector1;

			Assert::AreEqual(testVector1.x, -firstX);
			Assert::AreEqual(testVector1.y, -firstY);
		}

		TEST_METHOD(Vector2_Copy_Constructor)
		{
			Vector2f testVector1;
			//Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;

			Vector2f testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
		}

		TEST_METHOD(Vector2_Explicit_cast)
		{
			Vector2i testVector1;
			//Vector2f testVector2;

			testVector1.x = 10;
			testVector1.y = 12;

			Vector2f testVector2 = static_cast<Vector2f>(testVector1);

			Assert::AreEqual(static_cast<float>(testVector1.x), testVector2.x);
			Assert::AreEqual(static_cast<float>(testVector1.y), testVector2.y);
		}

		TEST_METHOD(Vector2_Assigment_Constructor)
		{
			Vector2f testVector(2.4f, 6.4f);

			Assert::AreEqual(testVector.x, 2.4f);
			Assert::AreEqual(testVector.y, 6.4f);
		}

		TEST_METHOD(Vector2_Add_Operator)
		{
			float firstX = 0.1f;
			float firstY = 0.3f;
			
			float secondX = 2.1f;
			float secondY = 9.1f;

			Vector2f testVector1(firstX, firstY);
			Vector2f testVector2(secondX, secondY);

			Vector2f resultVector = testVector1 + testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(resultVector.x, firstX + secondX);
			Assert::AreEqual(resultVector.y, firstY + secondY);
		}

		TEST_METHOD(Vector2_Minus_Operator)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;

			float secondX = 1.7f;
			float secondY = 3.8f;

			Vector2f testVector1(firstX, firstY);
			Vector2f testVector2(secondX, secondY);

			Vector2f resultVector = testVector1 - testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(resultVector.x, firstX - secondX);
			Assert::AreEqual(resultVector.y, firstY - secondY);
		}

		TEST_METHOD(Vector2_Multiple_Operator)
		{
			const float ScalarValue = 3.78f;

			float firstX = 1.7f;
			float firstY = 3.8f;

			Vector2f testVector1(firstX, firstY);
			
			Vector2f resultVector = testVector1 * ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);

			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(resultVector.x, firstX * ScalarValue);
			Assert::AreEqual(resultVector.y, firstY * ScalarValue);
		}

		TEST_METHOD(Vector2_Division_Operator)
		{
			const float ScalarValue = 3.78f;

			float firstX = 157.7f;
			float firstY = 358.8f;

			Vector2f testVector1(firstX, firstY);

			Vector2f resultVector = testVector1 / ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);

			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(resultVector.x, firstX / ScalarValue);
			Assert::AreEqual(resultVector.y, firstY / ScalarValue);
		}

		TEST_METHOD(Static_Vector2_Length2)
		{
			float firstX = 3;
			float firstY = 4;

			Vector2f testVector1(firstX, firstY);

			const float testResult = testVector1.Length2();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(testResult, 25.f);
		}

		TEST_METHOD(Static_Vector2_Length)
		{
			float firstX = 3;
			float firstY = 4;

			Vector2f testVector1(firstX, firstY);

			const float testResult = testVector1.Length();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(testResult, 5.f);
		}

		TEST_METHOD(Vector2_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;

			float secondX = 1.7f;
			float secondY = 3.8f;

			Vector2f testVector1(firstX, firstY);
			Vector2f testVector2(secondX, secondY);

			float resultScalar = testVector1.Dot(testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(resultScalar, manualResult);
		}

		TEST_METHOD(Static_Vector2_Normalize)
		{
			float firstX = 3;
			float firstY = 4;

			Vector2f testVector1(firstX, firstY);

			testVector1.Normalize();

			Assert::AreEqual(testVector1.x, firstX / 5.f );

			Assert::AreEqual(testVector1.y, firstY / 5.f);
		}

		TEST_METHOD(Static_Vector2Get_Normalize)
		{
			float firstX = 3;
			float firstY = 4;

			Vector2f testVector1(firstX, firstY);

			Vector2f testVector2 = testVector1.GetNormalized();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(testVector2.x, firstX / 5.f);

			Assert::AreEqual(testVector2.y, firstY / 5.f);
		}

		TEST_METHOD(Vector2_Static_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;

			float secondX = 1.7f;
			float secondY = 3.8f;

			Vector2f testVector1(firstX, firstY);
			Vector2f testVector2(secondX, secondY);

			float resultScalar = Vector2f::Dot(testVector1, testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(resultScalar, manualResult);
		}

		TEST_METHOD(Static_Vector2_Static_Normalize)
		{
			float firstX = 3;
			float firstY = 4;

			Vector2f testVector1(firstX, firstY);

			Vector2f testVector2 = Vector2f::Normalize(testVector1);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(testVector2.x, firstX / 5.f);

			Assert::AreEqual(testVector2.y, firstY / 5.f);
		}

#pragma endregion

#pragma region Vector3
		
		TEST_METHOD(Vector3_Default_Constructor)
		{
			Vector3f testVector;

			Assert::AreEqual(testVector.x, 0.f);
			Assert::AreEqual(testVector.y, 0.f);
			Assert::AreEqual(testVector.z, 0.f);
		}


		TEST_METHOD(Vector3_Assignment_Operator)
		{
			Vector3f testVector1;
			Vector3f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;

			testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
		}

		TEST_METHOD(Vector3_Flip_Operator)
		{
			float firstX = 157.7f;
			float firstY = 358.8f;
			float firstZ = 24.8f;

			Vector3f testVector1(firstX, firstY, firstZ);
			testVector1 = -testVector1;

			Assert::AreEqual(testVector1.x, -firstX);
			Assert::AreEqual(testVector1.y, -firstY);
			Assert::AreEqual(testVector1.z, -firstZ);
		}

		TEST_METHOD(Vector3_Copy_Constructor)
		{
			Vector3f testVector1;
			//Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;

			Vector3f testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
		}

		TEST_METHOD(Vector4_To_Vector3_Copy_Constructor)
		{
			Vector4f testVector1;
			//Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;
			testVector1.z = 178.2f;

			Vector3f testVector2(testVector1);

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
		}
		
		TEST_METHOD(Vector3_Explicit_cast)
		{
			Vector3i testVector1;
			//Vector2f testVector2;

			testVector1.x = 10;
			testVector1.y = 12;
			testVector1.z = 12;

			Vector3f testVector2 = static_cast<Vector3f>(testVector1);

			Assert::AreEqual(static_cast<float>(testVector1.x), testVector2.x);
			Assert::AreEqual(static_cast<float>(testVector1.y), testVector2.y);
			Assert::AreEqual(static_cast<float>(testVector1.z), testVector2.z);
		}

		
		TEST_METHOD(Vector3_Assigment_Constructor)
		{
			Vector3f testVector(2.4f, 6.4f, 2.2f);

			Assert::AreEqual(testVector.x, 2.4f);
			Assert::AreEqual(testVector.y, 6.4f);
			Assert::AreEqual(testVector.z, 2.2f);
		}

		TEST_METHOD(Vector4_Flip_Operator)
		{
			float firstX = 157.7f;
			float firstY = 358.8f;
			float firstZ = 24.8f;
			float firstW = 298.8f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);
			testVector1 = -testVector1;

			Assert::AreEqual(testVector1.x, -firstX);
			Assert::AreEqual(testVector1.y, -firstY);
			Assert::AreEqual(testVector1.z, -firstZ);
			Assert::AreEqual(testVector1.w, -firstW);
		}
		
		TEST_METHOD(Vector3_Add_Operator)
		{
			float firstX = 0.1f;
			float firstY = 0.3f;
			float firstZ = 0.7f;

			float secondX = 2.1f;
			float secondY = 9.1f;
			float secondZ = 5.3f;

			Vector3f testVector1(firstX, firstY, firstZ);
			Vector3f testVector2(secondX, secondY, secondZ);

			Vector3f resultVector = testVector1 + testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(resultVector.x, firstX + secondX);
			Assert::AreEqual(resultVector.y, firstY + secondY);
			Assert::AreEqual(resultVector.z, firstZ + secondZ);
		}

		
		TEST_METHOD(Vector3_Minus_Operator)
		{
			float firstX = 0.1f;
			float firstY = 0.3f;
			float firstZ = 0.7f;

			float secondX = 2.1f;
			float secondY = 9.1f;
			float secondZ = 5.3f;

			Vector3f testVector1(firstX, firstY, firstZ);
			Vector3f testVector2(secondX, secondY, secondZ);

			Vector3f resultVector = testVector1 - testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(resultVector.x, firstX - secondX);
			Assert::AreEqual(resultVector.y, firstY - secondY);
			Assert::AreEqual(resultVector.z, firstZ - secondZ);
		}

		
		TEST_METHOD(Vector3_Multiple_Operator)
		{
			const float ScalarValue = 3.78f;

			float firstX = 3.1f;
			float firstY = 6.3f;
			float firstZ = 2.7f;

			Vector3f testVector1(firstX, firstY, firstZ);

			Vector3f resultVector = testVector1 * ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);

			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(resultVector.x, firstX * ScalarValue);
			Assert::AreEqual(resultVector.y, firstY * ScalarValue);
			Assert::AreEqual(resultVector.z, firstZ * ScalarValue);
		}

		
		TEST_METHOD(Vector3_Division_Operator)
		{
			const float ScalarValue = 3.78f;

			float firstX = 157.7f;
			float firstY = 358.8f;
			float firstZ = 2.7f;

			Vector3f testVector1(firstX, firstY, firstZ);

			Vector3f resultVector = testVector1 / ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);

			Assert::AreEqual(testVector1.y, firstY);

			Assert::AreEqual(resultVector.x, firstX / ScalarValue);
			Assert::AreEqual(resultVector.y, firstY / ScalarValue);
			Assert::AreEqual(resultVector.z, firstZ / ScalarValue);
		}

		
		TEST_METHOD(Static_Vector3_Length2)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			Vector3f testVector1(firstX, firstY, firstZ);

			const float testResult = testVector1.Length2();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);

			Assert::AreEqual(testResult, 49.f);
		}

		
		TEST_METHOD(Static_Vector3_Length)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			Vector3f testVector1(firstX, firstY, firstZ);

			const float testResult = testVector1.Length();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);

			Assert::AreEqual(testResult, 7.f);
		}

		
		TEST_METHOD(Vector3_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;
			float firstZ = 6.f;

			float secondX = 1.7f;
			float secondY = 3.8f;
			float secondZ = 6.f;

			Vector3f testVector1(firstX, firstY, firstZ);
			Vector3f testVector2(secondX, secondY, secondZ);

			float resultScalar = testVector1.Dot(testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY) + (firstZ * secondZ);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(resultScalar, manualResult);
		}

		
		TEST_METHOD(Static_Vector3_Normalize)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			Vector3f testVector1(firstX, firstY, firstZ);

			testVector1.Normalize();

			Assert::AreEqual(testVector1.x, firstX / 7.f);

			Assert::AreEqual(testVector1.y, firstY / 7.f);

			Assert::AreEqual(testVector1.z, firstZ / 7.f);
		}

		
		TEST_METHOD(Static_Vector3Get_Normalize)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			Vector3f testVector1(firstX, firstY, firstZ);

			Vector3f testVector2 = testVector1.GetNormalized();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);

			Assert::AreEqual(testVector2.x, firstX / 7.f);

			Assert::AreEqual(testVector2.y, firstY / 7.f);

			Assert::AreEqual(testVector2.z, firstZ / 7.f);
		}

		TEST_METHOD(Vector3_Static_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;
			float firstZ = 6.f;

			float secondX = 1.7f;
			float secondY = 3.8f;
			float secondZ = 6.f;

			Vector3f testVector1(firstX, firstY, firstZ);
			Vector3f testVector2(secondX, secondY, secondZ);

			float resultScalar = Vector3f::Dot(testVector1, testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY) + (firstZ * secondZ);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(resultScalar, manualResult);
		}

		
		TEST_METHOD(Static_Vector3_Static_Normalize)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			Vector3f testVector1(firstX, firstY, firstZ);

			Vector3f testVector2 = Vector3f::Normalize(testVector1);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);

			Assert::AreEqual(testVector2.x, firstX / 7.f);

			Assert::AreEqual(testVector2.y, firstY / 7.f);

			Assert::AreEqual(testVector2.z, firstZ / 7.f);
		}

		TEST_METHOD(Static_Vector3_Cross)
		{
			float firstX = 2;
			float firstY = 3;
			float firstZ = 6;

			float secondX = 1.7f;
			float secondY = 3.8f;
			float secondZ = 6.f;

			Vector3f testVector1(firstX, firstY, firstZ);
			Vector3f testVector2(secondX, secondY, secondZ);

			Vector3f testVector3 = Vector3f::Cross(testVector1, testVector2);

			const float ResultX = (firstY * secondZ) - (firstZ * secondY);
			const float ResultY = (firstZ * secondX) - (firstX * secondZ);
			const float ResultZ = (firstX * secondY) - (firstY * secondX);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);

			Assert::AreEqual(testVector3.x, ResultX);

			Assert::AreEqual(testVector3.y, ResultY);

			Assert::AreEqual(testVector3.z, ResultZ);
		}
		

#pragma endregion

#pragma region Vector4
		
		TEST_METHOD(Vector4_Default_Constructor)
		{
			Vector4f testVector;

			Assert::AreEqual(testVector.x, 0.f);
			Assert::AreEqual(testVector.y, 0.f);
			Assert::AreEqual(testVector.z, 0.f);
			Assert::AreEqual(testVector.w, 0.f);
		}

		
		TEST_METHOD(Vector4_Assignment_Operator)
		{
			Vector4f testVector1;
			Vector4f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;
			testVector1.w = 7.2f;

			testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
			Assert::AreEqual(testVector1.w, testVector2.w);
		}

		
		TEST_METHOD(Vector4_Copy_Constructor)
		{
			Vector4f testVector1;
			//Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;
			testVector1.w = 7.2f;

			Vector4f testVector2 = testVector1;

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
		}

		TEST_METHOD(Vector3_To_Vector4_Copy_Constructor)
		{
			Vector3f testVector1;
			//Vector2f testVector2;

			testVector1.x = 10.f;
			testVector1.y = 12.f;
			testVector1.z = 12.2f;
			testVector1.w = 7.2f;

			Vector4f testVector2(testVector1);

			Assert::AreEqual(testVector1.x, testVector2.x);
			Assert::AreEqual(testVector1.y, testVector2.y);
			Assert::AreEqual(testVector1.z, testVector2.z);
			Assert::AreEqual(1.f, testVector2.w);
		}

		
		TEST_METHOD(Vector4_Explicit_cast)
		{
			Vector4i testVector1;
			//Vector2f testVector2;

			testVector1.x = 10;
			testVector1.y = 12;
			testVector1.z = 12;
			testVector1.w = 9;

			Vector4f testVector2 = static_cast<Vector4f>(testVector1);

			Assert::AreEqual(static_cast<float>(testVector1.x), testVector2.x);
			Assert::AreEqual(static_cast<float>(testVector1.y), testVector2.y);
			Assert::AreEqual(static_cast<float>(testVector1.z), testVector2.z);
			Assert::AreEqual(static_cast<float>(testVector1.w), testVector2.w);
		}

		
		TEST_METHOD(Vector4_Assigment_Constructor)
		{
			Vector4f testVector(2.4f, 6.4f, 2.2f, 1.9f);

			Assert::AreEqual(testVector.x, 2.4f);
			Assert::AreEqual(testVector.y, 6.4f);
			Assert::AreEqual(testVector.z, 2.2f);
			Assert::AreEqual(testVector.w, 1.9f);
		}

		
		TEST_METHOD(Vector4_Add_Operator)
		{
			float firstX = 0.1f;
			float firstY = 0.3f;
			float firstZ = 0.7f;
			float firstW = 77.3f;

			float secondX = 2.1f;
			float secondY = 9.1f;
			float secondZ = 5.3f;
			float secondW = 21.3f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);
			Vector4f testVector2(secondX, secondY, secondZ, secondW);

			Vector4f resultVector = testVector1 + testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(testVector1.w, firstW);
			Assert::AreEqual(testVector2.w, secondW);

			Assert::AreEqual(resultVector.x, firstX + secondX);
			Assert::AreEqual(resultVector.y, firstY + secondY);
			Assert::AreEqual(resultVector.z, firstZ + secondZ);
			Assert::AreEqual(resultVector.w, firstW + secondW);
		}

		
		TEST_METHOD(Vector4_Minus_Operator)
		{
			float firstX = 0.1f;
			float firstY = 0.3f;
			float firstZ = 0.7f;
			float firstW = 77.3f;

			float secondX = 2.1f;
			float secondY = 9.1f;
			float secondZ = 5.3f;
			float secondW = 21.3f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);
			Vector4f testVector2(secondX, secondY, secondZ, secondW);

			Vector4f resultVector = testVector1 - testVector2;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(testVector1.w, firstW);
			Assert::AreEqual(testVector2.w, secondW);

			Assert::AreEqual(resultVector.x, firstX - secondX);
			Assert::AreEqual(resultVector.y, firstY - secondY);
			Assert::AreEqual(resultVector.z, firstZ - secondZ);
			Assert::AreEqual(resultVector.w, firstW - secondW);
		}

		
		TEST_METHOD(Vector4_Multiple_Operator)
		{
			const float ScalarValue = 3.78f;

			float firstX = 3.1f;
			float firstY = 6.3f;
			float firstZ = 2.7f;
			float firstW = 2.9f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			Vector4f resultVector = testVector1 * ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(resultVector.x, firstX * ScalarValue);
			Assert::AreEqual(resultVector.y, firstY * ScalarValue);
			Assert::AreEqual(resultVector.z, firstZ * ScalarValue);
			Assert::AreEqual(resultVector.w, firstW * ScalarValue);
		}

		TEST_METHOD(Vector4_Division_Operator)
		{
			const float ScalarValue = 78.78f;

			float firstX = 3.1f;
			float firstY = 6.3f;
			float firstZ = 2.7f;
			float firstW = 2.9f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			Vector4f resultVector = testVector1 / ScalarValue;

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(resultVector.x, firstX / ScalarValue);
			Assert::AreEqual(resultVector.y, firstY / ScalarValue);
			Assert::AreEqual(resultVector.z, firstZ / ScalarValue);
			Assert::AreEqual(resultVector.w, firstW / ScalarValue);
		}

		
		TEST_METHOD(NonStatic_Vector4_Length2)
		{
			float firstX = 3.f;
			float firstY = 4.f;
			float firstZ = 7.f;
			float firstW = 9.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			const float TestCompare = (firstX * firstX) + (firstY * firstY) + (firstZ * firstZ) + (firstW * firstW);

			const float testResult = testVector1.Length2();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(testResult, TestCompare);
		}


		
		TEST_METHOD(Static_Vector4_Length)
		{
			float firstX = 3.f;
			float firstY = 4.f;
			float firstZ = 7.f;
			float firstW = 9.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			const float TestCompare = sqrt((firstX * firstX) + (firstY * firstY) + (firstZ * firstZ) + (firstW * firstW));

			const float testResult = testVector1.Length();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(testResult, TestCompare);
		}

		
		TEST_METHOD(Vector4_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;
			float firstZ = 6.f;
			float firstW = 9.f;

			float secondX = 1.7f;
			float secondY = 3.8f;
			float secondZ = 6.f;
			float secondW = 78.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);
			Vector4f testVector2(secondX, secondY, secondZ, secondW);

			float resultScalar = testVector1.Dot(testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY) + (firstZ * secondZ) + (firstW * secondW);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(testVector1.w, firstW);
			Assert::AreEqual(testVector2.w, secondW);

			Assert::AreEqual(resultScalar, manualResult);
		}

		
		TEST_METHOD(Static_Vector4_Normalize)
		{
			float firstX = 3.f;
			float firstY = 4.f;
			float firstZ = 7.f;
			float firstW = 9.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			const float TestCompare = sqrt((firstX * firstX) + (firstY * firstY) + (firstZ * firstZ) + (firstW * firstW));

			testVector1.Normalize();

			Assert::AreEqual(testVector1.x, firstX / TestCompare);
			Assert::AreEqual(testVector1.y, firstY / TestCompare);
			Assert::AreEqual(testVector1.z, firstZ / TestCompare);
			Assert::AreEqual(testVector1.w, firstW / TestCompare);
		}

		
		TEST_METHOD(Static_Vector4_Get_Normalize)
		{
			float firstX = 3.f;
			float firstY = 4.f;
			float firstZ = 7.f;
			float firstW = 9.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			const float TestCompare = sqrt((firstX * firstX) + (firstY * firstY) + (firstZ * firstZ) + (firstW * firstW));

			Vector4f testVector2 = testVector1.GetNormalized();

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(testVector2.x, firstX / TestCompare);
			Assert::AreEqual(testVector2.y, firstY / TestCompare);
			Assert::AreEqual(testVector2.z, firstZ / TestCompare);
			Assert::AreEqual(testVector2.w, firstW / TestCompare);
		}

		
		TEST_METHOD(Vector4_Static_Dot_Produkt)
		{
			float firstX = 5.1f;
			float firstY = 33.3f;
			float firstZ = 6.f;
			float firstW = 9.f;

			float secondX = 1.7f;
			float secondY = 3.8f;
			float secondZ = 6.f;
			float secondW = 78.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);
			Vector4f testVector2(secondX, secondY, secondZ, secondW);

			float resultScalar = Vector4f::Dot(testVector1, testVector2);

			float manualResult = (firstX * secondX) + (firstY * secondY) + (firstZ * secondZ) + (firstW * secondW);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector2.x, secondX);

			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector2.y, secondY);

			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector2.z, secondZ);

			Assert::AreEqual(testVector1.w, firstW);
			Assert::AreEqual(testVector2.w, secondW);

			Assert::AreEqual(resultScalar, manualResult);
		}

		
		TEST_METHOD(Static_Vector4_Static_Normalize)
		{
			float firstX = 3.f;
			float firstY = 4.f;
			float firstZ = 7.f;
			float firstW = 9.f;

			Vector4f testVector1(firstX, firstY, firstZ, firstW);

			const float TestCompare = sqrt((firstX * firstX) + (firstY * firstY) + (firstZ * firstZ) + (firstW * firstW));

			Vector4f testVector2 = Vector4f::Normalize(testVector1);

			Assert::AreEqual(testVector1.x, firstX);
			Assert::AreEqual(testVector1.y, firstY);
			Assert::AreEqual(testVector1.z, firstZ);
			Assert::AreEqual(testVector1.w, firstW);

			Assert::AreEqual(testVector2.x, firstX / TestCompare);
			Assert::AreEqual(testVector2.y, firstY / TestCompare);
			Assert::AreEqual(testVector2.z, firstZ / TestCompare);
			Assert::AreEqual(testVector2.w, firstW / TestCompare);
		}

#pragma endregion
	};
}
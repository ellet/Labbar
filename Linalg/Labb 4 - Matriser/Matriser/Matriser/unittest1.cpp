#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Matriser\matrix44.h"
#include "Matriser\matrix33.h"
#include <random>
#include <iostream>
#include <array>
#include "Vectors\vector4.h"
#include "Vectors\vector3.h"
#include "Macros\Macros.h"

template class Matrix44< float > ;
//template class Matrix33< float >;

namespace Matriser
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		std::random_device RandomDevice;
		std::mt19937 RandomGenerator; 

		Matrix44f MatrixWith2s;

		Matrix44f MatrixWith4s;
		
		Matrix44f MatrisWithPREATLYALLTHENUMBERS;

		Matrix44f MatrisSTAGGERINGIDENTITY;

		Matrix44<int> MatrixWithI3s;


		Matrix33f MatrixWith2s33;

		Matrix33f MatrixWith4s33;

		Matrix33f MatrisWithPREATLYALLTHENUMBERS33;

		Matrix33f MatrisSTAGGERINGIDENTITY33;

		Matrix33<int> MatrixWithI3s33;


		TEST_CLASS_INITIALIZE(derp)
		{
			//RandomGenerator = std::mt19937((RandomDevice()));
			//std::uniform_real_distribution<float> NumbersGet(-100.0f, 100.0f);
		}


		TEST_METHOD_INITIALIZE(methodName)
		{
#pragma region init 44
			for (size_t iSlot = 0; iSlot < MatrixWith2s.NumElements; ++iSlot)
			{
				MatrixWith2s.myMatrix[iSlot] = 2.f;
			}

			for (size_t iSlot = 0; iSlot < MatrixWith4s.NumElements; ++iSlot)
			{
				MatrixWith4s.myMatrix[iSlot] = 4.f;
			}

			for (size_t iSlot = 0; iSlot < MatrixWithI3s.NumElements; ++iSlot)
			{
				MatrixWithI3s.myMatrix[iSlot] = 3;
			}

			MatrisWithPREATLYALLTHENUMBERS = Matrix44f(
				1.f, 2.f, 3.f, 4.f,
				5.f, 6.f, 7.f, 8.f,
				9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f);

			MatrisSTAGGERINGIDENTITY = Matrix44f(
				1.f, 0.f, 0.f, 0.f,
				0.f, 2.f, 0.f, 0.f,
				0.f, 0.f, 3.f, 0.f,
				0.f, 0.f, 0.f, 4.f);
#pragma endregion

#pragma region init 33
			for (size_t iSlot = 0; iSlot < MatrixWith2s33.NumElements; ++iSlot)
			{
				MatrixWith2s33.myMatrix[iSlot] = 2.f;
			}

			for (size_t iSlot = 0; iSlot < MatrixWith4s33.NumElements; ++iSlot)
			{
				MatrixWith4s33.myMatrix[iSlot] = 4.f;
			}

			for (size_t iSlot = 0; iSlot < MatrixWithI3s33.NumElements; ++iSlot)
			{
				MatrixWithI3s33.myMatrix[iSlot] = 3;
			}

			MatrisWithPREATLYALLTHENUMBERS33 = Matrix33f(
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f,
				7.f, 8.f, 9.f);

			MatrisSTAGGERINGIDENTITY33 = Matrix33f(
				1.f, 0.f, 0.f,
				0.f, 2.f, 0.f,
				0.f, 0.f, 3.f
				);
#pragma endregion
		}

#pragma region Matris44
		TEST_METHOD(TestMatris44Constructor)
		{
			Matrix44f testMatris;

			Assert::AreEqual(testMatris.m11, 1.f);
			Assert::AreEqual(testMatris.m22, 1.f);
			Assert::AreEqual(testMatris.m33, 1.f);
			Assert::AreEqual(testMatris.m44, 1.f);

			float testNumber = 0.f;

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				testNumber += testMatris.myMatrix[iSlot];
			}

			Assert::AreEqual(testNumber, 4.f);
		}

		TEST_METHOD(TestMatris44CopyConstructor)
		{
			Matrix44f testMatris(MatrixWith2s);

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}

		TEST_METHOD(TestMatris44CopyConstructorOfOtherType)
		{
			Matrix44f testMatris(MatrixWithI3s);

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 3.f);
			}
		}

		TEST_METHOD(TestMatris44ArrayCopyConstructor)
		{
			float prettyArrayOf9fs[Matrix44f::NumElements];

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				prettyArrayOf9fs[iSlot] = 9.f;
			}

			Matrix44f testMatris(prettyArrayOf9fs);

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 9.f);
			}
		}

		TEST_METHOD(TestMatris44ContructorWithMANYTHIUNGS)
		{
			Matrix44f testMatris(
				1.f, 2.f, 3.f, 4.f,
				5.f, 6.f, 7.f, 8.f,
				9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f);

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], iSlot + 1.f);
			}
		}

		TEST_METHOD(TestMatris4PLUSEQUALSOPERATOR)
		{
			Matrix44f testMatris(MatrixWith2s);

			testMatris += MatrixWith2s;

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}
		}

		TEST_METHOD(TestMatris4MINUSEQUALSOPERATOR)
		{
			Matrix44f testMatris(MatrixWith4s);

			testMatris -= MatrixWith2s;

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}

		TEST_METHOD(TestMatris4MULTIPLYQUALSOPERATOR)
		{
			Matrix44f testMatris;
			Matrix44f testMatris2;

			testMatris *= testMatris2;

			Assert::AreEqual(testMatris.m11, 1.f);
			Assert::AreEqual(testMatris.m22, 1.f);
			Assert::AreEqual(testMatris.m33, 1.f);
			Assert::AreEqual(testMatris.m44, 1.f);

			float testNumber = 0.f;

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				testNumber += testMatris.myMatrix[iSlot];
			}

			Assert::AreEqual(testNumber, 4.f);
		}

		TEST_METHOD(TestMatris4EQUALSOPERATOR)
		{
			Matrix44f testMatris;

			testMatris = MatrixWith4s;

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}
			
		}

		TEST_METHOD(TestMatris4OVERLOADFÖRÄDLRAR_I_IS)
		{
			Matrix44f testMatris;

			Assert::AreEqual(testMatris(1,1), 1.f);
			Assert::AreEqual(testMatris(2,2), 1.f);
			Assert::AreEqual(testMatris(3,3), 1.f);
			Assert::AreEqual(testMatris(4,4), 1.f);
			Assert::AreEqual(testMatris(2, 3), 0.f);
			Assert::AreEqual(testMatris(1, 4), 0.f);
			
		}

		TEST_METHOD(TestMatris4TRANSA_GÖR_POSE)
		{
			MatrisWithPREATLYALLTHENUMBERS.Transpose();

			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(1, 1), 1.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(2, 1), 5.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(3, 1), 9.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(4, 1), 13.f);

			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(1, 2), 2.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(2, 2), 6.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(3, 2), 10.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(4, 2), 14.f);

			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(1, 3), 3.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(2, 3), 7.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(3, 3), 11.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(4, 3), 15.f);

			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(1, 4), 4.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(2, 4), 8.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(3, 4), 12.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS(4, 4), 16.f);

		}

		TEST_METHOD(TestMatris4vectorvictorvector)
		{
			Vector4f DAPRITTIESTSVector = Vector4f(1.f, 1.f , 1.f, 1.f);

			Vector4f NEJYLWA = DAPRITTIESTSVector * MatrisSTAGGERINGIDENTITY;

			Assert::AreEqual(NEJYLWA.x, 1.f);
			Assert::AreEqual(NEJYLWA.y, 2.f);
			Assert::AreEqual(NEJYLWA.z, 3.f);
			Assert::AreEqual(NEJYLWA.w, 4.f);

		}

		/*
		ALLT ÄR YLvAS FEL!tfc gvbfrtygh nrbcdk nb6o 6n 64o5 nj5 no n nm nm
		
		*/

		TEST_METHOD(TestMatris4ROTETERARUNTX)
		{
			Matrix44f rotateX = Matrix44f::CreateRotateAroundX( M_PI / 2 );

			Vector4f CalculateVector = Vector4f(0.f, 0.f, 1.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateX;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);
			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);
			
			Assert::IsTrue(resultVector.y > -1 - epsilon && resultVector.y < -1 + epsilon);
		}

		TEST_METHOD(TestMatris4ROTETERARUNTX45)
		{
			Matrix44f rotateX = Matrix44f::CreateRotateAroundX(M_PI / 4);

			Vector4f CalculateVector = Vector4f(0.f, 0.f, 1.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateX;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.z > 0.70710678118654752440084436210485 - epsilon && resultVector.z < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);

			Assert::IsTrue(resultVector.y > -0.70710678118654752440084436210485f - epsilon && resultVector.y < -0.70710678118654752440084436210485f + epsilon);
		}

		TEST_METHOD(TestMatris4ROTETERARUNTY)
		{
			Matrix44f rotateY = Matrix44f::CreateRotateAroundY(M_PI / 2);

			Vector4f CalculateVector = Vector4f(1.f, 0.f, 0.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateY;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.y > 0 - epsilon && resultVector.y < 0 + epsilon);
			
			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);

			Assert::IsTrue(resultVector.z > -1 - epsilon && resultVector.z < -1 + epsilon);
		}

		TEST_METHOD(TestMatris4ROTETERARUNTY45)
		{
			Matrix44f rotateY = Matrix44f::CreateRotateAroundY(M_PI / 4);

			Vector4f CalculateVector = Vector4f(1.f, 0.f, 0.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateY;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0.70710678118654752440084436210485 - epsilon && resultVector.x < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.z > -0.70710678118654752440084436210485 - epsilon && resultVector.z < -0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);

			Assert::IsTrue(resultVector.y > 0 - epsilon && resultVector.y < 0 + epsilon);
		}

		TEST_METHOD(TestMatris4ROTETERARUNTZ)
		{
			Matrix44f rotateZ = Matrix44f::CreateRotateAroundZ(M_PI / 2);

			Vector4f CalculateVector = Vector4f(1.f, 0.f, 0.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateZ;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.y > 1 - epsilon && resultVector.y < 1 + epsilon);

			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);

			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);
		}

		TEST_METHOD(TestMatris4ROTETERARUNTZ45)
		{
			Matrix44f rotateZ = Matrix44f::CreateRotateAroundZ(M_PI / 4);

			Vector4f CalculateVector = Vector4f(1.f, 0.f, 0.f, 0.f);

			Vector4f resultVector = CalculateVector * rotateZ;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0.70710678118654752440084436210485 - epsilon && resultVector.x < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.y > 0.70710678118654752440084436210485 - epsilon && resultVector.y < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.w > 0 - epsilon && resultVector.w < 0 + epsilon);

			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);
		}

		TEST_METHOD(TestMatris4COPYCAT_TRANSA_GÖR_POSE)
		{
			
			Matrix44f copyCat = Matrix44f::Transpose(MatrisWithPREATLYALLTHENUMBERS);

			Assert::AreEqual(copyCat(1, 1), 1.f);
			Assert::AreEqual(copyCat(2, 1), 5.f);
			Assert::AreEqual(copyCat(3, 1), 9.f);
			Assert::AreEqual(copyCat(4, 1), 13.f);

			Assert::AreEqual(copyCat(1, 2), 2.f);
			Assert::AreEqual(copyCat(2, 2), 6.f);
			Assert::AreEqual(copyCat(3, 2), 10.f);
			Assert::AreEqual(copyCat(4, 2), 14.f);

			Assert::AreEqual(copyCat(1, 3), 3.f);
			Assert::AreEqual(copyCat(2, 3), 7.f);
			Assert::AreEqual(copyCat(3, 3), 11.f);
			Assert::AreEqual(copyCat(4, 3), 15.f);

			Assert::AreEqual(copyCat(1, 4), 4.f);
			Assert::AreEqual(copyCat(2, 4), 8.f);
			Assert::AreEqual(copyCat(3, 4), 12.f);
			Assert::AreEqual(copyCat(4, 4), 16.f);

		}

		TEST_METHOD(TestMatris4CopyPLUSEQUALSOPERATOR)
		{
			Matrix44f testMatris = MatrixWith2s + MatrixWith2s;

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}
		}

		TEST_METHOD(TestMatris4CopyMINUSEQUALSOPERATOR)
		{
			Matrix44f testMatris = MatrixWith4s - MatrixWith2s;

			for (size_t iSlot = 0; iSlot < Matrix44f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}


		TEST_METHOD(TestMatris4CopyCOMPAREOPERATOR)
		{
			Matrix44f testMatris(MatrixWith4s);

			int apa = 1234;
			int merApa = 4321;

			if (testMatris == MatrixWith4s)
			{
				apa = 1;
			}

			if (testMatris != MatrixWith2s)
			{
				merApa = 1;
			}

			Assert::AreEqual(apa, 1);
			Assert::AreEqual(merApa, 1);

		}

		TEST_METHOD(TestMatris44CopyConstructorWith33)
		{
			Matrix44f testMatrix(MatrisWithPREATLYALLTHENUMBERS33);

			Assert::AreEqual(testMatrix.m11, 1.f);
			Assert::AreEqual(testMatrix.m12, 2.f);
			Assert::AreEqual(testMatrix.m13, 3.f);
			Assert::AreEqual(testMatrix.m14, 0.f);

			Assert::AreEqual(testMatrix.m21, 4.f);
			Assert::AreEqual(testMatrix.m22, 5.f);
			Assert::AreEqual(testMatrix.m23, 6.f);
			Assert::AreEqual(testMatrix.m24, 0.f);

			Assert::AreEqual(testMatrix.m31, 7.f);
			Assert::AreEqual(testMatrix.m32, 8.f);
			Assert::AreEqual(testMatrix.m33, 9.f);
			Assert::AreEqual(testMatrix.m34, 0.f);

			Assert::AreEqual(testMatrix.m41, 0.f);
			Assert::AreEqual(testMatrix.m42, 0.f);
			Assert::AreEqual(testMatrix.m43, 0.f);
			Assert::AreEqual(testMatrix.m44, 1.f);
		}
#pragma endregion

#pragma region Matris33
		TEST_METHOD(TestMatris33Constructor)
		{
			Matrix33f testMatris;

			Assert::AreEqual(testMatris.m11, 1.f);
			Assert::AreEqual(testMatris.m22, 1.f);
			Assert::AreEqual(testMatris.m33, 1.f);

			float testNumber = 0.f;

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				testNumber += testMatris.myMatrix[iSlot];
			}

			Assert::AreEqual(testNumber, 3.f);
		}

		TEST_METHOD(TestMatris33CopyConstructor)
		{
			Matrix33f testMatris(MatrixWith2s33);

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}

		TEST_METHOD(TestMatris33CopyConstructorOfOtherType)
		{
			Matrix33f testMatris(MatrixWithI3s33);

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 3.f);
			}
		}

		TEST_METHOD(TestMatris33ArrayCopyConstructor)
		{
			float prettyArrayOf9fs[Matrix33f::NumElements];

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				prettyArrayOf9fs[iSlot] = 9.f;
			}

			Matrix33f testMatris(prettyArrayOf9fs);

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 9.f);
			}
		}

		TEST_METHOD(TestMatris33ContructorWithMANYTHIUNGS)
		{
			Matrix33f testMatris(
				1.f, 2.f, 3.f,
				4.f, 5.f, 6.f, 
				7.f, 8.f, 9.f );

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], iSlot + 1.f);
			}
		}

		TEST_METHOD(TestMatris3PLUSEQUALSOPERATOR)
		{
			Matrix33f testMatris(MatrixWith2s33);

			testMatris += MatrixWith2s33;

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}
		}

		TEST_METHOD(TestMatris3MINUSEQUALSOPERATOR)
		{
			Matrix33f testMatris(MatrixWith4s33);

			testMatris -= MatrixWith2s33;

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}

		TEST_METHOD(TestMatris3MULTIPLYQUALSOPERATOR)
		{
			Matrix33f testMatris;
			Matrix33f testMatris2;

			testMatris *= testMatris2;

			Assert::AreEqual(testMatris.m11, 1.f);
			Assert::AreEqual(testMatris.m22, 1.f);
			Assert::AreEqual(testMatris.m33, 1.f);

			float testNumber = 0.f;

			for (size_t iSlot = 0; iSlot < testMatris.NumElements; ++iSlot)
			{
				testNumber += testMatris.myMatrix[iSlot];
			}

			Assert::AreEqual(testNumber, 3.f);
		}

		TEST_METHOD(TestMatris3EQUALSOPERATOR)
		{
			Matrix33f testMatris;

			testMatris = MatrixWith4s33;

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}

		}

		TEST_METHOD(TestMatris3OVERLOADFÖRÄDLRAR_I_IS)
		{
			Matrix33f testMatris;

			Assert::AreEqual(testMatris(1, 1), 1.f);
			Assert::AreEqual(testMatris(2, 2), 1.f);
			Assert::AreEqual(testMatris(3, 3), 1.f);
			Assert::AreEqual(testMatris(2, 3), 0.f);

		}

		TEST_METHOD(TestMatris3TRANSA_GÖR_POSE)
		{
			MatrisWithPREATLYALLTHENUMBERS33.Transpose();

			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(1, 1), 1.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(2, 1), 4.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(3, 1), 7.f);
			
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(1, 2), 2.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(2, 2), 5.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(3, 2), 8.f);
														   
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(1, 3), 3.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(2, 3), 6.f);
			Assert::AreEqual(MatrisWithPREATLYALLTHENUMBERS33(3, 3), 9.f);

		}

		TEST_METHOD(TestMatris3vectorvictorvector)
		{
			Vector3f DAPRITTIESTSVector = Vector3f(1.f, 1.f, 1.f);

			Vector3f NEJYLWA = DAPRITTIESTSVector * MatrisSTAGGERINGIDENTITY33;

			Assert::AreEqual(NEJYLWA.x, 1.f);
			Assert::AreEqual(NEJYLWA.y, 2.f);
			Assert::AreEqual(NEJYLWA.z, 3.f);

		}

		/*
		ALLT ÄR YLvAS FEL!tfc gvbfrtygh nrbcdk nb6o 6n 64o5 nj5 no n nm nm
		OCH LINUS ÄR LÖSNINGEN
		*/

		TEST_METHOD(TestMatris3ROTETERARUNTX)
		{
			Matrix33f rotateX = Matrix33f::CreateRotateAroundX(M_PI / 2);

			Vector3f CalculateVector = Vector3f(0.f, 0.f, 1.f);

			Vector3f resultVector = CalculateVector * rotateX;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);

			Assert::IsTrue(resultVector.y > -1 - epsilon && resultVector.y < -1 + epsilon);
		}

		TEST_METHOD(TestMatris3ROTETERARUNTX45)
		{
			Matrix33f rotateX = Matrix33f::CreateRotateAroundX(M_PI / 4);

			Vector3f CalculateVector = Vector3f(0.f, 0.f, 1.f);

			Vector3f resultVector = CalculateVector * rotateX;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.z > 0.70710678118654752440084436210485 - epsilon && resultVector.z < 0.70710678118654752440084436210485 + epsilon);

			Assert::IsTrue(resultVector.y > -0.70710678118654752440084436210485f - epsilon && resultVector.y < -0.70710678118654752440084436210485f + epsilon);
		}

		TEST_METHOD(TestMatris3ROTETERARUNTY)
		{
			Matrix33f rotateY = Matrix33f::CreateRotateAroundY(M_PI / 2);

			Vector3f CalculateVector = Vector3f(1.f, 0.f, 0.f);

			Vector3f resultVector = CalculateVector * rotateY;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.y > 0 - epsilon && resultVector.y < 0 + epsilon);


			Assert::IsTrue(resultVector.z > -1 - epsilon && resultVector.z < -1 + epsilon);
		}

		TEST_METHOD(TestMatris3ROTETERARUNTY45)
		{
			Matrix33f rotateY = Matrix33f::CreateRotateAroundY(M_PI / 4);

			Vector3f CalculateVector = Vector3f(1.f, 0.f, 0.f);

			Vector3f resultVector = CalculateVector * rotateY;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0.70710678118654752440084436210485 - epsilon && resultVector.x < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.z > -0.70710678118654752440084436210485 - epsilon && resultVector.z < -0.70710678118654752440084436210485 + epsilon);

			Assert::IsTrue(resultVector.y > 0 - epsilon && resultVector.y < 0 + epsilon);
		}

		TEST_METHOD(TestMatris3ROTETERARUNTZ)
		{
			Matrix33f rotateZ = Matrix33f::CreateRotateAroundZ(M_PI / 2);

			Vector3f CalculateVector = Vector3f(1.f, 0.f, 0.f);

			Vector3f resultVector = CalculateVector * rotateZ;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0 - epsilon && resultVector.x < 0 + epsilon);
			Assert::IsTrue(resultVector.y > 1 - epsilon && resultVector.y < 1 + epsilon);


			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);
		}

		TEST_METHOD(TestMatris3ROTETERARUNTZ45)
		{
			Matrix33f rotateZ = Matrix33f::CreateRotateAroundZ(M_PI / 4);

			Vector3f CalculateVector = Vector3f(1.f, 0.f, 0.f);

			Vector3f resultVector = CalculateVector * rotateZ;

			float epsilon = 0.0001f;

			Assert::IsTrue(resultVector.x > 0.70710678118654752440084436210485 - epsilon && resultVector.x < 0.70710678118654752440084436210485 + epsilon);
			Assert::IsTrue(resultVector.y > 0.70710678118654752440084436210485 - epsilon && resultVector.y < 0.70710678118654752440084436210485 + epsilon);

			Assert::IsTrue(resultVector.z > 0 - epsilon && resultVector.z < 0 + epsilon);
		}

		TEST_METHOD(TestMatris3COPYCAT_TRANSA_GÖR_POSE)
		{

			Matrix33f copyCat = Matrix33f::Transpose(MatrisWithPREATLYALLTHENUMBERS33);

			Assert::AreEqual(copyCat(1, 1), 1.f);
			Assert::AreEqual(copyCat(2, 1), 4.f);
			Assert::AreEqual(copyCat(3, 1), 7.f);
							 
			Assert::AreEqual(copyCat(1, 2), 2.f);
			Assert::AreEqual(copyCat(2, 2), 5.f);
			Assert::AreEqual(copyCat(3, 2), 8.f);
							 
			Assert::AreEqual(copyCat(1, 3), 3.f);
			Assert::AreEqual(copyCat(2, 3), 6.f);
			Assert::AreEqual(copyCat(3, 3), 9.f);

		}

		TEST_METHOD(TestMatris3CopyPLUSEQUALSOPERATOR)
		{
			Matrix33f testMatris = MatrixWith2s33 + MatrixWith2s33;

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 4.f);
			}
		}

		TEST_METHOD(TestMatris3CopyMINUSEQUALSOPERATOR)
		{
			Matrix33f testMatris = MatrixWith4s33 - MatrixWith2s33;

			for (size_t iSlot = 0; iSlot < Matrix33f::NumElements; ++iSlot)
			{
				Assert::AreEqual(testMatris.myMatrix[iSlot], 2.f);
			}
		}


		TEST_METHOD(TestMatris3CopyCOMPAREOPERATOR)
		{
			Matrix33f testMatris(MatrixWith4s33);

			int apa = 1234;
			int merApa = 4321;

			if (testMatris == MatrixWith4s33)
			{
				apa = 1;
			}

			if (testMatris != MatrixWith2s33)
			{
				merApa = 1;
			}

			Assert::AreEqual(apa, 1);
			Assert::AreEqual(merApa, 1);

		}

		TEST_METHOD(TestMatris33CopyConstructorWith44)
		{
			Matrix33f testMatrix(MatrisWithPREATLYALLTHENUMBERS);

			Assert::AreEqual(testMatrix.m11, 1.f);
			Assert::AreEqual(testMatrix.m12, 2.f);
			Assert::AreEqual(testMatrix.m13, 3.f);

			Assert::AreEqual(testMatrix.m21, 5.f);
			Assert::AreEqual(testMatrix.m22, 6.f);
			Assert::AreEqual(testMatrix.m23, 7.f);

			Assert::AreEqual(testMatrix.m31, 9.f);
			Assert::AreEqual(testMatrix.m32, 10.f);
			Assert::AreEqual(testMatrix.m33, 11.f);
		}
#pragma endregion

	};
}
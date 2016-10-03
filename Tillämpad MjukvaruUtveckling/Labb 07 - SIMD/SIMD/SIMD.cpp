// SIMD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <memory>
#include <Windows.h>
#include <iostream>
#include "Vector4.h"
#include "Matrix44.h"
#include "Time.h"
#include "Stopwatch.h"

Matrix44f MultiplySimd(const Matrix44f & aLeft, const Matrix44f & aRight)
{
	Matrix44f newMatrix;
	__m128 a, b, sum;

	__m128 firstRow = _mm_load_ps(&aLeft.myMatrix[0]);

	for (int i = 0; i < 16; i += 4)
	{
		// unroll the first step of the loop to avoid having to initialize r_line to zero
		b = _mm_set1_ps(aRight.myMatrix[i]);      // b.xyzw = row[i].xxxx
		sum = _mm_mul_ps(firstRow, b); // sum = firstRow * b

		{
			a = _mm_load_ps(&aLeft.myMatrix[0]); // a = vec4(row(a, j))
			b = _mm_set1_ps(aRight.myMatrix[i + 0]); // b.xyzw = row[i / 4].xxxx
			
			// Add a * b to sum
			sum = _mm_add_ps(_mm_mul_ps(a, b), sum);
		}
		{
			a = _mm_load_ps(&aLeft.myRows[1].myElements[0]); // a_line = vec4(row(a, j))
			b = _mm_set1_ps(aRight.myMatrix[i + 1]); // b.xyzw = row[i / 4].yyyy

			// Add a * b to sum
			sum = _mm_add_ps(_mm_mul_ps(a, b), sum);
		}
		{
			a = _mm_load_ps(&aLeft.myRows[2].myElements[0]); // a_line = vec4(row(a, j))
			b = _mm_set1_ps(aRight.myMatrix[i + 2]);  // b.xyzw = row[i / 4].zzzz

			// Add a * b to sum
			sum = _mm_add_ps(_mm_mul_ps(a, b), sum);
		}
		{
			a = _mm_load_ps(&aLeft.myRows[3].myElements[0]); // a_line = vec4(row(a, j))
			b = _mm_set1_ps(aRight.myMatrix[i + 3]);  // b.xyzw = row[i / 4].wwww

			// Add a * b to sum
			sum = _mm_add_ps(_mm_mul_ps(a, b), sum);
		}

		_mm_store_ps(&newMatrix.myMatrix[i], sum);     // row[i / 4] = sum
	}

	return newMatrix;
}

float RandomFloat()
{
	return -100.f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 200.f;
}

int main()
{
	auto randomMatrices = std::make_unique<std::array<Matrix44f, 1000000>>();

	for (size_t i = 0; i < randomMatrices->size(); i++)
	{
		(*randomMatrices)[i] = Matrix44f(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
			RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
			RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
			RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
	}

	//for (;;)
	{
		Matrix44f regularResult;
		Matrix44f simdResult;

		Stopwatch timer;

		for (size_t i = 0; i < randomMatrices->size(); i += 2)
		{
			const Matrix44f &a = randomMatrices->at(i),
				&b = randomMatrices->at(i + 1);

			regularResult = regularResult * (a * b);
		}

		Time regularTime = timer.GetElapsedTime();
		timer.Restart();

		for (size_t i = 0; i < randomMatrices->size(); i += 2)
		{
			const Matrix44f &a = randomMatrices->at(i),
				&b = randomMatrices->at(i + 1);

			simdResult = MultiplySimd(simdResult, MultiplySimd(a, b));
		}

		Time simdTime = timer.GetElapsedTime();

		std::cout << "Regular and SIMD does produce the same result!" << std::endl;
		if (regularResult != simdResult)
		{
			// Optimization
			system("cls");
			std::cout << "Regular and SIMD does not produce the same result! =(" << std::endl;
		}

		std::cout << "Regular time: " << regularTime.InMilliseconds() << "ms" << std::endl;
		std::cout << "SIMD time: " << simdTime.InMilliseconds() << "ms" << std::endl;
	}

	std::cin.get();
    return 0;
}


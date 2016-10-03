// SIMDmatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix44.h"
#include <time.h>
#include <windows.h>
#include <iostream>

int main()
{
	LARGE_INTEGER freq, pc;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&pc);

	float myFrequency = static_cast<float>(freq.QuadPart);

	Matrix44f matWOSimd, matWSimd, 
		matMulA(10.f, 3.f, 8.f, 2.f, 9.f, 3.f, 9.f, 16.f, 2.f, 9.f, 23.f, 4.f, 2.f, 7.f, 6.f, 4.f), 
		matMulB(5.f, 2.f, 6.f, 4.f, 8.f, 12.f, 16.f, 9.f, 1.f, 1.f, 3.f, 5.f, 10.f, 8.f, 3.f, 8.f);

	LONGLONG myStartTime = pc.QuadPart;
	//-------- normal
	std::cout << "Starting to calculate normal matrix multiplication..." << std::endl;
	for (unsigned int i = 0; i < 1000000; ++i)
	{
		matWOSimd = matMulA * matMulB;
	}
	
	QueryPerformanceCounter(&pc);
	float timeTakenInSecondsNormal = (static_cast<float>(pc.QuadPart - myStartTime) / myFrequency);
	//----------------
	//-------- SIMD
	std::cout << "Seconds taken for normal multiplication : " << timeTakenInSecondsNormal << std::endl;
	std::cout << "\nStarting to calculate SIMD matrix multiplication..." << std::endl;
	QueryPerformanceCounter(&pc);
	myStartTime = pc.QuadPart;
	for (unsigned int i = 0; i < 1000000; ++i)
	{
		matWSimd.MulSIMD(matMulA, matMulB);
	}

	QueryPerformanceCounter(&pc);
	float timeTakenInSecondsSIMD = (static_cast<float>(pc.QuadPart - myStartTime) / myFrequency);
	//---------------
	std::cout << "Seconds taken for SIMD multiplication : " << timeTakenInSecondsSIMD << std::endl;

	if (matWOSimd == matWSimd)
	{
		std::cout << "And matrices are equal" << std::endl;
	}
	else
	{
		std::cout << "And matrices are NOT equal, ERROOOOR!! :c" << std::endl;
	}
	std::cout << "\nAdditionally, the differences in time is extreme in debug. Like, 11 : 1 seconds." << std::endl;
	system("pause");

    return 0;
}


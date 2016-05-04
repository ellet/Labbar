// Macros.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include <Macros.h>


int main()
{
	int test = 10;
	int test2 = 20;

	PRINT_VARIABLE(test);
	PRINT_VARIABLE(test2);

	std::cout << std::endl;

	std::cout << "Smallest value is: " << MIN(test, test2) << std::endl;
	std::cout << "Biggest value is: " << MAX(test, test2) << std::endl;

	std::cout << std::endl;

	std::vector<int> testvector = { 10, 20, 30, 40, 50 };
	
	std::cout << "Vector is size: " << testvector.size() << std::endl;
	std::cout << "Position1 is: " << testvector[1] << std::endl;
	std::cout << "Last Position is: " << testvector[VECTOR_POSITION_SIZE(testvector)] << std::endl;

	std::cout << std::endl;

	VECTOR_CYCLE_ERASE(testvector, 1);

	std::cout << "Vector is size: " << testvector.size() << std::endl;
	std::cout << "Position1 is: " << testvector[1] << std::endl;
	std::cout << "Last Position is: " << testvector[VECTOR_POSITION_SIZE(testvector)] << std::endl;

	std::cout << std::endl;

	std::cout << "Clamp on range: " << test << ", " << 0 << ", " << 5;

	std::cout << " is " << CLAMP(test, 0, 5) << std::endl;
	std::cout << std::endl;

	std::cout << "Clamp on range: " << test << ", " << 500 << ", " << 100000;

	std::cout << " is " << CLAMP(test, 500, 100000);
	std::cout << std::endl;

	std::cout << "Clamp on range: " << test << ", " << 0 << ", " << 30;

	std::cout << " is " << CLAMP(test, 0, 30);
	std::cout << std::endl;
	
	int firstVariable = 25;
	int secondVariable = 50;

	PRINT_VARIABLE(firstVariable);
	std::cout << std::endl;
	PRINT_VARIABLE(secondVariable);
	std::cout << std::endl;
	SWAP(firstVariable, secondVariable);

	PRINT_VARIABLE(firstVariable);
	std::cout << std::endl;
	PRINT_VARIABLE(secondVariable);
	std::cout << std::endl;

	int * aPointer = new int(500);

	PRINT_VARIABLE(aPointer);

	std::cout << std::endl;

	SAFE_DELETE(aPointer);

	std::cout << std::endl;

	PRINT_VARIABLE(aPointer);

    system("pause");
}
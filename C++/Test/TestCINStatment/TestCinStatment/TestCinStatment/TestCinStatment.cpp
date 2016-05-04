// TestCinStatment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int main()
{
	int sum = 0, value = 0;

	while (std::cin >> value)
	{
		sum += value;
	}

	std::cout << "sum is: " << sum << std::endl;
	system("pause");
	return 0;
}


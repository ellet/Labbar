// TupleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <string>

template <typename T>
T PopTop();

template <>
int PopTop<int>()
{
	return 10;
}

template <>
float PopTop<float>()
{
	return 34.74f;
}

template <>
std::string PopTop<std::string>()
{
	return "test apa";
}

template<typename... ret>
std::tuple<ret...> ReturnValues()
{
	return std::make_tuple(PopTop<ret>()...);
}

int main()
{

	std::tuple<int, float, std::string> testTuple = ReturnValues<int, float, std::string>();
	std::cout << std::get<0>(testTuple) << std::endl;
	std::cout << std::get<1>(testTuple) << std::endl;
	std::cout << std::get<2>(testTuple) << std::endl;

	int intValue = 0;
	float floatValue = 0;
	std::string charValue = "";

	std::tie(intValue, floatValue, charValue) = ReturnValues<int, float, std::string>();
	std::cout << intValue << std::endl;
	std::cout << floatValue << std::endl;
	std::cout << charValue << std::endl;


	std::system("pause");

    return 0;
}


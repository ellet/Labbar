#pragma once
#include <iostream>
#include <string>

#define PRINT_ERROR(aError) std::cout << aError;
#define Error(e) { std::string _errorString = "Error in execution:\r\n"; _errorString += e; _errorString += "\r\nAt "; _errorString += __FILE__; _errorString += ":"; _errorString += std::to_string(__LINE__); std::cout << _errorString << std::endl; MessageBoxA(nullptr, _errorString.c_str(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY); terminate(); }

inline void ProgressMessage(const std::string aMessage)
{
	std::cout << aMessage << std::endl;
}

inline void SomethingWentWrongMessage(const std::string aMessage)
{
	std::cout << aMessage << std::endl;
	
	std::system("pause");
}
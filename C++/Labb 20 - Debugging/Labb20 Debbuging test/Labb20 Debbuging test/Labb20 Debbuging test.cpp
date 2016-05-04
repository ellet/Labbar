// Labb20 Debbuging test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

std::string getCurrentTimeAsString();

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << getCurrentTimeAsString();

	std::string test2 = getCurrentTimeAsString();
	test2 += ".txt";
	//std::string test = "Tue Dec 01 12-27-47 2015";
	//std::string test = getCurrentTimeAsString();

	std::ofstream ofs(test2, std::ofstream::out);

	system("pause");
}

std::string getCurrentTimeAsString()
{
	struct tm newtime;
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.

	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}

	// Convert to an ASCII representation. 
	err = asctime_s(timebuf, 26, &newtime);
	if (err)
	{
		printf("Invalid argument to asctime_s.");
		exit(1);
	}
	
	std::string removeColons = timebuf;

	removeColons.resize(removeColons.size() - 1);

	for (size_t iChar = 0; iChar < removeColons.size(); ++iChar)
	{
		if (removeColons[iChar] == ':')
		{
			removeColons[iChar] = '-';
		}
	}	
	
	return removeColons;
}
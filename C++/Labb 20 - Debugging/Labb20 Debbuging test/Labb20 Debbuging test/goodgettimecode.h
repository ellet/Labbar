#include <time.h>
#include <fstream>

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
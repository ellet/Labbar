#pragma once
#include <vector>
#include "../Structs/name_and_description.h"
class NameHolder
{
public:
	NameHolder();
	~NameHolder();

	NameAndDescription GetAName();

	void AddNamesToHold(const std::vector<NameAndDescription> & aVectorOfNames);

private:
	std::vector<NameAndDescription> myHeldNames;

	unsigned int myOutOfNamesCounter;
};


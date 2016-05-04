#pragma once
#include <../CommonUtilities/GrowingArray/GrowingArray.h>
#include "../Levels/Border.h"
class JsonSaver
{
public:
	JsonSaver();
	void SaveToFile(CommonUtilities::GrowingArray<Border> aBorderList, std::string aLevelName);
	~JsonSaver();
};


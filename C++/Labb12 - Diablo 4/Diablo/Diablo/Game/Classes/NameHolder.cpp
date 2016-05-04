#include "stdafx.h"
#include "NameHolder.h"
#include "../HelpFunctions/HelpFunctions.h"

NameHolder::NameHolder()
{
	myOutOfNamesCounter = 0;
}


NameHolder::~NameHolder()
{
}

NameAndDescription NameHolder::GetAName()
{
	if (myHeldNames.size() > 0)
	{
		const unsigned int randomSlot = static_cast<unsigned int>(l1functions::math::GetRandomNumber(static_cast<int>(myHeldNames.size())));
		NameAndDescription nameHolder = myHeldNames[randomSlot];
		myHeldNames.erase(myHeldNames.begin() + randomSlot);
		
		return nameHolder;
	}
	else
	{
		++myOutOfNamesCounter;
		NameAndDescription tempNameDesc;
		tempNameDesc.name = "Default name number: " + l1functions::ConvertNumberToString(static_cast<int>(myOutOfNamesCounter));
		tempNameDesc.description = "Default description number: " + l1functions::ConvertNumberToString(static_cast<int>(myOutOfNamesCounter));
		return tempNameDesc;
	}
}

void NameHolder::AddNamesToHold(const std::vector<NameAndDescription>& aVectorOfNames)
{
	myHeldNames = aVectorOfNames;
}

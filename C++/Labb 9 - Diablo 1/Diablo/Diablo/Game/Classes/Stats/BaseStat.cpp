#include "stdafx.h"
#include "BaseStat.h"
#include "../../HelpFunctions/HelpFunctions.h"
#include "../../HelpFunctions/enumfunctions.h"

BaseStat::BaseStat()
{
	myBaseValue = 20;
	myType = enumStatTypes::enumLength;
	myName = "BaseState Default";
	
	RecalculateValue();
}

BaseStat::~BaseStat()
{
}

unsigned int BaseStat::GetStatValue() const
{
	return myValue;
}


void BaseStat::TimeCheckBuffs(const unsigned int aTurnCount)
{
	for (unsigned int iBuff = 0; iBuff < myTempBuffs.size(); ++iBuff)
	{
		if (myTempBuffs[iBuff].CheckIfExpired(aTurnCount))
		{
			RemoveTempBuff(iBuff);
			--iBuff;
		}
	}
}


void BaseStat::IncreaseStat(unsigned int aIncreaseAmount)
{
	myBaseValue += aIncreaseAmount;
}

void BaseStat::DecreaseStat(unsigned int aIncreaseAmount)
{
	if (aIncreaseAmount < myBaseValue)
	{
		myBaseValue -= aIncreaseAmount;
	}
	else
	{
		myBaseValue = 1;
	}
}

void BaseStat::SetType(const enumStatTypes aStatType)
{
	myType = aStatType;

	SetStatName();
}

std::string BaseStat::GetPrintStringOfStat() const
{
	std::string tempString = myName + " is: " + l1functions::ConvertNumberToString(static_cast<int>(myValue));
	if (GetMainBuffCount() > 0)
	{
		tempString += " main buff count " + l1functions::ConvertNumberToString(static_cast<int>(GetMainBuffCount()));
	}
	if (GetTempBuffCount() > 0)
	{
		tempString += " temp buff count " + l1functions::ConvertNumberToString(static_cast<int>(GetTempBuffCount()));
	}

	return tempString;
}

void BaseStat::AddMainBuff(const Buff & aBuffToAdd)
{
	myMainBuffs.push_back(aBuffToAdd);
	RecalculateValue();
}

void BaseStat::AddTempBuff(const Buff & aBuffToAdd)
{
	myTempBuffs.push_back(aBuffToAdd);
	RecalculateValue();
}

void BaseStat::SetStat(const unsigned int aValueToSet)
{
	myBaseValue = aValueToSet;
	RecalculateValue();
}


unsigned int BaseStat::GetMainBuffCount() const
{
	return static_cast<unsigned int>(myMainBuffs.size());
}

unsigned int BaseStat::GetTempBuffCount() const
{
	return static_cast<unsigned int>(myTempBuffs.size());
}



void BaseStat::ClearMainBuffs()
{
	myMainBuffs.clear();
}

void BaseStat::RemoveTempBuff(unsigned int aTempBuffIndex)
{
	l1functions::console::PrintToConsole("Buff Expired");
	myTempBuffs.erase(myTempBuffs.begin() + aTempBuffIndex);
	RecalculateValue();
	system("pause");
}

void BaseStat::RecalculateValue()
{
	myValue = myBaseValue + Buff::GetSumOfBuffVector(myMainBuffs) + Buff::GetSumOfBuffVector(myTempBuffs);
}

void BaseStat::SetStatName()
{
	enumutility::GetStringFromEnum(myType, myName);
}
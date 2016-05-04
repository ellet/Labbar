#include "stdafx.h"
#include "VitalStat.h"
#include "../../HelpFunctions/enumfunctions.h"
#include "../../HelpFunctions/HelpFunctions.h"

VitalStat::VitalStat(const enumVitalTypes aVitalType)
{
	SetType(aVitalType);

	myVitalValue = 1.f;
	myBaseValue = 1.f;
	myMaxVital = 1.f;
	myVitalIsPositive = true;
}


VitalStat::~VitalStat()
{
}

void VitalStat::TimeCheckBuffs(const unsigned int aTurnCount)
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

void VitalStat::GetPrintOfVital(std::string & aStringToAddTo) const
{
	aStringToAddTo = myName + " is: " + l1functions::ConvertNumberToString((myVitalValue));



	if (GetMainBuffCount() > 0)
	{
		aStringToAddTo += " main buff count " + l1functions::ConvertNumberToString(static_cast<int>(GetMainBuffCount()));
	}
	if (GetTempBuffCount() > 0)
	{
		aStringToAddTo += " temp buff count " + l1functions::ConvertNumberToString(static_cast<int>(GetTempBuffCount()));
	}
}

void VitalStat::RemoveTempBuff(unsigned int aTempBuffIndex)
{
	myTempBuffs.erase(myTempBuffs.begin() + aTempBuffIndex);
}

void VitalStat::SetType(const enumVitalTypes aVitalType)
{
	myType = aVitalType;
	SetNameFromType();
}

void VitalStat::SetVital(const float aVitalValue, const bool aKeepPercentage)
{
	if (aKeepPercentage == false)
	{
		myVitalValue = myMaxVital;
		myBaseValue = aVitalValue;
	}
	else
	{
		myBaseValue = aVitalValue;
	}

	RecalculateValue();
}

void VitalStat::ChangeVital(const float aChangeWith)
{
	myVitalValue += aChangeWith;

	CheckVitalIsCorrect();
	CheckVital();
}

enumVitalTypes VitalStat::GetVitalType() const
{
	return myType;
}

float VitalStat::GetVitalValue() const
{
	return myVitalValue;
}

bool VitalStat::GetVitalState() const
{
	return myVitalIsPositive;
}

float VitalStat::GetVitalhPercentage() const
{
	return myVitalValue / myMaxVital;
}

void VitalStat::RecalculateValue()
{
	const float CurrentPercentage = GetVitalhPercentage();

	myMaxVital = myBaseValue + static_cast<float>(Buff::GetSumOfBuffVector(myMainBuffs)) + static_cast<float>(Buff::GetSumOfBuffVector(myTempBuffs));
	
	myVitalValue = CurrentPercentage * myMaxVital;
}

void VitalStat::AddMainBuff(const Buff & aBuffToAdd)
{
	myMainBuffs.push_back(aBuffToAdd);
}

void VitalStat::AddTempBuff(const Buff & aBuffToAdd)
{
	myTempBuffs.push_back(aBuffToAdd);
}

unsigned int VitalStat::GetMainBuffCount() const
{
	return static_cast<unsigned int>(myMainBuffs.size());
}

unsigned int VitalStat::GetTempBuffCount() const
{
	return static_cast<unsigned int>(myTempBuffs.size());
}

void VitalStat::ClearMainBuffs()
{
	myMainBuffs.clear();
}

void VitalStat::SetNameFromType()
{
	enumutility::GetStringFromEnum(myType, myName);
}

void VitalStat::CheckVitalIsCorrect()
{
	if (myBaseValue > myMaxVital)
	{
		myBaseValue = myMaxVital;
	}
}

void VitalStat::CheckVital()
{
	if (myVitalValue <= 0)
	{
		myVitalIsPositive = false;
	}
}
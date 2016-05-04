#include "stdafx.h"
#include "VitalsManager.h"
#include "../../HelpFunctions/HelpFunctions.h"

VitalsManager::VitalsManager()
{
	CreateAllVitals();
}


VitalsManager::~VitalsManager()
{
}

void VitalsManager::PrintVitals() const
{
	std::vector<std::string> myStatPrints;

	for (unsigned int iStat = 0; iStat < myVitals.size(); ++iStat)
	{
		std::string tempString;
		myVitals[iStat].GetPrintOfVital(tempString);
		
		myStatPrints.push_back(tempString);
	}

	l1functions::console::PrintVectorOfStrings(myStatPrints);
}

bool VitalsManager::GetVitalState(const enumVitalTypes aVitalToCheck) const
{
	return myVitals[static_cast<unsigned int>(aVitalToCheck)].GetVitalState();
}

void VitalsManager::IncreaseVital(const float aIncreaseWith, const enumVitalTypes aVitalToIncrease)
{
	SetVital(GetVitalValue(aVitalToIncrease) + aIncreaseWith , aVitalToIncrease);
}

void VitalsManager::SetVital(const float aValueToSetTo, const enumVitalTypes aVitalToSet)
{
	myVitals[static_cast<unsigned int>(aVitalToSet)].SetVital(aValueToSetTo);
}

void VitalsManager::ReceiveMainBuffs(const std::vector<Buff>& aVectorOfStatBuffs)
{
	ClearAllMainBuffs();


	for (unsigned int iBuff = 0; iBuff < aVectorOfStatBuffs.size(); ++iBuff)
	{
		AddMainBuffToVital(aVectorOfStatBuffs[iBuff]);
	}
}

void VitalsManager::AddMainBuffToVital(const Buff aBuffToAdd)
{
	myVitals[static_cast<unsigned int>(aBuffToAdd.GetVitalType())].AddMainBuff(aBuffToAdd);
}

void VitalsManager::AddTempBuffToVital(const Buff aBuffToAdd)
{
	myVitals[static_cast<unsigned int>(aBuffToAdd.GetVitalType())].AddTempBuff(aBuffToAdd);
}

float VitalsManager::GetVitalValue(const enumVitalTypes aVitalType) const
{
	return myVitals[static_cast<unsigned int>(aVitalType)].GetVitalValue();
}

void VitalsManager::TimeCheckTrigger(const unsigned int aTurnCount)
{
	for (unsigned int iVital = 0; iVital <  myVitals.size(); ++iVital)
	{
		myVitals[iVital].TimeCheckBuffs(aTurnCount);
	}
}

void VitalsManager::ChangeVital(const float aValueToChangeWith, const enumVitalTypes aVitalToChange)
{
	myVitals[static_cast<unsigned int>(aVitalToChange)].ChangeVital(aValueToChangeWith);
}

VitalStat & VitalsManager::GetVitalStat(const enumVitalTypes aVitalToGet)
{
	return myVitals[static_cast<unsigned int>(aVitalToGet)];
}

void VitalsManager::ClearAllMainBuffs()
{
	for (unsigned int iVital= 0; iVital < myVitals.size(); ++iVital)
	{
		myVitals[iVital].ClearMainBuffs();
	}
}

void VitalsManager::CreateAllVitals()
{
	myVitals.clear();

	for (unsigned int iVital = 0; iVital < static_cast<unsigned int>(enumVitalTypes::enumLength); ++iVital)
	{
		myVitals.push_back(VitalStat(static_cast<enumVitalTypes>(iVital)));
	}
}

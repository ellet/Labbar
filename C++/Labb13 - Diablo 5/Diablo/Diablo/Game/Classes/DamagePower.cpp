#include "stdafx.h"
#include "DamagePower.h"
#include "../HelpFunctions/HelpFunctions.h"
#include "../HelpFunctions/enumfunctions.h"

DamagePower::DamagePower(enumAttackTypes aAttackType)
{
	myDamage.maxDamage = 20.f;
	myDamage.minDamage = 10.f;

	myStaminaCost = 1.f;
	myAttackType = aAttackType;

	enumutility::GetStringFromEnum(myAttackType, myName.name);

	myName.description = "default attack Description";
}


DamagePower::~DamagePower()
{
}

void DamagePower::SetStaminaCost(const float aStaminaCost)
{
	myStaminaCost = aStaminaCost;
}

float DamagePower::GetStaminaCost() const
{
	return myStaminaCost;
}

const float DamagePower::GetDamageToDeal() const
{
	if (myDamage.maxDamage == myDamage.minDamage)
	{
		return myDamage.minDamage;
	}
	else if (myDamage.minDamage < myDamage.maxDamage)
	{
		return l1functions::math::GetRandomNumber(myDamage.maxDamage, myDamage.minDamage);
	}
	else
	{
		l1functions::console::PrintErrorToConsole("Min Damage is bigger then max damage");
		return 0;
	}
}

void DamagePower::GetPrintOfDamageRange(std::string & aStringToPrint) const
{
	if (myDamage.maxDamage == myDamage.minDamage)
	{
		aStringToPrint += l1functions::ConvertNumberToString(myDamage.minDamage);
	}
	else
	{
		aStringToPrint += l1functions::ConvertNumberToString(myDamage.minDamage);
		aStringToPrint += " - ";
		aStringToPrint += l1functions::ConvertNumberToString(myDamage.maxDamage);
	}
}

void DamagePower::SetDamage(MinMaxDamage aDamageRange)
{
	myDamage = aDamageRange;
}

enumAttackTypes DamagePower::GetAttackType() const
{
	return myAttackType;
}

void DamagePower::SetName(std::string & aNewName)
{
	myName.name = aNewName;
}

void DamagePower::GetName(std::string & aStringToChange) const
{
	aStringToChange += myName.name;
}


#include "stdafx.h"
#include "enumfunctions.h"
#include "../HelpFunctions/HelpFunctions.h"


namespace enumutility
{
	void GetStringFromEnum(const enumAttackTypes aAttackType, std::string & aStringToChange)
	{
		switch (aAttackType)
		{
		case enumAttackTypes::eNormalAttack:
			aStringToChange = "Physical attack";
			break;
		case enumAttackTypes::eMagicAttack:
			aStringToChange = "Magic attack";
			break;
		default:
			l1functions::console::PrintErrorToConsole("Attacktype print is out of range");
			break;
		}
	}


	void GetStringFromEnum(const enumChestOpeningOptions aStatType, std::string & aStringToChange)
	{
		switch (aStatType)
		{
		case enumChestOpeningOptions::eBruteForce:
			aStringToChange = "Brute force";
			break;

		case enumChestOpeningOptions::eLockPick:
			aStringToChange = "Pick lock";
			break;

		default:
			l1functions::console::PrintErrorToConsole("ChestOptions print is out of range");
			break;
		}
	}

	void GetStringFromEnum(const enumVitalTypes aStatType, std::string & aStringToChange)
	{
		switch (aStatType)
		{
		case enumVitalTypes::eHealth:
			aStringToChange = "Health";
			break;

		case enumVitalTypes::eStamina:
			aStringToChange = "Stamina";
			break;

		case enumVitalTypes::eDefense:
			aStringToChange = "Defense";
			break;

		case enumVitalTypes::eCarryLimit:
			aStringToChange = "Carry limit";
			break;

		default:
			l1functions::console::PrintErrorToConsole("VitalStat print is out of range");
			break;
		}
	}
	void GetStringFromEnum(const enumMenuOptions aStatType, std::string & aStringToChange)
	{
		switch (aStatType)
		{
		case enumMenuOptions::eChangeRoom:
			aStringToChange = "Changeroom";
			break;
		case enumMenuOptions::eChests:
			aStringToChange = "Open chest";
			break;
		case enumMenuOptions::eExit:
			aStringToChange = "Exit";
			break;
		case enumMenuOptions::eItems:
			aStringToChange = "Check items in room";
			break;
		case enumMenuOptions::eInventory:
			aStringToChange = "Check Inventory";
			break;
		case enumMenuOptions::eStats:
			aStringToChange = "CheckStats";
			break;

		default:
		case enumMenuOptions::enumLength:
			l1functions::console::PrintErrorToConsole("Enumoptions print is out of range");
			break;
		}
	}

	void GetStringFromEnum(const enumStatTypes aStatType, std::string & aStringToChange)
	{
		switch (aStatType)
		{
		case enumStatTypes::eAgility:
			aStringToChange = "Agility";
			break;
		case enumStatTypes::eIntelligens:
			aStringToChange = "Intelligense";
			break;
		case enumStatTypes::eKondition:
			aStringToChange = "Endurance";
			break;
		case enumStatTypes::eStrength:
			aStringToChange = "Strengrth";
			break;

		default:
		case enumStatTypes::enumLength:
			l1functions::console::PrintErrorToConsole("Basestat print is out of range");
			break;
		}
	}

	std::string GetStringFromEnum(const enumStatTypes aStatType)
	{
		std::string tmpString;
		GetStringFromEnum(aStatType, tmpString);
		return tmpString;
	}

	void CreateStringVectorFromEnumVector(const std::vector<enumMenuOptions>& aVectorOfEnums, std::vector<std::string> & aVectorOfString)
	{
		for (unsigned int iEnumSlot = 0; iEnumSlot < aVectorOfEnums.size(); ++iEnumSlot)
		{
			std::string tempString;
			GetStringFromEnum(aVectorOfEnums[iEnumSlot], tempString);
			aVectorOfString.push_back(tempString);
		}
	}

}
#pragma once
#include "../Classes/Menu/MenuOptionsEnum.h"
#include "../Classes/Stats/BaseStatEnum.h"
#include "../Classes/Stats/VitalStat.h"
#include "../Classes/Menu/ChestOpeningOptionsEnum.h"
#include "../Classes/Stats/AttackTypesEnum.h"
#include <string>
#include <vector>


namespace enumutility
{
	void GetStringFromEnum(const enumAttackTypes aAttackType, std::string & aStringToChange);

	void GetStringFromEnum(const enumChestOpeningOptions aStatType, std::string & aStringToChange);

	void GetStringFromEnum(const enumVitalTypes aStatType, std::string & aStringToChange);

	void GetStringFromEnum(const enumMenuOptions aStatType, std::string & aStringToChange);

	void GetStringFromEnum(const enumStatTypes aStatType, std::string & aStringToChange);

	std::string GetStringFromEnum(const enumStatTypes aStatType);


	void CreateStringVectorFromEnumVector(const std::vector<enumMenuOptions> & aVectorOfEnums, std::vector<std::string> & aVectorOfString);
}
#pragma once
#include "Stats\AttackTypesEnum.h"
#include <string>
#include "../Structs/name_and_description.h"

struct MinMaxDamage
{
	float minDamage;
	float maxDamage;
};

class DamagePower
{
public:
	DamagePower(enumAttackTypes aAttackType);
	~DamagePower();

	void SetStaminaCost(const float aStaminaCost);

	float GetStaminaCost() const;

	const float GetDamageToDeal() const;

	void GetPrintOfDamageRange(std::string & aStringToPrint) const;

	void SetDamage(MinMaxDamage aDamageRange);

	enumAttackTypes GetAttackType() const;

	void GetName(std::string & aStringToChange) const;

private:
	void SetName(std::string & aNewName);

	float myStaminaCost;

	NameAndDescription myName;
	
	MinMaxDamage myDamage;

	enumAttackTypes myAttackType;
};


#pragma once

#include "GameObjects/Unit/BaseUnitClass.h"

class DefaultUnit : public BaseUnitClass
{
public:
	DefaultUnit(const unsigned short aIndex, const unsigned short aFactionID);
	~DefaultUnit();


	virtual float GetAttackRating() override;

	virtual float GetDefenseRating() override;

	virtual float GetMoraleRating() override;

	virtual void Move(const CU::Vector2ui & aNewPosition) override;

private:
	float myDamage;
	float myDefense;
	float myMorale;
};
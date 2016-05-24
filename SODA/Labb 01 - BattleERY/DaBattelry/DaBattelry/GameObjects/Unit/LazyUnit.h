#pragma once
#include "GameObjects/Unit/BaseUnitClass.h"

class LazyUnit : public BaseUnitClass
{
public:
	LazyUnit(const unsigned short aIndex, const unsigned short aFactionID);
	~LazyUnit();

	virtual float GetAttackRating() override;

	virtual float GetDefenseRating() override;

	virtual float GetMoraleRating() override;

	virtual void Move(const CU::Vector2ui & aNewPosition) override;
};


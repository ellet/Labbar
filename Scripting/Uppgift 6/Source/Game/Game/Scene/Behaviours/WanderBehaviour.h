#pragma once
#include "BaseBehaviour.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"


class WanderBehaviour : public BaseBehaviour
{
public:
	WanderBehaviour(const Unit & aParentUnit);
	~WanderBehaviour();


	virtual Steering GetSteering(const SB::Time & aDeltaTime) override;

	static float ourWeight;

private:
	float GetRandomBinomial();

	SB::Randomizer myRandomizer;

};


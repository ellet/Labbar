#pragma once
#include "Engine\Component\BaseComponent.h"
class ShotComponent : public SB::BaseComponent
{
public:

	void SetSpeed(const SB::Vector3f & aSpeed);

	virtual void Initialize() override;
	~ShotComponent();

	virtual void Update(const SB::Time & aDeltaTime) override;

	bool myHasHit;

private:
	

	SB::Vector3f mySpeed;
	SB::Time myAge;
};


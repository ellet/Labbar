#pragma once
#include "Game\Component\Shooting\Projectiles\ShotComponent.h"
#include "Game\Component\Shooting\WeaponData.h"


class BeamShotComponent : public ShotComponent
{
public:
	BeamShotComponent();
	~BeamShotComponent();

	void Update(const SB::Time& aDeltaTime) override;

	void SetData(const SB::Vector3f& aSourcePosition, const SB::Vector3f& aTargetPosition, const float aLifeTime);
	//void SetData(const BeamWeaponData& aData);


private:
	void UpdateMovement(const SB::Time& aDeltaTime);

	SB::Vector3f mySourcePosition;
	SB::Vector3f myTargetPosition;
	bool myHasMoved;
};


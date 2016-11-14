#pragma once
#include "..\AIControllerComponent.h"

class WeaponComponent;

namespace SB
{
	class Time;
}

class AIMothershipTurretComponent :
	public AIControllerComponent
{
public:
	AIMothershipTurretComponent();
	~AIMothershipTurretComponent();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Initialize() override;

	virtual void LoadData(SB::DataNode aProperties) override;

	virtual void ToJson() const override;

private:
	void LookAtPlayer(const SB::Time & aDeltaTime);
	void CheckIfWantToShoot(const SB::Time & aDeltaTime);
	void Shoot();

	WeaponComponent * myWeaponComponent;
	SB::Time myShootingCooldown;
	SB::Time myCooldownTimer;
	float myMaxRotationDegrees;

};


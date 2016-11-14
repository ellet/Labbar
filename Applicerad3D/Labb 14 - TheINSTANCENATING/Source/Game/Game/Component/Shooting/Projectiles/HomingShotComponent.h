#pragma once
#include "ShotComponent.h"
#include "Engine/Component/Collider/CollisionEvent.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"
#include <Utilities/Randomizer/Randomizer.h>
#include "..\WeaponData.h"


class HomingShotComponent : public ShotComponent
{
public:
	HomingShotComponent();
	~HomingShotComponent();
	void Initialize() override;
	void OnRemoved() override;

	void Update(const SB::Time& aDeltaTime) override;

	void SetData(const HomingWeaponData& aData);

	SB::ObjectPtr GetClosestAvailableTarget();

private:
	void UpdateRotation(const SB::Time& aDeltaTime);
	void UpdateAcceleration(const SB::Time& aDeltaTime);
	void UpdateHoming(const SB::Time& aDeltaTime);
	void RecieveEvent(const SB::TriggerCollisionEvent& aEvent) override;

	SB::GrowingArray<SB::ObjectPtr> myTargetsInRange;
	SB::ObjectPtr myCurrentTarget;
	SB::Randomizer myRandomizer;
	SB::Time myTrackingDelay;
	SB::Time myTargetSwitchingCooldown;
	SB::Time myTargetSwitchingTimer;
	float myProjectileRotationDegreesPerSecond;
	float myProjectileSpeedMax;
};


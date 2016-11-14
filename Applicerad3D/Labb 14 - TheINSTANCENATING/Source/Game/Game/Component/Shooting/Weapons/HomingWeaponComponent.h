#pragma once
#include "Game\Component\Shooting\Weapons\WeaponComponent.h"
#include "..\WeaponData.h"

class HomingWeaponComponent : public WeaponComponent
{
public:
	HomingWeaponComponent();
	HomingWeaponComponent(const WeaponData& aData);
	HomingWeaponComponent(SB::DataNode aProperties);
	~HomingWeaponComponent();

	virtual void FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation) override;

	virtual void ToJson() const override;

private:
	SB::ObjectPtr CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection) override;

	HomingWeaponData myHomingData;
};


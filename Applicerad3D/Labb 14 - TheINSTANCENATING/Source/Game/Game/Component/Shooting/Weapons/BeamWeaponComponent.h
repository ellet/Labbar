#pragma once
#include "Game\Component\Shooting\Weapons\WeaponComponent.h"
#include "..\WeaponData.h"

namespace SB
{
	class RayCollider;
}

class BeamWeaponComponent : public WeaponComponent
{
public:
	BeamWeaponComponent();
	BeamWeaponComponent(const WeaponData& aData);
	BeamWeaponComponent(SB::DataNode aProperties);
	~BeamWeaponComponent();

	virtual void ToJson()const  override;

private:
	void CreateImpactParticles(const SB::Vector3f & aPosition);
	void HandleBeamCollision(SB::CollisionData& aCollisionData);
	SB::Vector3f DetermineFurthestBeamPoint(const SB::Vector3f& aFiringPosition, const SB::Quaternion& aLaunchDirection) const;

	SB::ObjectPtr CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection) override;

	BeamWeaponData myBeamData;
	std::unique_ptr<SB::RayCollider> myCollider;
};


#pragma once

struct WeaponData
{
	WeaponData()
	{
		identifier = "";
		weaponModelPath = "";
		weaponIconPath = "";
		projectileModelPath = "";
		muzzleFlashModelPath = "";
		shootSound = "";
		impactSound = "";
		shootEffect = "";
		barrelOffset = SB::Vector3f::Zero;
		shotScale = SB::Vector3f::One;
		shotCooldown = 1.f;
		damage = 1.f;
		shotSpeed = 10.f;
		firingRotationVelocityMax = 0.f;
		firingRotationVelocityAccelerationTime = 0.f;
		overheatDuration = 0.f;
		overheatPerShot = 0;
		firingType = 0;
		isOwned = true;
	}
	WeaponData(const SB::GrowingArray<std::string>& aImpactEffects, const std::string& aIdentifier, const std::string& aWeaponModelPath, const std::string& aWeaponIconPath, 
		const std::string& aProjectileModelPath, const std::string& aMuzzleFlashModelPath, const std::string& aShootSound, const std::string& aImpactSound, const std::string& aShootEffect, 
		const SB::Vector3f& aBarrelOffset, const SB::Vector3f& aShotScale, const float aShotCooldown, const float aDamage, const float aShotSpeed, const float aFiringRotationVelocityMax, 
		const SB::Time& aFiringRotationVelocityAccelerationTime, const SB::Time& aOverheatDuration, const unsigned short aOverheatPerShot, const unsigned short aFiringType, const bool aIsOwned)
	{
		impactSound = aImpactSound;
		impactEffects = aImpactEffects;
		identifier = aIdentifier;
		weaponModelPath = aWeaponModelPath;
		projectileModelPath = aProjectileModelPath;
		muzzleFlashModelPath = aMuzzleFlashModelPath;
		weaponIconPath = aWeaponIconPath;
		shootSound = aShootSound;
		shootEffect = aShootEffect;
		barrelOffset = aBarrelOffset;
		shotScale = aShotScale;
		shotCooldown = aShotCooldown;
		damage = aDamage;
		shotSpeed = aShotSpeed;
		firingRotationVelocityMax = aFiringRotationVelocityMax;
		firingRotationVelocityAccelerationTime = aFiringRotationVelocityAccelerationTime;
		overheatDuration = aOverheatDuration;
		overheatPerShot = aOverheatPerShot;
		firingType = aFiringType;
		isOwned = aIsOwned;
	}

	SB::GrowingArray<std::string> impactEffects;
	std::string identifier;
	std::string weaponModelPath;
	std::string weaponIconPath;
	std::string projectileModelPath;
	std::string muzzleFlashModelPath;
	std::string impactSound;
	std::string shootSound;
	std::string shootEffect;
	SB::Vector3f barrelOffset;
	SB::Vector3f shotScale;
	float shotCooldown;
	float damage;
	float shotSpeed;
	float firingRotationVelocityMax; //max z-rotation angular velocity barrel can attain whilst firing
	SB::Time firingRotationVelocityAccelerationTime; //time it takes to reach maximum velocity whilst firing (in seconds)
	SB::Time overheatDuration; //Time spent waiting once overheating triggers
	unsigned short overheatPerShot; //Overheat % per shot
	unsigned short firingType;
	bool isOwned;
};

struct HomingWeaponData
{
	HomingWeaponData()
	{
		targetScanRadius = 0.f;
		shotTrackingDelay = 0.f;
		shotSpeedMax = 0.f;
		projectileRotationDegreesPerSecond = 0.f;
		targetSwitchingCooldown = 0.f;
	}
	HomingWeaponData(const float aTargetScanRadius, const float aShotTrackingDelay, const float aShotSpeedMax, const float aProjectileRotationDegreesPerSecond, const float aTargetSwitchingCooldown)
	{
		targetScanRadius = aTargetScanRadius;
		shotTrackingDelay = aShotTrackingDelay;
		shotSpeedMax = aShotSpeedMax;
		projectileRotationDegreesPerSecond = aProjectileRotationDegreesPerSecond;
		targetSwitchingCooldown = aTargetSwitchingCooldown;
	}

	float targetScanRadius;
	float shotTrackingDelay;
	float shotSpeedMax;
	float projectileRotationDegreesPerSecond;
	float targetSwitchingCooldown;
};

struct BeamWeaponData
{
	BeamWeaponData()
	{
		beamRadius = 0.f;
		beamMaxDistance = 0.f;
		beamLifeTime = 0.f;
		beamPierces = false;
	}
	BeamWeaponData(const float aBeamRadius, const float aBeamMaxDistance, const float aBeamLifeTime, const bool aBeamPierces)
	{
		beamRadius = aBeamRadius;
		beamMaxDistance = aBeamMaxDistance;
		beamLifeTime = aBeamLifeTime;
		beamPierces = aBeamPierces;
	}

	float beamRadius;
	float beamMaxDistance;
	float beamLifeTime;
	bool beamPierces;
};

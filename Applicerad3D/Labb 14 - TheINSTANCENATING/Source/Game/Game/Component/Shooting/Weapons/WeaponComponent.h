#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Utilities/Randomizer/Randomizer.h>
#include "..\WeaponData.h"


namespace ENGINE_NAMESPACE
{
	class GameObject;
}

enum class eFiringType
{
	eStandard,
	eHoming,
	eBeam
};

class WeaponComponent : public SB::BaseComponent
{
public:
	WeaponComponent();
	WeaponComponent(const WeaponData& aData);
	WeaponComponent(SB::DataNode aProperties);
	~WeaponComponent();

	void LoadData(SB::DataNode aProperties) override;
	virtual void ToJson() const override;

	virtual void FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation);

	inline const std::string& GetIdentifier() const
	{
		return myWeaponData.identifier;
	}
	inline const std::string& GetShootSound() const
	{
		return myWeaponData.shootSound;
	}
	inline const std::string& GetWeaponIconPath() const
	{
		return myWeaponData.weaponIconPath;
	}
	inline const SB::Vector3f& GetShotScale() const
	{
		return myWeaponData.shotScale;
	}
	inline const SB::Vector3f& GetBarrelOffset() const
	{
		return myWeaponData.barrelOffset;
	}
	inline std::shared_ptr<SB::Model> GetWeaponModel() const
	{
		return myWeaponModel;
	}
	inline std::shared_ptr<SB::Model> GetProjectileModel() const
	{
		return myProjectileModel;
	}
	inline float GetShotCooldown() const
	{
		return myWeaponData.shotCooldown;
	}
	inline float GetDamage() const
	{
		return myWeaponData.damage;
	}
	inline float GetShotSpeed() const
	{
		return myWeaponData.shotSpeed;
	}
	inline float GetFiringRotationVelocityMax() const
	{
		return myWeaponData.firingRotationVelocityMax;
	}
	inline const SB::Time& GetFiringRotationVelocityAccelerationTime() const
	{
		return myWeaponData.firingRotationVelocityAccelerationTime;
	}
	inline const SB::Time& GetOverheatDuration() const
	{
		return myWeaponData.overheatDuration;
	}
	inline unsigned short GetOverheatPerShot() const
	{
		return myWeaponData.overheatPerShot;
	}
	inline bool GetIsOwned() const
	{
		return myWeaponData.isOwned;
	}

	inline SB::GameObject* GetUser()
	{
		return myUser;
	}
	inline void SetIsOwned(const bool aValue)
	{
		myWeaponData.isOwned = aValue;
	}
	inline void SetUser(SB::GameObject* aWeaponUser)
	{
		myUser = aWeaponUser;
	}
	inline void SetCollisonFilters(const unsigned int aCollisionFilter) 
	{
		myCollisionFilter = aCollisionFilter;
	}
	inline void SetLayerID(const unsigned int aLayerID)
	{ 
		myLayerID = aLayerID;
	}


protected:
	void SetData(const WeaponData& aData);
	virtual SB::ObjectPtr CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection);
	std::string GetDefaultProjectileIdentifier() const;
	SB::Quaternion GetRandomShotRotation(const SB::Quaternion& aWeaponOrientation);
	void SpawnShotParticles(SB::ObjectPtr aShot);
	void EndToJson()const ;

	WeaponData myWeaponData;
	SB::Randomizer myRandomizer;
	std::shared_ptr<SB::Model> myWeaponModel;
	std::shared_ptr<SB::Model> myProjectileModel;
	std::shared_ptr<SB::Model> myMuzzleFlashModel;
	SB::GameObject* myUser;
	unsigned int myCollisionFilter;
	unsigned int myLayerID;
};


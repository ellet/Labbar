#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Utilities/Randomizer/Randomizer.h>


struct WeaponData
{
	WeaponData()
	{
		identifier = "";
		weaponModelPath = "";
		weaponIconPath = "";
		projectileModelPath = "";
		shootSound = "";
		barrelOffset = SB::Vector3f::Zero;
		shotScale = SB::Vector3f::One;
		shotCooldown = 1.f;
		damage = 1.f;
		shotSpeed = 10.f;
	}
	WeaponData(const std::string& aIdentifier, const std::string& aWeaponModelPath, const std::string& aWeaponIconPath, const std::string& aProjectileModelPath, const std::string& aShootSound, const SB::Vector3f& aBarrelOffset, const SB::Vector3f& aShotScale, const float aShotCooldown, const float aDamage, const float aShotSpeed)
	{
		identifier = aIdentifier;
		weaponModelPath = aWeaponModelPath;
		projectileModelPath = aProjectileModelPath;
		weaponIconPath = aWeaponIconPath;
		shootSound = aShootSound;
		barrelOffset = aBarrelOffset;
		shotScale = aShotScale;
		shotCooldown = aShotCooldown;
		damage = aDamage;
		shotSpeed = aShotSpeed;
	}
	std::string identifier;
	std::string weaponModelPath;
	std::string weaponIconPath;
	std::string projectileModelPath;
	std::string shootSound;
	SB::Vector3f barrelOffset;
	SB::Vector3f shotScale;
	float shotCooldown;
	float damage;
	float shotSpeed;
};

class WeaponComponent : public SB::BaseComponent
{
public:
	WeaponComponent();
	WeaponComponent(const WeaponData& aData);
	~WeaponComponent();

	void LoadData(SB::DataNode aProperties) override;

	virtual void FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation);

	inline const std::string& GetIdentifier() const
	{
		return myIdentifier;
	}
	inline const std::string& GetShootSound() const
	{
		return myShootSound;
	}
	inline const std::string& GetWeaponIconPath() const
	{
		return myWeaponIconPath;
	}
	inline const SB::Vector3f& GetShotScale() const
	{
		return myShotScale;
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
		return myShotCooldown;
	}
	inline float GetDamage() const
	{
		return myDamage;
	}
	inline float GetShotSpeed() const
	{
		return myShotSpeed;
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
	void HardCodedShotParticlesToRemoveAfterCheckup(SB::ObjectPtr aShot);
	SB::ObjectPtr CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection);
	std::string GetDefaultProjectileIdentifier() const;

	std::string myIdentifier;
	std::string myShootSound;
	std::string myWeaponModelPath;
	std::string myProjectileModelPath;
	std::string myWeaponIconPath;
	SB::Randomizer myRandomizer;
	SB::Vector3f myBarrelOffset;
	SB::Vector3f myShotScale;
	std::shared_ptr<SB::Model> myWeaponModel;
	std::shared_ptr<SB::Model> myProjectileModel;
	float myShotCooldown;
	float myDamage;
	float myShotSpeed;
	unsigned int myCollisionFilter;
	unsigned int myLayerID;
};


#pragma once

class WeaponComponent;

enum class eWeaponEquipState
{
	eUnequipped,
	eEquipping,
	eEquipped,
	eUnequipping
};

namespace ENGINE_NAMESPACE
{
	class SpeakerComponent;
}

class WeaponMount
{
public:
	WeaponMount(const SB::GrowingArray<std::shared_ptr<WeaponComponent>>& aAvailableWeapons, const SB::ObjectPtr& aWeaponRoot, const SB::GrowingArray<SB::Vector3f>& aWeaponNodeLocalPositions, const std::string& aWeaponGUIIdentifier);
	void InitNodes();
	~WeaponMount();

	void OnRemoved();

	void Update(const SB::Time& aDeltaTime);
	void EquipWeapon(const std::string& aWeaponIdentifier);
	void EquipWeapon(const unsigned short aWeaponIndex);
	void EquipWeaponInstantly(const std::string& aWeaponIdentifier);
	void EquipWeaponInstantly(const unsigned short aWeaponIndex);
	void FireEquippedWeapon();
	void FireWeapon(std::shared_ptr<WeaponComponent> aWeapon);

	inline void SetIsFiring(const bool aValue)
	{
		if (myHasOverheated == false) //Disallow changing firing state if currently overheating
			myIsFiring = aValue;
		//else
			//TODO: Play sound to signal firing as unavailable
	}
	inline const bool GetHasOverheated() const
	{
		return myHasOverheated;
	}
	const std::string& GetWeaponIdentifierAtIndex(const unsigned short aWeaponIndex);
	void Reset();
private:
	//Member Functions:
	void UpdateEquipping(const SB::Time& aDeltaTime);
	void UpdateBarrelRotation(const SB::Time& aDeltaTime);
	void UpdateOverheat(const SB::Time& aDeltaTime);
	void UpdateFiring(const SB::Time& aDeltaTime);
	void UpdateRTPC();

	void SwapQueuedWeaponWithCurrentlyEquipped();
	void StartRetractingWeapon();
	void StartExtendingWeapon();
	void PerformWeaponRetractionStep(const SB::Time& aDeltaTime);
	void PerformWeaponExtensionStep(const SB::Time& aDeltaTime);
	void FinalizeUnequip();
	void FinalizeEquip();

	void RotateWeaponNodes(const float aAngleDegrees);
	void ResetWeaponNodeRotations();
	bool GetCanEquippedWeaponRotate() const;

	void AddOverheat();
	void TriggerOverheat();
	void ResetOverheatTimer();
	void ResetOverheat();
	void TriggerOverheatInputErrorFeedback();

	inline bool GetIsPrimaryWeaponMount()
	{
		return (myWeaponMountID % 2 == 0); //Even IDs means it's a primary
	}
	void SetCurrentOverheatAmount(const float aNewValue);

	//Member Vars:
	const SB::GrowingArray<std::shared_ptr<WeaponComponent>>& myWeapons;
	SB::GrowingArray<SB::ObjectPtr> myWeaponNodes;
	SB::GrowingArray<SB::ObjectPtr> myMuzzleNodes;
	SB::GrowingArray<SB::Vector3f> myRetractedPositions;
	SB::GrowingArray<SB::Vector3f> myExtendedPositions;
	std::string myWeaponGUIIdentifier;
	std::shared_ptr<WeaponComponent> myEquippedWeapon;
	std::shared_ptr<WeaponComponent> myQueuedEquippedWeapon;
	SB::SpeakerComponent* mySpeakerComponent;
	SB::ObjectPtr myWeaponRoot;
	SB::Time myShotCooldown;
	SB::Time myWeaponSwapCooldown;
	SB::Time myWeaponSwapTimer;
	SB::Time myOverheatTimer;
	float myWeaponSwapStep;
	float myCurrentBarrelRotationVelocity;
	float myOldBarrelRotationVelocity;
	float myCurrentOverheatAmount;
	eWeaponEquipState myWeaponEquipState;
	unsigned short myCurrentlyFiringNodeIndex;
	unsigned short myWeaponMountID; //For purposes of sending the appropriate GUI bar message
	bool myIsFiring;
	bool myHasOverheated;
};


#pragma once


struct SavedPlayerData
{
	SavedPlayerData()
	{
		myHealth = 0.f;
		myStartPosition = SB::Vector3f::Zero;
		for (unsigned short i = 0; i < myOwnedPrimaryWeapons.Size(); ++i)
		{
			myOwnedPrimaryWeapons[i] = false;
		}
		for (unsigned short i = 0; i < myOwnedPrimaryWeapons.Size(); ++i)
		{
			myOwnedPrimaryWeapons[i] = false;
		}
	}
	SavedPlayerData(const float aHealth, const SB::GrowingArray<bool>& aOwnedPrimaryWeapons, const SB::GrowingArray<bool>& aOwnedSecondaryWeapons, const SB::Vector3f & aStartPosition)
	{
		myHealth = aHealth;
		myStartPosition = aStartPosition;
		myOwnedPrimaryWeapons = aOwnedPrimaryWeapons;
		myOwnedSecondaryWeapons = aOwnedSecondaryWeapons;
	}

	SavedPlayerData& operator =(const SavedPlayerData& aOther)
	{
		myHealth = aOther.myHealth;
		myStartPosition = aOther.myStartPosition;
		myOwnedPrimaryWeapons = aOther.myOwnedPrimaryWeapons;
		myOwnedSecondaryWeapons = aOther.myOwnedSecondaryWeapons;

		return *this;
	}

	float myHealth;
	SB::Vector3f myStartPosition;
	SB::GrowingArray<bool> myOwnedPrimaryWeapons;
	SB::GrowingArray<bool> myOwnedSecondaryWeapons;
	//float myAimRate;
	//WeaponStuffs myAvailableWeapons
	//enum class Difficulty myChosenDifficulty
};
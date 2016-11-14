#pragma once
#include "../Game/Game/Player/PlayerDataStruct.h"

struct PlayerHealthChangedMessage
{
	PlayerHealthChangedMessage(const float aNewValue)
	{
		myCurrentHealth = aNewValue;
	}

	float myCurrentHealth;
};

struct OverheatChangedMessage
{
	OverheatChangedMessage(const float aNewValue, const bool aIsPrimary)
	{
		myCurrentOverheatValue = aNewValue;
		myIsPrimary = aIsPrimary;
	}

	float myCurrentOverheatValue;
	bool myIsPrimary;
};

struct SetPlayerDataMessage
{
	SetPlayerDataMessage(const SavedPlayerData & aLoadedPlayerData)
	{
		mySavedData = aLoadedPlayerData;
	}

	SavedPlayerData mySavedData;
};

struct PlayerTakenDamageMessage
{
	PlayerTakenDamageMessage(const float aDamageAmount)
	{
		myDamageAmount = aDamageAmount;
	}

	float myDamageAmount;
};


#pragma once

struct TakeDamageMessage
{
	TakeDamageMessage(const float aNewHealth, const float aDamageAmount)
	{
		newHealth = aNewHealth;
		damageAmount = aDamageAmount;
	}

	float newHealth;
	float damageAmount;
};

struct RecoverHealthMessage
{
	RecoverHealthMessage(const float aNewHealth, const float aRecoverAmount)
	{
		newHealth = aNewHealth;
		recoverAmount = aRecoverAmount;
	}

	float newHealth;
	float recoverAmount;
};

struct EnemyTakeDamageMessage : public TakeDamageMessage
{
	EnemyTakeDamageMessage(const float aNewHealth, const float aDamageAmount) : TakeDamageMessage(aNewHealth, aDamageAmount)
	{
	}
};

struct EnemyRecoverHealthMessage : public RecoverHealthMessage
{
	EnemyRecoverHealthMessage(const float aNewHealth, const float aRecoverAmount) : RecoverHealthMessage(aNewHealth, aRecoverAmount)
	{
	}
};

struct PlayerTakeDamageMessage : public TakeDamageMessage
{
	PlayerTakeDamageMessage(const float aNewHealth, const float aDamageAmount) : TakeDamageMessage(aNewHealth, aDamageAmount)
	{
	}
};

struct PlayerRecoverHealthMessage : public RecoverHealthMessage
{
	PlayerRecoverHealthMessage(const float aNewHealth, const float aRecoverAmount) : RecoverHealthMessage(aNewHealth, aRecoverAmount)
	{
	}
};

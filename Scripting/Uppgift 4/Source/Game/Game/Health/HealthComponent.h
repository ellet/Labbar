#pragma once
#include "HealthMessages.h"


class HealthComponent : public SB::BaseComponent
{
public:
	HealthComponent(const float aMaxHealth = 100.f);
	~HealthComponent() = 0;

	virtual void LoadData(SB::DataNode aProperties) override;
	virtual void ToJson(SB::JsonSerializer& aSerializer) const override;

	//Health Manipulation Functions:
	virtual void TakeDamage(const float aAmount);
	virtual void RecoverHealth(const float aAmount);
	void SetCurrentHealth(const float aValue, const bool aReviveIfDead = false);
	void SetMaxHealth(const float aValue);

	inline float GetCurrentHealth() const
	{
		return myCurrentHealth;
	}
	inline float GetMaxHealth() const
	{
		return myMaxHealth;
	}

	//Utility Functions:
	inline float GetRemainingHealthPercentage() const
	{
		return myCurrentHealth / myMaxHealth;
	}
	inline bool GetIsDead() const
	{
		return myCurrentHealth > 0.f;
	}
	virtual inline bool GetIsPlayer() const
	{
		return false;
	}
	virtual inline bool GetIsEnemy() const
	{
		return false;
	}

protected:
	float myCurrentHealth;
	float myMaxHealth;
	bool myIsInvulnerable;
};


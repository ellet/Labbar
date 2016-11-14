#pragma once
#include "Engine\Component\BaseComponent.h"


class HealthComponent :
	public SB::BaseComponent
{
public:
	HealthComponent();
	~HealthComponent();

	void AddHealth(const float aValue);
	void RemoveHealth(const float aValue);
	void SetHealth(const float aValue);

	inline float GetCurrentHealth() const
	{
		return myCurrentHealth;
	}
	inline float GetMaxHealth() const
	{
		return myMaxHealth;
	}

	void LoadData(SB::DataNode aProperties) override;
	void ToJson() const override;

	bool GetIsDead() const;


private:
	void HandleZeroHealth();

	float myCurrentHealth;
	float myMaxHealth;
};


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

	float GetHealth() const;

	void LoadData(SB::DataNode aProperties) override;

private:
	float myCurrentHealth;
};


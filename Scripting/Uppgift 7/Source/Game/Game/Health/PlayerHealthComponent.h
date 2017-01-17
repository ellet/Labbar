#pragma once
#include "Game/Health/HealthComponent.h"


class PlayerHealthComponent : public HealthComponent
{
public:
	PlayerHealthComponent(const float aMaxHealth = 100.f);
	PlayerHealthComponent(SB::DataNode aProperties);
	~PlayerHealthComponent();

	virtual void TakeDamage(const float aAmount) override;
	virtual void RecoverHealth(const float aAmount) override;

	inline bool GetIsPlayer() const override
	{
		return true;
	}


private:

};


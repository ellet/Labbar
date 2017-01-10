#pragma once
#include "Game/Health/HealthComponent.h"


class EnemyHealthComponent : public HealthComponent
{
public:
	EnemyHealthComponent(const float aMaxHealth = 100.f);
	EnemyHealthComponent(SB::DataNode aProperties);
	~EnemyHealthComponent();

	virtual void TakeDamage(const float aAmount) override;
	virtual void RecoverHealth(const float aAmount) override;

	inline bool GetIsEnemy() const override
	{
		return true;
	}

private:

};


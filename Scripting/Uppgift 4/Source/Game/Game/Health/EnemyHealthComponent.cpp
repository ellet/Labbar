#include "stdafx.h"
#include "EnemyHealthComponent.h"


EnemyHealthComponent::EnemyHealthComponent(const float aMaxHealth/* = 100.f*/) : HealthComponent(aMaxHealth)
{
}

EnemyHealthComponent::EnemyHealthComponent(SB::DataNode aProperties)
{
	LoadData(aProperties);
}

EnemyHealthComponent::~EnemyHealthComponent()
{
}

void EnemyHealthComponent::TakeDamage(const float aAmount)
{
	float previousHealth = myCurrentHealth;

	HealthComponent::TakeDamage(aAmount);

	if (myCurrentHealth < previousHealth)
	{
		SB::PostMaster::Post(EnemyTakeDamageMessage(myCurrentHealth, aAmount));
	}
}

void EnemyHealthComponent::RecoverHealth(const float aAmount)
{
	float previousHealth = myCurrentHealth;

	HealthComponent::RecoverHealth(aAmount);

	if (myCurrentHealth > previousHealth)
	{
		SB::PostMaster::Post(EnemyRecoverHealthMessage(myCurrentHealth, aAmount));
	}
}

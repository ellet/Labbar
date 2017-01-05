#include "stdafx.h"
#include "PlayerHealthComponent.h"


PlayerHealthComponent::PlayerHealthComponent(const float aMaxHealth/* = 100.f*/) : HealthComponent(aMaxHealth)
{
}

PlayerHealthComponent::PlayerHealthComponent(SB::DataNode aProperties)
{
	LoadData(aProperties);
}

PlayerHealthComponent::~PlayerHealthComponent()
{
}

void PlayerHealthComponent::TakeDamage(const float aAmount)
{
	float previousHealth = myCurrentHealth;

	HealthComponent::TakeDamage(aAmount);

	if (myCurrentHealth < previousHealth)
	{
		SB::PostMaster::Post(PlayerTakeDamageMessage(myCurrentHealth, aAmount));
	}
}

void PlayerHealthComponent::RecoverHealth(const float aAmount)
{
	float previousHealth = myCurrentHealth;

	HealthComponent::RecoverHealth(aAmount);

	if (myCurrentHealth > previousHealth)
	{
		SB::PostMaster::Post(PlayerRecoverHealthMessage(myCurrentHealth, aAmount));
	}
}

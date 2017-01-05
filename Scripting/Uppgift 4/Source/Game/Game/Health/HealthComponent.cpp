#include "stdafx.h"
#include "HealthComponent.h"


HealthComponent::HealthComponent(const float aMaxHealth)
{
	myMaxHealth = aMaxHealth;
	myCurrentHealth = aMaxHealth;
	myIsInvulnerable = false;
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::LoadData(SB::DataNode aProperties)
{
	myMaxHealth = MAX(aProperties["maxHealth"].GetFloat(), 1.f);

	if (aProperties.HasMember("currentHealth") == true)
		myCurrentHealth = CLAMP(aProperties["currentHealth"].GetFloat(), 0.f, myMaxHealth);
	else
		myCurrentHealth = myMaxHealth;

	myIsInvulnerable = aProperties["isInvulnerable"].GetBool();
}

void HealthComponent::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("currentHealth", myCurrentHealth);
	aSerializer.WriteNode("maxHealth", myMaxHealth);
	aSerializer.WriteNode("isInvulnerable", myIsInvulnerable);
}

void HealthComponent::TakeDamage(const float aAmount)
{
	SetCurrentHealth(myCurrentHealth - aAmount);
}

void HealthComponent::RecoverHealth(const float aAmount)
{
	SetCurrentHealth(myCurrentHealth + aAmount);
}

void HealthComponent::SetCurrentHealth(const float aValue, const bool aReviveIfDead/* = false*/)
{
	if (myIsInvulnerable == true && aValue < myCurrentHealth) //If we're invulnerable, we can't take damage
	{
		return;
	}
	if (aValue == myCurrentHealth) //Abort if value is unchanged
	{
		return;
	}
	if (GetIsDead() == true && aReviveIfDead == false) //If we're already dead and can't be revived, abort
	{
		return;
	}
	if (aValue >= myMaxHealth && myCurrentHealth >= myMaxHealth) //If we're trying to increase health and we're already at max, abort
	{
		return;
	}
	else if (aValue <= 0.f && myCurrentHealth <= 0.f) //If we're already at 0 health and we're trying to decrease it further, abort
	{
		return;
	}

	float previous = myCurrentHealth;

	myCurrentHealth = CLAMP(aValue, 0.f, myMaxHealth);

	if (previous > myCurrentHealth)
	{
		//TODO: Send TakeDamage event
	}
	else if (previous < myCurrentHealth)
	{
		//TODO: Send RecoverHealth event
	}
}

void HealthComponent::SetMaxHealth(const float aValue)
{
	if (aValue <= 0.f || aValue == myMaxHealth)
	{
		//Abort if we're trying to set max to 0 or below, or if value is unchanged
		return;
	}

	float difference = aValue - myMaxHealth;

	myMaxHealth = aValue;

	//Modify current as well due to the increase -- remove the below if undesired
	myCurrentHealth = CLAMP(myCurrentHealth + difference, 1.f, myMaxHealth);
}

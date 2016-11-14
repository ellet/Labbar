#include "stdafx.h"
#include "HealthComponent.h"
#include "ObjectOutOfHealthMessage.h"
#include "Game/Player/PlayerMessages.h"


HealthComponent::HealthComponent()
{
	myMaxHealth = 100.f;
	myCurrentHealth = myMaxHealth;
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::AddHealth(const float aValue)
{
	SetHealth(myCurrentHealth + aValue);
}

void HealthComponent::RemoveHealth(const float aValue)
{
	SetHealth(myCurrentHealth - aValue);
}

void HealthComponent::SetHealth(const float aValue)
{
	float previousHealth = myCurrentHealth;
	myCurrentHealth = CLAMP(aValue, 0.f, myMaxHealth);

	if (myObject->GetIdentifier() == "Player")
	{
		if (previousHealth != myCurrentHealth)
		{
			SB::PostMaster::Post<PlayerHealthChangedMessage>(PlayerHealthChangedMessage(myCurrentHealth));

			if (previousHealth > myCurrentHealth)
			{
				float damageTaken = previousHealth - myCurrentHealth;
				SB::PostMaster::Post<PlayerTakenDamageMessage>(PlayerTakenDamageMessage(damageTaken));
			}
		}
	}

	if (aValue <= 0.f)
	{
		HandleZeroHealth();
	}
}


void HealthComponent::LoadData(SB::DataNode aProperties)
{
	myMaxHealth = aProperties["StartHealth"].GetFloat();

	if (aProperties.HasMember("currentHealth") == true)
		myCurrentHealth = aProperties["currentHealth"].GetFloat();
	else
		myCurrentHealth = myMaxHealth;
}

bool HealthComponent::GetIsDead() const
{
	return myCurrentHealth <= 0.f;
}

void HealthComponent::HandleZeroHealth()
{
	ObjectOutOfHealthMessage tempDeathMessage;
	tempDeathMessage.myLifeValue = myCurrentHealth;
	myObject->TriggerEvent(tempDeathMessage);

	if (myObject->GetComponent<SB::LuaComponent>() != nullptr)
	{
		myObject->GetComponent<SB::LuaComponent>()->ReceiveLuaEvent("ZeroHPEvent");
	}
}

void HealthComponent::ToJson()const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");

	serializer.WriteNode("currentHealth", myCurrentHealth);
	serializer.WriteNode("StartHealth", myMaxHealth);

	serializer.StepOut();
	serializer.WriteNode("type", "HealthComponent");
}

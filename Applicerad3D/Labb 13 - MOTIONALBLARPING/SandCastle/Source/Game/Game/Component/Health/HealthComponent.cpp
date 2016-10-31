#include "stdafx.h"
#include "HealthComponent.h"
#include "ObjectOutOfHealthMessage.h"


HealthComponent::HealthComponent()
{
	myCurrentHealth = 100.f;
}

HealthComponent::~HealthComponent()
{

}

void HealthComponent::AddHealth(const float aValue)
{
	if (aValue > 0.f)
	{
		myCurrentHealth += aValue;
	}
}

void HealthComponent::RemoveHealth(const float aValue)
{
	if (aValue > 0.f)
	{
		myCurrentHealth -= aValue;

		if (myCurrentHealth <= 0.f)
		{
			ObjectOutOfHealthMessage tempDeathMessage;
			tempDeathMessage.myLifeValue = myCurrentHealth;
			myObject->TriggerEvent(tempDeathMessage);

			if (myObject->GetComponent<SB::LuaComponent>() != nullptr)
			{
				myObject->GetComponent<SB::LuaComponent>()->ReceiveLuaEvent("ZeroHPEvent");
			}
		}
	}
}



float HealthComponent::GetHealth() const
{
	return myCurrentHealth;
}

void HealthComponent::LoadData(SB::DataNode aProperties)
{
	myCurrentHealth = aProperties["StartHealth"].GetFloat();
}

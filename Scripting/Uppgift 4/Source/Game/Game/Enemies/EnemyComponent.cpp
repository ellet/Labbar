#include "stdafx.h"
#include "EnemyComponent.h"
#include "Game/Health/EnemyHealthComponent.h"


EnemyComponent::EnemyComponent()
{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize()
{
	//Note: this may cause double initialization - remove if so
	myObject->GetComponent<EnemyHealthComponent>()->Initialize();
}

void EnemyComponent::Update(const SB::Time& aDeltaTime)
{

}

void EnemyComponent::LoadData(SB::DataNode aProperties)
{
	auto healthComponent = myObject->CreateComponent<EnemyHealthComponent>();
	healthComponent->LoadData(aProperties);
}

void EnemyComponent::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("type", "EnemyComponent");

	aSerializer.WriteObject("properties");
	auto healthComponent = myObject->GetComponent<EnemyHealthComponent>();
	healthComponent->ToJson(aSerializer);
	aSerializer.StepOut();
}

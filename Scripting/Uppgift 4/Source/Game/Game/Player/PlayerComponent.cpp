#include "stdafx.h"
#include "PlayerComponent.h"
#include <Engine/Camera/Controllers/BirdsEyeController.h>
#include "Game/Health/PlayerHealthComponent.h"


PlayerComponent::PlayerComponent()
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Initialize()
{
	mySpeed = 3.f;

	myObject->GetScene().PushCameraController(std::make_shared<SB::BirdsEyeController>(myObject->AsPointer(), 5.f, -QuarterPi, 0.8f, 0.f));

	//Note: this may cause double initialization - remove if so
	myObject->GetComponent<PlayerHealthComponent>()->Initialize();
}

void PlayerComponent::Update(const SB::Time& aDeltaTime)
{
	SB::Vector3f moveAmount;

	if (myInput.GetHeldKeyDown(SB::KeyboardKey::eA))
	{
		moveAmount += SB::Vector3f(-1.f, 0.f, -1.f);
	}
	if (myInput.GetHeldKeyDown(SB::KeyboardKey::eD))
	{
		moveAmount += SB::Vector3f(1.f, 0.f, 1.f);
	}
	if (myInput.GetHeldKeyDown(SB::KeyboardKey::eW))
	{
		moveAmount += SB::Vector3f(-1.f, 0.f, 1.f);
	}
	if (myInput.GetHeldKeyDown(SB::KeyboardKey::eS))
	{
		moveAmount += SB::Vector3f(1.f, 0.f, -1.f);
	}

	if (moveAmount != SB::Vector3f::Zero)
	{
		myObject->AddPosition(moveAmount.GetNormalized() * mySpeed * aDeltaTime.InSeconds());
	}
}

void PlayerComponent::LoadData(SB::DataNode aProperties)
{
	auto healthComponent = myObject->CreateComponent<PlayerHealthComponent>();
	healthComponent->LoadData(aProperties);
}

void PlayerComponent::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("type", "PlayerComponent");

	aSerializer.WriteObject("properties");
	auto healthComponent = myObject->GetComponent<PlayerHealthComponent>();
	healthComponent->ToJson(aSerializer);
	aSerializer.StepOut();
}

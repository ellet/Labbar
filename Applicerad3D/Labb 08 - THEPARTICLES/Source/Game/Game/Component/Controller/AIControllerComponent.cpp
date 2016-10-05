#include "stdafx.h"
#include "AIControllerComponent.h"
#include "Game/Component/Shooting/ShootingComponent.h"

AIControllerComponent::AIControllerComponent()
{
	myShootTimer = 0.0f;
}

AIControllerComponent::~AIControllerComponent()
{
}

void AIControllerComponent::Update(const SB::Time & aDeltaTime)
{
	myShootTimer += aDeltaTime.InSeconds();
	if (myShootTimer > 1.f)
	{
		SB::Vector3f dir = myPlayer->GetPosition() - myObject->GetPosition();
		dir.Normalize();

		myObject->GetComponent<ShootingComponent>(0)->Shoot(dir);
		myShootTimer = 0.f;
	}
	myObject->RotateAlongAxis(SB::Vector3f(0.0f, 1.0f, 0.0f), 0.1f * aDeltaTime.InSeconds());
}

void AIControllerComponent::SetPlayer(std::shared_ptr<SB::GameObject> aPlayer)
{
	myPlayer = aPlayer;
}

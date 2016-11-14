#include "stdafx.h"
#include "AIControllerComponent.h"

AIControllerComponent::AIControllerComponent()
{
}

AIControllerComponent::~AIControllerComponent()
{
}

void AIControllerComponent::OnRemoved()
{
	myPlayer = nullptr;
}

void AIControllerComponent::Update(const SB::Time & aDeltaTime)
{
}

void AIControllerComponent::SetPlayer(const SB::ObjectPtr & aPlayer)
{
	myPlayer = aPlayer;
}

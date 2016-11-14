#include "stdafx.h"
#include "BeamShotComponent.h"
#include <Engine/Physics/PhysicsComponent.h>


BeamShotComponent::BeamShotComponent()
{
	mySourcePosition = SB::Vector3f::Zero;
	myTargetPosition = SB::Vector3f::Zero;
	myLifeTime = 2.f;
	myHasMoved = false;
}

BeamShotComponent::~BeamShotComponent()
{
}


void BeamShotComponent::Update(const SB::Time& aDeltaTime)
{
	ShotComponent::Update(aDeltaTime);
	UpdateMovement(aDeltaTime);
}

void BeamShotComponent::UpdateMovement(const SB::Time& aDeltaTime)
{
	if (myHasMoved == true)
	{
		return;
	}

	myObject->SetPosition(myTargetPosition); //GetComponent<SB::PhysicsComponent>()->SetObjectPosition(myTargetPosition);
	myHasMoved = true;
}

void BeamShotComponent::SetData(const SB::Vector3f& aSourcePosition, const SB::Vector3f& aTargetPosition, const float aLifeTime)
{
	mySourcePosition = aSourcePosition;
	myTargetPosition = aTargetPosition;
	myLifeTime = aLifeTime;
}

//void BeamShotComponent::SetData(const BeamWeaponData& aData)
//{
//}

#include "stdafx.h"
#include "HomingShotComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include <Engine/Physics/PhysicsComponent.h>


HomingShotComponent::HomingShotComponent()
{
	myTargetsInRange.Reserve(8);
	myTrackingDelay = 0.f;
	myTargetSwitchingTimer = 0.f;
	myTargetSwitchingCooldown = 0.f;
	myCurrentTarget = nullptr;
	myLifeTime = 30.f;

	myProjectileRotationDegreesPerSecond = 1080.f;
	if (myRandomizer.GetRandomValue(0.f, 1.f) >= 0.5f)
	{
		myProjectileRotationDegreesPerSecond *= -1;
	}
}

HomingShotComponent::~HomingShotComponent()
{
	myCurrentTarget = nullptr;
	myTargetsInRange.RemoveAll();
}

void HomingShotComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
}

void HomingShotComponent::OnRemoved()
{
	myCurrentTarget = nullptr;
	myTargetsInRange.RemoveAll();
}

void HomingShotComponent::Update(const SB::Time& aDeltaTime)
{
	ShotComponent::Update(aDeltaTime);

	UpdateHoming(aDeltaTime);
	UpdateAcceleration(aDeltaTime);
	UpdateRotation(aDeltaTime);
}

void HomingShotComponent::SetData(const HomingWeaponData& aData)
{
	myProjectileRotationDegreesPerSecond = aData.projectileRotationDegreesPerSecond;
	myProjectileSpeedMax = aData.shotSpeedMax;
	myTrackingDelay = aData.shotTrackingDelay;
	myTargetSwitchingCooldown = aData.targetSwitchingCooldown;
}

void HomingShotComponent::UpdateRotation(const SB::Time& aDeltaTime)
{
	float rotationAmount = DEGREES_TO_RADIANSF((myProjectileRotationDegreesPerSecond * (myAge.InSeconds() / (myLifeTime.InSeconds() * 0.5f) )) * aDeltaTime.InSeconds());
	myObject->GetRotation().RotateAroundLocalZ(rotationAmount);
}

void HomingShotComponent::UpdateAcceleration(const SB::Time& aDeltaTime)
{
	const float CurrentSpeed = myObject->GetComponent<SB::PhysicsComponent>()->GetSpeed();
	if (CurrentSpeed >= myProjectileSpeedMax || myTrackingDelay.InSeconds() <= 0.f) 
	{
		return; //No acceleration to perform, abort
	}


	const float AccelerationAmount = ((myProjectileSpeedMax - CurrentSpeed) / myTrackingDelay.InSeconds()) * aDeltaTime.InSeconds();
	float newSpeed = CurrentSpeed + AccelerationAmount;
	if (newSpeed > myProjectileSpeedMax)
	{
		newSpeed = myProjectileSpeedMax;
	}

	myObject->GetComponent<SB::PhysicsComponent>()->SetSpeed(newSpeed);
}

void HomingShotComponent::UpdateHoming(const SB::Time& aDeltaTime)
{
	//Perform target switching timer tick if we're on cooldown
	if (myTargetSwitchingTimer > 0.f)
	{
		myTargetSwitchingTimer -= aDeltaTime;
		if (myTargetSwitchingTimer < 0.f)
		{
			myTargetSwitchingTimer = 0.f;
		}
	}

	//Update target tracking
	if (myAge.InSeconds() >= myTrackingDelay.InSeconds())
	{
		//Update target tracking if we're not on cooldown to switch targets
		if (myTargetSwitchingTimer <= 0.f)
		{
			SB::ObjectPtr closestTarget = GetClosestAvailableTarget();
			if (closestTarget != nullptr)
			{
				//If we've found a different target from last time, activate target switching cooldown and update new target as current
				if (myCurrentTarget == nullptr || closestTarget != myCurrentTarget)
				{
					myCurrentTarget = closestTarget;
					myTargetSwitchingTimer = myTargetSwitchingCooldown;
				}
			}
		}

		//Update homing - follow current (closest) target, if any
		if (myCurrentTarget != nullptr)
		{
			//Change course to follow target
			SB::Vector3f directionToTarget = (myCurrentTarget->GetTransformation().GetPosition() - myObject->GetTransformation().GetPosition()).Normalize(); //Instant tracking, TODO: apply gradual tracking if desired
			myObject->GetComponent<SB::PhysicsComponent>()->SetForceDirection(directionToTarget);

			//TODO: Also set orientation to face target (requires actual model for testing, hence to do)
		}

		myTargetsInRange.RemoveAll();
	}
}

void HomingShotComponent::RecieveEvent(const SB::TriggerCollisionEvent& aEvent)
{
	//Add to list of possible targets if the outer target-scanning collision trigger triggered the event
	if(aEvent.myColliderIndex == 1)
		myTargetsInRange.Add(aEvent.myGameObject->AsPointer());

	//Handle collision for the actual projectile collision trigger
	if(aEvent.myColliderIndex == 0)
		ShotComponent::RecieveEvent(aEvent);
}

//Determine closest available target from list of potential targets
SB::ObjectPtr HomingShotComponent::GetClosestAvailableTarget()
{
	if (myTargetsInRange.Size() > 0)
	{
		unsigned short closestTargetIndex = 0;
		float distanceBetweenPreviousClosest = FLT_MAX;

		for (unsigned short i = 0; i < myTargetsInRange.Size(); ++i)
		{
			float distanceBetweenCurrent = (myTargetsInRange[i]->GetPosition() - myObject->GetPosition()).Length2();

			if (distanceBetweenCurrent < distanceBetweenPreviousClosest)
			{
				closestTargetIndex = i;
				distanceBetweenPreviousClosest = (myTargetsInRange[closestTargetIndex]->GetPosition() - myObject->GetPosition()).Length2();
			}
		}

		return myTargetsInRange[closestTargetIndex];
	}
	
	return nullptr;
}

#pragma once
#include "AIControllerComponent.h"
#include "InterceptorActionCalculator.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"

namespace SB
{
	class Randomizer;
	class PhysicsComponent;
	class ColliderComponent;
	struct CollisionEvent;
	struct TriggerCollisionEvent;
	class SpeakerComponent;
}

class WeaponComponent;

class AIInterceptorComponent :
	public AIControllerComponent, public SB::EventSubscriber<SB::CollisionEvent>, public SB::EventSubscriber<SB::TriggerCollisionEvent>
{
	friend InterceptorActionCalculator;

public:
	AIInterceptorComponent();
	~AIInterceptorComponent();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Initialize() override;

	virtual void Render() const override;
	virtual void RecieveEvent(const SB::CollisionEvent & aEvent) override;
	virtual void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;
	virtual void LoadData(SB::DataNode aProperties) override;


	virtual void ToJson() const override;

private:

	void RotateTowardsPlayer(const SB::Time aDeltaTime);
	void Accelerate(const SB::Time & aDeltaTime);
	void Break(const SB::Time & aDeltaTime);
	void ResetActionSpecificVariables();
	void DebugDraw() const;
	void TurnAwayFromPlayer(const SB::Time & aDeltaTime);
	void TurnAwayFromPoint(const SB::Time & aDeltaTime);
	void ShootAtPlayer();

	SB::GrowingArray<const SB::GameObject*> myNearbyObjects;
	SB::Vector3f myTurningDirection;
	SB::Vector3f myTurnAwayFromCluster;
	SB::Vector3f myTurnAwayFromObject;
	SB::Vector3f myTriggerColliderOffset;
	InterceptorActionCalculator myActionCalc;
	SB::Randomizer* myRandomizer;
	SB::PhysicsComponent* myPhysicsComponent;
	SB::ColliderComponent* myTriggerComponent;
	SB::SpeakerComponent* mySpeakerComponent;
	WeaponComponent* myWeaponComponent;
	ActionScoreResult myLastResult; // for debugging
	float myForwardMaxSpeed;
	float myForwardCurrentSpeed;
	float myAcceleration;
	float myBreakPower;
	float myDistanceToPlayer;
	float myAngleToPlayer;
	float myShootingDelta;
	float myForwardMinSpeed;
	float myHasCollidedTimer;
	float myLengthToTurnAwayFromPoint;
	float myDistanceToNearestPoint;
	float myTurningTimer;
	bool myIsRotating;
	bool myIsTurning;
};


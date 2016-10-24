#pragma once
#include "AIControllerComponent.h"
#include "InterceptorActionCalculator.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"

namespace SB
{
	class Randomizer;
	class PhysicsComponent;
	struct CollisionEvent;
	struct TriggerCollisionEvent;
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
	SB::Vector3f myTurnAwayFromPoint;
	InterceptorActionCalculator myActionCalc;
	SB::Randomizer* myRandomizer;
	SB::PhysicsComponent* myPhysicsComponent;
	WeaponComponent* myWeaponComponent;
	float myForwardMaxSpeed;
	float myForwardCurrentSpeed;
	float myAcceleration;
	float myBreakPower;
	float myDistanceToPlayer;
	float myAngleToPlayer;
	float myShootingDelta;
	float myForwardMinimumSpeed;
	float myHasCollidedTimer;
	bool myIsRotating;
	bool myIsTurning;
};


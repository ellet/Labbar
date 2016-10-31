#include "stdafx.h"
#include "AIInterceptorComponent.h"
#include "..\Engine\Engine\Physics\PhysicsComponent.h"
#include "..\Engine\Engine\Physics\PhysicsComponent.h"
#include "..\Utilities\Utilities\Math\MathMacros.h"
#include "..\Game\Game\Component\Shooting\WeaponComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionFilter.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"
#include <Engine\Camera\Controllers\FirstPersonCameraController.h>

AIInterceptorComponent::AIInterceptorComponent()
{
	myHasCollidedTimer = 0.f;
	myRandomizer = nullptr;
	myIsRotating = false;
	myForwardCurrentSpeed = 0.0f;
	myForwardMaxSpeed = 200.0f;
	myAcceleration = 30.0f;
	myForwardMinimumSpeed = 20.f;
	myBreakPower = 100.0f;
	myTurningDirection = SB::Vector3f::Zero;
	myIsTurning = false;
}

AIInterceptorComponent::~AIInterceptorComponent()
{
	delete myRandomizer;
	myRandomizer = nullptr;
}

void AIInterceptorComponent::Update(const SB::Time & aDeltaTime)
{
	switch (myActionCalc.CalculateActionScore(this))
	{
	case ActionScoreResult::eAccelerate:
		Accelerate(aDeltaTime);
		ResetActionSpecificVariables();
		//std::cout << "move" << std::endl;
		break;
	case ActionScoreResult::eStartToBreak:
		Break(aDeltaTime);
		ResetActionSpecificVariables();
		//std::cout << "break" << std::endl;
		break;
	case ActionScoreResult::eTurnAwayFromPoint:
		TurnAwayFromPoint(aDeltaTime);
		//std::cout << "turning from Point" << std::endl;
		break;
	case ActionScoreResult::eTurnAwayFromPlayer:
		TurnAwayFromPlayer(aDeltaTime);
		//std::cout << "turning" << std::endl;
		break;
	case ActionScoreResult::eRotateTowardsPlayer:
		RotateTowardsPlayer(aDeltaTime);
		ResetActionSpecificVariables();
		//std::cout << "rotate" << std::endl;
		break;
	case ActionScoreResult::eShootAtPlayer:
		ShootAtPlayer();
		ResetActionSpecificVariables();
		//std::cout << "Shoot" << std::endl;
		break;
	default:
		//std::cout << "default" << std::endl;
		break;
	}
	if (myHasCollidedTimer <= 0.f)
	{
		myPhysicsComponent->SetForceDirection(myObject->GetRotation().GetForward());
		myPhysicsComponent->SetSpeed(myForwardCurrentSpeed);
	}
	myShootingDelta -= aDeltaTime.InSeconds();
	if (myShootingDelta < -1.f)
	{
		myShootingDelta = -1.f;
	}
	myHasCollidedTimer -= aDeltaTime.InSeconds();
	myNearbyObjects.RemoveAll();
	AIControllerComponent::Update(aDeltaTime);
}

void AIInterceptorComponent::Initialize()
{
	SetPlayer(myObject->GetScene().FindObject("Player"));
	myActionCalc.SetObjects(&*myPlayer, myObject);
	myNearbyObjects.Reserve(myObject->GetScene().GetNumberOfObjects());
	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();
	myWeaponComponent = &*myObject->GetComponent<WeaponComponent>();
	myRandomizer = new SB::Randomizer;
	myRandomizer->SetSeed(time(0));
	myShootingDelta = 0.0f;
	BaseComponent::Initialize();
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());

	//SB::ObjectPtr follower = myObject->GetScene().CreateGameObject("folower");
	//follower->SetParent(myObject->AsPointer());
	//follower->SetPosition(SB::Vector3f(0.f, 10.f, -20.f));
	//SB::Quaternion q;
	//q.RotateAroundLocalX(Pi / 32.f);
	//follower->SetRotation(q);
	//follower->Initialize();

	//myObject->GetScene().PushCameraController(std::make_shared<SB::FirstPersonCameraController>(&*follower));
}

void AIInterceptorComponent::Render() const
{
	DebugDraw();
}

void AIInterceptorComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	myHasCollidedTimer = 2.f;
	myForwardCurrentSpeed = 0.0f;
	myPhysicsComponent->SetDrag(100.f);
}


void AIInterceptorComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	myNearbyObjects.Add(aEvent.myGameObject);
}

void AIInterceptorComponent::LoadData(SB::DataNode aProperties)
{
	myForwardMaxSpeed = aProperties["forwardMax"].GetFloat();
	myAcceleration = aProperties["acceleration"].GetFloat();
}

void AIInterceptorComponent::RotateTowardsPlayer(const SB::Time aDeltaTime)
{
	myIsRotating = true;
	SB::Vector3f epsilonVector(0.0000f, 0.0000f, 0.0000f);
	myAngleToPlayer;
	if (myAngleToPlayer >= 179.f && myAngleToPlayer  <= 181.f)
	{
		epsilonVector = SB::Vector3f(0.1f, 0.0000f, 0.0000f);
	}
	if (myAngleToPlayer > 1.f)
	{
		if (myAngleToPlayer < 10)
		{
			myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myPlayer->GetPosition() + epsilonVector, aDeltaTime.InSeconds(),1.f);
		}
		else
		{
			myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myPlayer->GetPosition() + epsilonVector, aDeltaTime.InSeconds(), 0.2f);
		}
	}
}

void AIInterceptorComponent::Accelerate(const SB::Time & aDeltaTime)
{
	if (myForwardCurrentSpeed < myForwardMaxSpeed)
	{
		myForwardCurrentSpeed += myAcceleration * aDeltaTime.InSeconds();
	}
}

void AIInterceptorComponent::Break(const SB::Time & aDeltaTime)
{

	if (myForwardCurrentSpeed > myForwardMinimumSpeed)
	{
		myForwardCurrentSpeed -= myBreakPower * aDeltaTime.InSeconds();
	}
}

void AIInterceptorComponent::ResetActionSpecificVariables()
{
	myIsTurning = false;
}

void AIInterceptorComponent::DebugDraw() const
{
	SB::Engine::GetDebugger().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetRight().GetNormalized() * 5.f, SB::Vector4f(1.f, 0.f, 0.f, 1.f));
	SB::Engine::GetDebugger().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetUpward().GetNormalized() * 5.f, SB::Vector4f(0.f, 1.f, 0.f, 1.f));
	SB::Engine::GetDebugger().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetForward().GetNormalized() * 5.f, SB::Vector4f(0.f, 0.f, 1.f, 1.f)); 
	SB::Engine::GetDebugger().DrawLine(myObject->GetPosition(), myPlayer->GetPosition() , SB::Vector4f(0.f, 0.f, 1.f, 1.f));
} 

void AIInterceptorComponent::TurnAwayFromPlayer(const SB::Time & aDeltaTime)
{
	if (myIsTurning == false)
	{
		float randVal = myRandomizer->GetRandomValue(0.f, 4.f);
		if (randVal > 3.f)
		{
			myTurningDirection = myObject->GetRotation().GetLeft();
		}
		else if (randVal > 2.f)
		{
			myTurningDirection = myObject->GetRotation().GetRight();
		}
		else if (randVal > 1.f)
		{
			myTurningDirection = myObject->GetRotation().GetDownward();
		}
		else
		{
			myTurningDirection = myObject->GetRotation().GetUpward();
		}
		myIsTurning = true;
	}
	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myTurningDirection * 100.f + myObject->GetRotation().GetForward() * 50.f, aDeltaTime.InSeconds(), 1.f);
}

void AIInterceptorComponent::TurnAwayFromPoint(const SB::Time & aDeltaTime)
{
	if (myIsTurning == false)
	{
		float randVal = myRandomizer->GetRandomValue(0.f, 1.f);
		SB::Vector3f dirToCluster(myTurnAwayFromPoint - myObject->GetPosition());
		dirToCluster.Normalize();
		SB::Vector3f random(myRandomizer->GetRandomValue(0.f, 1.f), myRandomizer->GetRandomValue(0.f, 1.f), myRandomizer->GetRandomValue(0.f, 1.f));
		random.Normalize();
		SB::Vector3f newDir = SB::Vector3f::Cross(dirToCluster,random);
		newDir.Normalize();
		SB::Vector3f newDir2 = ((myTurnAwayFromPoint + newDir * 150.f) - myObject->GetPosition());
		myTurningDirection = newDir2.Normalize();

		myIsTurning = true;
	}
	
	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myTurningDirection * 200.f, aDeltaTime.InSeconds(), 1.f);
}

void AIInterceptorComponent::ShootAtPlayer()
{
	if (myShootingDelta < 0.f)
	{
		myWeaponComponent->SetLayerID(static_cast<unsigned int>(CollisionFilter::eEnemy));
		myWeaponComponent->SetCollisonFilters(CollisionFilter::ePlayer | CollisionFilter::eEnviorment);
		myWeaponComponent->FireWeapon(myObject->GetTransformation().GetPosition() + myObject->GetRotation().GetForward() * 20.f, myObject->GetRotation());
		myShootingDelta = .2f;
	}
}

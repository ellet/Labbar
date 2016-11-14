#include "stdafx.h"
#include "AIInterceptorComponent.h"
#include "..\Engine\Engine\Physics\PhysicsComponent.h"
#include "..\Utilities\Utilities\Math\MathMacros.h"
#include "..\Game\Game\Component\Shooting\Weapons\WeaponComponent.h"
#include "..\Engine\Engine\Component\Collider\CollisionFilter.h"
#include "..\Engine\Engine\Component\Collider\ColliderComponent.h"
#include "Engine\Component\Collider\TriggerCollisionEvent.h"
#include <Engine\Camera\Controllers\FirstPersonCameraController.h>
#include "Engine\SoundManager\SpeakerComponent.h"
#include "Engine/SoundManager/SoundManager.h"
#include "..\Engine\Engine\Debugging\DebugDrawer.h"

AIInterceptorComponent::AIInterceptorComponent()
{
	myHasCollidedTimer = 0.f;
	myRandomizer = nullptr;
	myIsRotating = false;
	myForwardCurrentSpeed = 0.0f;
	myForwardMinSpeed = 20.f;
	myForwardMaxSpeed = 200.0f;
	myAcceleration = 30.0f;
	myBreakPower = 10.0f;
	myLengthToTurnAwayFromPoint = 0.f;
	myTurningDirection = SB::Vector3f::Zero;
	myPhysicsComponent = nullptr;
	myTriggerComponent = nullptr;
	mySpeakerComponent = nullptr;
	myIsTurning = false;
	myDistanceToNearestPoint = 10000.f;
}

AIInterceptorComponent::~AIInterceptorComponent()
{
	delete myRandomizer;
	myRandomizer = nullptr;
}

void AIInterceptorComponent::Update(const SB::Time & aDeltaTime)
{
	auto hej = myObject->GetComponent<SB::ColliderComponent>();
	//myTriggerComponent->UpdatePosition(myObject->GetTransformation().GetPosition());
	myLastResult = myActionCalc.CalculateActionScore(this);
	switch (myLastResult)
	{
	case ActionScoreResult::eAccelerate:
		Accelerate(aDeltaTime);
		ResetActionSpecificVariables();
		//std::cout << "move" << std::endl;
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
		if (myForwardCurrentSpeed > 10.f)
		{
			mySpeakerComponent->PostSoundEvent("Play_Interceptor_Movement");
		}
		else
		{
			//SB::Engine::GetSoundManager().PostEvent("Play_Interceptor_Movement", mySoundID);
		}
	}
	SB::Vector3f possie = myObject->GetWorldPosition();
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
	if (myObject->GetComponent<SB::ColliderComponent>()->GetIsTrigger() == true)
	{
		myTriggerComponent = &*myObject->GetComponent<SB::ColliderComponent>();
	}
	else
	{
		myTriggerComponent = &*myObject->GetComponent<SB::ColliderComponent>(1);
		if (myTriggerComponent == nullptr)
		{
			Error("Collider Component (assumed to not be trigger) on object " + myObject->GetIdentifier() + " doesn't exist. The AI Interceptor Component is looking for it.")
		}
	}
	myTriggerColliderOffset = myTriggerComponent->GetOffset();

	if (myPhysicsComponent == nullptr)
	{
		Error("Physics Component on object " + myObject->GetIdentifier() + " doesn't exist. The AI Interceptor Component is looking for it.")
	}
	myWeaponComponent = &*myObject->GetComponent<WeaponComponent>();

	if (myWeaponComponent == nullptr)
	{
		Error("Weapon Component on object " + myObject->GetIdentifier() + " doesn't exist. The AI Interceptor Component is looking for it.")
	}

	mySpeakerComponent = &*myObject->GetComponent<SB::SpeakerComponent>();
	if (mySpeakerComponent == nullptr)
	{
		Error("Speaker Component on object " + myObject->GetIdentifier() + " doesn't exist. The AI Interceptor Component is looking for it.")
	}

	myWeaponComponent->SetUser(myObject);
	myRandomizer = new SB::Randomizer;
	myRandomizer->SetSeed(time(0));
	myShootingDelta = 0.0f;
	BaseComponent::Initialize();
	myObject->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::eEnemy);
	myObject->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(0 | CollisionFilter::eEnemy);
	myObject->GetComponent<SB::ColliderComponent>(1)->SetColliderLayerID(CollisionFilter::eDefault);
	myObject->GetComponent<SB::ColliderComponent>(1)->SetCollisionFilter(CollisionFilter::eEnvironment| CollisionFilter::eEnemy | CollisionFilter::ePlayer);

	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());

	//SB::ObjectPtr follower = myObject->GetScene().CreateGameObject("folower");
	//follower->SetParent(myObject->AsPointer());
	//follower->SetPosition(SB::Vector3f(0.f, 10.f, -20.f));.
	//SB::Quaternion q;
	//q.RotateAroundLocalX(Pi / 32.f);
	//follower->SetRotation(q);
	//follower->Initialize();

	//myObject->GetScene().PushCameraController(std::make_shared<SB::FirstPersonCameraController>(&*follower));
}

void AIInterceptorComponent::Render() const
{
	//DebugDraw();
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
	myForwardMaxSpeed = aProperties["maxForwardSpeed"].GetFloat();
	myForwardMinSpeed = aProperties["minForwardSpeed"].GetFloat();
	myBreakPower = aProperties["breakPower"].GetFloat();
	myAcceleration = aProperties["acceleration"].GetFloat();

	if (aProperties.HasMember("forwardCurrentSpeed"))
	{
		myForwardCurrentSpeed = aProperties["forwardCurrentSpeed"].GetFloat();
	}
	myActionCalc.LoadData(aProperties);
}


void AIInterceptorComponent::ToJson()const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("type", "AIInterceptorComponent");

	serializer.WriteObject("properties");
	serializer.WriteNode("maxForwardSpeed", myForwardMaxSpeed);
	serializer.WriteNode("minForwardSpeed", myForwardMinSpeed);
	serializer.WriteNode("breakPower", myBreakPower);
	serializer.WriteNode("acceleration", myAcceleration);
	serializer.WriteNode("forwardCurrentSpeed", myForwardCurrentSpeed);
	myActionCalc.ToJson();
	serializer.StepOut();
}

void AIInterceptorComponent::RotateTowardsPlayer(const SB::Time aDeltaTime)
{
	myIsRotating = true;
	SB::Vector3f epsilonVector(0.0000f, 0.0000f, 0.0000f);
	myAngleToPlayer;
	if (myAngleToPlayer >= 179.f && myAngleToPlayer <= 181.f)
	{
		epsilonVector = SB::Vector3f(0.1f, 0.0000f, 0.0000f);
	}
	if (myAngleToPlayer > 1.f)
	{
		//if (myAngleToPlayer < 10)
		//{
		//	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myPlayer->GetPosition() + epsilonVector, aDeltaTime.InSeconds(), 3.f);
		//}
		//else
		//{
		//	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myPlayer->GetPosition() + epsilonVector, aDeltaTime.InSeconds(), 1.f);
		//}


		float trea = 3.f;
		
		if (myAngleToPlayer >= 10)
		{
			trea = 1.f;
		}
		SB::Quaternion & q = myObject->GetRotation();
		SB::Vector3f pos = myObject->GetPosition();
		SB::Vector3f playerPos = myPlayer->GetPosition();
		 
		q.RotateTowardsPoint(pos, playerPos + epsilonVector, aDeltaTime.InSeconds(), trea);
	}
}

void AIInterceptorComponent::Accelerate(const SB::Time & aDeltaTime)
{
	if (myForwardCurrentSpeed < myForwardMaxSpeed)
	{
		myForwardCurrentSpeed += myAcceleration * aDeltaTime.InSeconds();
	}
	if (myForwardCurrentSpeed > myForwardMaxSpeed)
	{
		myForwardCurrentSpeed = myForwardMaxSpeed;
	}
}

void AIInterceptorComponent::Break(const SB::Time & aDeltaTime)
{

	if (myForwardCurrentSpeed > myForwardMinSpeed)
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
	SB::Engine::GetDebugDrawer().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetRight().GetNormalized() * 5.f, SB::Vector4f(1.f, 0.f, 0.f, 1.f));
	SB::Engine::GetDebugDrawer().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetUpward().GetNormalized() * 5.f, SB::Vector4f(0.f, 1.f, 0.f, 1.f));
	SB::Engine::GetDebugDrawer().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + GetGameObject().GetRotation().GetForward().GetNormalized() * 5.f, SB::Vector4f(0.f, 0.f, 1.f, 1.f));
	SB::Engine::GetDebugDrawer().DrawLine(GetGameObject().GetPosition(), GetGameObject().GetPosition() + myTurningDirection * 50.f, SB::Vector4f(0.f, 0.f, 1.f, 1.f));
	
	SB::Engine::GetDebugDrawer().DrawLine(myObject->GetPosition(), myPlayer->GetPosition(), SB::Vector4f(0.f, 0.f, 1.f, 1.f));
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
	//Break(aDeltaTime);
	float turningRadius = 5.0f;
	bool turnAwayFromCluster = true;
	if (myDistanceToNearestPoint < 60.f * 60.f)
	{
		turningRadius = 10.f;
		turnAwayFromCluster = false;
	}
	if (myTurningTimer < 0.0f)
	{
		SB::Vector3f dirToPoint;
		if (turnAwayFromCluster == true)
		{
			dirToPoint = SB::Vector3f(myTurnAwayFromCluster - myObject->GetPosition());
		}
		else
		{
			dirToPoint = SB::Vector3f(myTurnAwayFromObject - myObject->GetPosition());
		}
		myLengthToTurnAwayFromPoint = dirToPoint.Length();
		dirToPoint.Normalize();
		SB::Vector3f perpVec;
		if (turnAwayFromCluster == true)
		{
			perpVec = SB::Vector3f(0.4f, 0.4f, 0.4f);// SB::Vector3f(myRandomizer->GetRandomValue(0.f, 1.f), myRandomizer->GetRandomValue(0.f, 1.f), myRandomizer->GetRandomValue(0.f, 1.f));
		}
		else
		{
			perpVec = (myTurnAwayFromCluster - myTurnAwayFromObject);
		}
		perpVec.Normalize();
		SB::Vector3f newDir = SB::Vector3f::Cross(dirToPoint, perpVec);
		newDir.Normalize();
		myTurningDirection = ((myObject->GetPosition()/* - myObject->GetRotation().GetForward() * 15.f */ + newDir * 10.f) - myObject->GetPosition());
		myTurningDirection.Normalize();
		myIsTurning = true;
		myTurningTimer = 1.1f;
	}
	if (myForwardCurrentSpeed > myForwardMaxSpeed * 0.75f)
	{
		//Break(aDeltaTime);
	}
	myTurningTimer -= aDeltaTime.InSeconds();
	if (turnAwayFromCluster == false)
	{
		myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myObject->GetPosition() + myTurningDirection * myLengthToTurnAwayFromPoint, aDeltaTime.InSeconds(), turningRadius);
		return;
	}
	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myObject->GetPosition() + myTurningDirection * myLengthToTurnAwayFromPoint, aDeltaTime.InSeconds(), turningRadius);
}

void AIInterceptorComponent::ShootAtPlayer()
{
	SB::PhysicsComponent* playerPhys = &*myPlayer->GetComponent<SB::PhysicsComponent>();
	float playerSpeed = playerPhys->GetSpeed();
	if (myShootingDelta < 0.f)
	{
		myWeaponComponent->SetLayerID(static_cast<unsigned int>(CollisionFilter::eEnemy));
		myWeaponComponent->SetCollisonFilters(CollisionFilter::ePlayer | CollisionFilter::eEnvironment);
 		SB::Quaternion shotRotation = myObject->GetRotation();
		myWeaponComponent->FireWeapon(myObject->GetTransformation().GetPosition() + myObject->GetRotation().GetForward() * 20.f,
			SB::Quaternion::CreateFromVectors(myObject->GetTransformation().GetPosition(),
				myPlayer->GetPosition() + ((playerSpeed <= 0.f) ? SB::Vector3f::Zero : (playerPhys->GetForceDirection() * playerSpeed * 0.5f)),
				myObject->GetRotation().GetUpward()));
		myShootingDelta = .2f;
	}
}

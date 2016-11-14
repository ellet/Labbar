#include "stdafx.h"
#include "PhysicsComponent.h"
#include "..\Component\Collider\ColliderComponent.h"
#include "CollisionData.h"
#include "..\CollisionHandling\ColliderData.h"

namespace ENGINE_NAMESPACE
{

	PhysicsComponent::PhysicsComponent()
	{
		myMoveToPosition = Vector3f::Zero;
		myIsInitialized = false;
		mySphereCollider = std::make_unique<SphereCollider>();
		SetForceDirection(Vector3f::UnitZ);
		SetCollisionForceReduction(0.8f);
		myMoveToSet = false;
		mySpeed = 0.f;
		myDrag = 0.f;

		myIndexInManager = 0;
	}


	PhysicsComponent::~PhysicsComponent()
	{
		if (myIsInitialized == true)
		{
			GetGameObject().GetScene().RemovePhysicsComponentToPhysicsManager(*this);
		}
	}

	void PhysicsComponent::Update(const Time & aDeltaTime)
	{
		(*mySphereCollider) = GetGameObject().GetComponent<ColliderComponent>()->GetCollider();

		HandleDrag(aDeltaTime);

		SetMoveToPosition(aDeltaTime);

	}

	void PhysicsComponent::Initialize()
	{
		myMoveToPosition = GetGameObject().GetPosition();
		GetGameObject().GetScene().AddPhysicsComponentToPhysicsManager(*this);
		myColliderComponent = &*GetGameObject().GetComponent<ColliderComponent>();
		if (myColliderComponent == nullptr)
		{
			Error("Could not find collider component on object " + myObject->GetIdentifier() + ". Physics component needs it");
		}
		(*mySphereCollider) = myColliderComponent->GetCollider();

		myIsInitialized = true;
	}

	void PhysicsComponent::LoadData(DataNode aProperties)
	{
		mySpeed = aProperties["StartSpeed"].GetFloat();

		myDrag = aProperties["Drag"].GetFloat();
		myForceDirection.x = aProperties["WorldDirection"][0].GetFloat();
		myForceDirection.y = aProperties["WorldDirection"][1].GetFloat();
		myForceDirection.z = aProperties["WorldDirection"][2].GetFloat();
	}

	void PhysicsComponent::ToJson() const
{
		SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
		serializer.WriteObject("properties");

		serializer.WriteNode("StartSpeed", mySpeed);
		serializer.WriteNode("Drag", myDrag);
		serializer.WriteNode("WorldDirection", myForceDirection);

		serializer.StepOut();
		serializer.WriteNode("type", "PhysicsComponent");
	}

	//Returns the estimated position of the object next frame
	/*Vector3f PhysicsComponent::GetNextEstimatedPosition(const Time& aDeltaTime) const
	{
		//Simulate drag
		float currentSpeed = mySpeed;
		if (myDrag > 0)
		{
			const float currentDrag = myDrag * aDeltaTime.InSeconds();

			currentSpeed = currentSpeed * (1.f - (currentDrag / 100.f));

			if (currentSpeed < 0.01f)
			{
				currentSpeed = 0.f;
			}
		}

		//Simulate movement
		Vector3f estimatedPosition = myObject->GetPosition();
		const float SpeedDelta = currentSpeed * aDeltaTime.InSeconds();

		const Vector3f PositionDelta(GetForceDirection() * SpeedDelta);

		estimatedPosition += PositionDelta;
	}*/

	bool PhysicsComponent::GetColliderIsTrigger()
	{
		return myColliderComponent->GetIsTrigger();
	}

	void PhysicsComponent::SetObjectPosition(const SB::Vector3f & aPosition)
	{
		myMoveToPosition = aPosition;
		GetGameObject().SetPosition(myMoveToPosition);
	}

	float PhysicsComponent::GetCollisionForceReduction() const
	{
		return myCollisionForceReduction;
	}

	ColliderData PhysicsComponent::GetColliderData() const
	{
		return GetGameObject().GetComponent<ColliderComponent>()->GetColliderData();
	}

	const SphereCollider & PhysicsComponent::GetMovedCollider() const
	{
		mySphereCollider->UpdatePosition(myMoveToPosition);
		return *mySphereCollider;
	}

	void PhysicsComponent::MoveObjectToPosition() const
	{
		if (myMoveToSet == true)
		{
			GetGameObject().SetPosition(myMoveToPosition);
		}


	}

	void PhysicsComponent::HandleDrag(const Time & aDeltaTime)
	{
		if (myDrag > 0)
		{
			const float tempDrag = myDrag * aDeltaTime.InSeconds();

			mySpeed = mySpeed * (1.f - (tempDrag / 100.f));

			if (mySpeed < 0.01f)
			{
				mySpeed = 0.f;
			}
		}
	}

	void PhysicsComponent::SetMoveToPosition(const Time & aDeltaTime)
	{
		myMoveToSet = true;

		Vector3f tempPosition = myObject->GetPosition();
		const float SpeedDelta = mySpeed * aDeltaTime.InSeconds();

		const Vector3f PositionDelta(GetForceDirection() * SpeedDelta);


		myMoveToPosition = tempPosition + PositionDelta;
	}

	void PhysicsComponent::HandleCollisionMovement(const CollisionData & aCollisionData)
	{
		SetForceDirection(aCollisionData.myDirection);
		mySpeed *= (1.f - GetCollisionForceReduction());
	}

	void PhysicsComponent::SetCollisionForceReduction(float aReduction)
	{
		myCollisionForceReduction = aReduction;
	}

	const Vector3f& PhysicsComponent::GetForceDirection() const
	{
		return myForceDirection;
	}

	void PhysicsComponent::SetForceDirection(const Vector3f & aForceDirection)
	{
		myForceDirection = aForceDirection;
	}

	float PhysicsComponent::GetSpeed() const
	{
		return mySpeed;
	}

	void PhysicsComponent::SetSpeed(float aSpeed)
	{
		mySpeed = aSpeed;
	}

	void PhysicsComponent::ApplyForce(const float aSpeed, const Vector3f & aDirection)
	{
		mySpeed = aSpeed;
		myForceDirection = aDirection;
	}

	float PhysicsComponent::GetDrag() const
	{
		return myDrag;
	}

	void PhysicsComponent::SetDrag(float aDragAmount)
	{
		myDrag = aDragAmount;
	}

}
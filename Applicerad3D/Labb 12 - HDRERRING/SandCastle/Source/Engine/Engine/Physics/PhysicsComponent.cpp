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
		GetGameObject().GetScene().AddPhysicsComponentToPhysicsManager(*this);
		(*mySphereCollider) = GetGameObject().GetComponent<ColliderComponent>()->GetCollider();
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
		//GetGameObject().SetRotation(Quaternion::CreateFromVectors(Vector3f::Zero, aCollisionData.myDirection, Vector3f(0.f, 1.f, 0.f)));
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
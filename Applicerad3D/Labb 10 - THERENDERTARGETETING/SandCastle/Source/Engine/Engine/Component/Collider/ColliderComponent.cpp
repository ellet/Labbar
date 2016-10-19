#include "stdafx.h"
#include "ColliderComponent.h"
#include "..\..\CollisionHandling\CollisionManager.h"
#include "RenderColliderComponent.h"

namespace ENGINE_NAMESPACE
{

	ColliderComponent::ColliderComponent()
	{
		myInitilzedFlag = false;
		myOffset = Vector3f::Zero;
		myIsTrigger = false;
		
		myColliderID = static_cast<unsigned int>(CollisionFilter::eDefault);
		myCollisionFilter = CollisionFilter::eDefault | CollisionFilter::eEnemy | CollisionFilter::ePlayer | CollisionFilter::eEnviorment;
	}

	ColliderComponent::~ColliderComponent()
	{
		RemoveColliderFromManager();
	}

	void ColliderComponent::Initialize()
	{
		myInitilzedFlag = true;
		AddColliderToManager();
	}

	void ColliderComponent::UpdatePosition(const Vector3f & aPosition)
	{
		myCollider.UpdatePosition(aPosition + myOffset);
	}

	void ColliderComponent::SetIsTrigger()
	{
		if (myInitilzedFlag == false)
		{
			myIsTrigger = true;
		}
	}	

	void ColliderComponent::SetRadius(const float aRadius)
	{
		myCollider.SetRadius(aRadius);
	}

	void ColliderComponent::SetPositionOffset(const Vector3f & aPositionOffset)
	{
		myOffset = aPositionOffset;
	}

	void ColliderComponent::SetOffsetAndRadius(const SphereShape & aSphereShape)
	{
		myCollider.SetRadius(aSphereShape.myRadius);
		myOffset = aSphereShape.myPosition;
	}

	void ColliderComponent::SetOffsetAndRadius(const Vector3f & aPosition, const float aRadius)
	{
		myOffset = aPosition;
		myCollider.SetRadius(aRadius);
	}
	

	void ColliderComponent::Update(const Time & aDeltaTime)
	{
		UpdatePosition(GetGameObject().GetTransformation().GetPosition());
	}

	void ColliderComponent::SetColliderLayedID(const CollisionFilter & aLayedID)
	{
		myColliderID = static_cast<unsigned int>(aLayedID);
	}

	void ColliderComponent::SetCollisionFilter(const unsigned int aCollisionFilter)
	{
		myCollisionFilter = aCollisionFilter;
	}

	ColliderData ColliderComponent::GetColliderData() const
	{
		ColliderData tempColliderData;
		tempColliderData.myCollider = &myCollider;
		tempColliderData.myGameObject = myObject;
		tempColliderData.myLayedID = &myColliderID;
		tempColliderData.myCollisionFilter = &myCollisionFilter;

		return tempColliderData;
	}

	void ColliderComponent::LoadData(DataNode aProperties)
	{
		SetRadius(aProperties["Radius"].GetFloat());
		
		myOffset.x = aProperties["Center"][0].GetFloat();
		myOffset.y = aProperties["Center"][1].GetFloat();
		myOffset.z = aProperties["Center"][2].GetFloat();

		if (aProperties["Trigger"].GetBool() == true)
		{
			SetIsTrigger();
		}

		const bool ShouldRenderCollider = aProperties["RenderCollider"].GetBool();
		
		if (ShouldRenderCollider == true)
		{
			myObject->CreateComponent<RenderColliderComponent>();
		}
	}

	void ColliderComponent::AddColliderToManager()
	{
		

		if (myIsTrigger == true)
		{
			myObject->GetScene().AddTriggerColliderToCollisionManager(GetColliderData());
		}
		else
		{
			myObject->GetScene().AddCollisionColliderToCollisionManager(GetColliderData());
		}
	}

	void ColliderComponent::RemoveColliderFromManager()
	{
		if (myInitilzedFlag == true)
		{
			if (myIsTrigger == true)
			{
				myObject->GetScene().RemoveTriggerColliderFromCollisionManager(GetColliderData());
			}
			else
			{
				myObject->GetScene().RemoveCollisionColliderFromCollisionManager(GetColliderData());
			}
		}
	}

}
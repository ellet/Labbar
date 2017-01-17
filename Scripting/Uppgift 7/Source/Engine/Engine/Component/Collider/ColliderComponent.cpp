#include "stdafx.h"
#include "ColliderComponent.h"

namespace SB
{

	ColliderComponent::ColliderComponent()
	{
		myInitilzedFlag = false;
		myOffset = Vector3f::Zero;
		
		myColliderType = ColliderTypes::eSphereCollider;
		myCollider = std::make_unique<SphereCollider>();

		myColliderID = static_cast<unsigned int>(CollisionFilter::eEnvironment);
		myCollisionFilter = static_cast<unsigned int>(CollisionFilter::eDefault);
	}

	ColliderComponent::~ColliderComponent()
	{
	}

	void ColliderComponent::Initialize()
	{
		UpdatePosition(GetGameObject().GetPosition());
		myInitilzedFlag = true;
	}

	void ColliderComponent::SetPositionOffset(const Vector3f & aPositionOffset)
	{
		myOffset = aPositionOffset;
	}
	
	void ColliderComponent::UpdatePosition(const Vector3f & aPosition)
	{
		myCollider->UpdatePosition(aPosition + myObject->AdjustOffset(myOffset));
	}

	
	void ColliderComponent::Update(const Time & aDeltaTime)
	{
		UpdatePosition(GetGameObject().GetTransformation().GetPosition());
	}

	void ColliderComponent::SetRadius(const float aRadius)
	{
		myCollider->SetRadius(aRadius);
	}

	float ColliderComponent::GetRadius() const
	{
		return myCollider->GetRadius();
	}

}


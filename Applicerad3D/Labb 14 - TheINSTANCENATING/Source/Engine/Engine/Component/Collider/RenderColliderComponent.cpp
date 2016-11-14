#include "stdafx.h"
#include "RenderColliderComponent.h"
#include "ColliderComponent.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "Engine\GameObject\GameObject.h"
#include "CollisionEvent.h"
#include "..\..\Physics\CollisionData.h"
#include "TriggerCollisionEvent.h"


namespace ENGINE_NAMESPACE
{
	bool RenderColliderComponent::ourShouldRenderCollidersFlag = false;

	const Vector4f NoCollisionColor = Vector4f(0.f, 1.f, 0.f, 1.f);
	const Vector4f CollisionColor = Vector4f(1.f, 0.f, 0.f, 1.f);
	const Vector4f TriggerColor = Vector4f(0.f, 0.f, 1.f, 1.f);

	RenderColliderComponent::RenderColliderComponent()
	{
	}


	RenderColliderComponent::~RenderColliderComponent()
	{
	}

	void RenderColliderComponent::Initialize()
	{

		myObject->AddEventSubscriber(EventSubscriber<CollisionEvent>::GetTypeIndex(), EventSubscriber<CollisionEvent>::GetInstanceIndex());
		myObject->AddEventSubscriber(EventSubscriber<TriggerCollisionEvent>::GetTypeIndex(), EventSubscriber<TriggerCollisionEvent>::GetInstanceIndex());

		unsigned short ColliderCount = myObject->GetComponentCount<ColliderComponent>();

		myRenderSpheres.Resize(ColliderCount);
		myHasCollidedFlags.Resize(ColliderCount);
		myHasTriggeredFlags.Resize(ColliderCount);
		myStopWatches.Resize(ColliderCount);
		myColors.Resize(ColliderCount);

		for (unsigned short iCollided = 0; iCollided < myHasCollidedFlags.Size(); ++iCollided)
		{
			myHasCollidedFlags[iCollided] = false;
			myHasTriggeredFlags[iCollided] = false;
		}

		
	}

	void RenderColliderComponent::DebugRender() const
	{
		if (ourShouldRenderCollidersFlag == true)
		{
			for (unsigned short iSphere = 0; iSphere < myRenderSpheres.Size(); ++iSphere)
			{
				SB::Engine::GetDebugDrawer().RenderShape(myRenderSpheres[iSphere], myColors[iSphere]);
			}
		}
	}

	void RenderColliderComponent::Update(const Time & aDeltaTime)
	{
		for (unsigned short iSphere = 0; iSphere < myRenderSpheres.Size(); ++iSphere)
		{
			myRenderSpheres[iSphere] = GetGameObject().GetComponent<ColliderComponent>(iSphere)->GetCollider().GetBasicSphere();
		}
		

		for (unsigned short iCollided = 0; iCollided < myHasCollidedFlags.Size(); ++iCollided)
		{
			myColors[iCollided] = NoCollisionColor;

			if (myHasCollidedFlags[iCollided] == true)
			{
				myColors[iCollided] = CollisionColor;

				if (myStopWatches[iCollided].GetElapsedTime() > 0.1f)
				{
					myHasCollidedFlags[iCollided] = false;
				}
			}
			else if (myHasTriggeredFlags[iCollided] == true)
			{
				myColors[iCollided] = TriggerColor;

				if (myStopWatches[iCollided].GetElapsedTime() > 0.1f)
				{
					myHasTriggeredFlags[iCollided] = false;
				}
			}
		}
		
	}

	void RenderColliderComponent::RecieveEvent(const CollisionEvent & aEvent)
	{
		unsigned short tempColliderIndex = aEvent.myCollisionData->myColliderIndex;
		myHasCollidedFlags[tempColliderIndex] = true;
		myStopWatches[tempColliderIndex].Restart();
	}

	void RenderColliderComponent::RecieveEvent(const TriggerCollisionEvent& aEvent)
	{
		unsigned short tempColliderIndex = aEvent.myColliderIndex;
		myHasTriggeredFlags[tempColliderIndex] = true;
		myStopWatches[tempColliderIndex].Restart();
	}


	void RenderColliderComponent::SwitchRenderColliders()
	{
		ourShouldRenderCollidersFlag = !ourShouldRenderCollidersFlag;
	}

	void RenderColliderComponent::ToJson() const
	{
		JsonSerializer &serializer = Engine::GetJsonSerializer();
		serializer.WriteObject("properties");
		serializer.StepOut();
		serializer.WriteNode("type", "RenderColliderComponent");
	}

}

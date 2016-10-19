#include "stdafx.h"
#include "RenderColliderComponent.h"
#include "ColliderComponent.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "Engine\GameObject\GameObject.h"
#include "CollisionEvent.h"


namespace ENGINE_NAMESPACE
{
	const Vector4f NoCollisionColor = Vector4f(0.f, 1.f, 0.f, 1.f);
	const Vector4f CollisionColor = Vector4f(1.f, 0.f, 0.f, 1.f);
	const Vector4f TriggerColor = Vector4f(0.f, 0.f, 1.f, 1.f);

	RenderColliderComponent::RenderColliderComponent()
	{
		myHasCollided = false;
		myHasTriggered = false;
	}


	RenderColliderComponent::~RenderColliderComponent()
	{
	}

	void RenderColliderComponent::Initialize()
	{
		myObject->AddEventSubscriber(EventSubscriber<CollisionEvent>::GetTypeIndex(), EventSubscriber<CollisionEvent>::GetInstanceIndex());
		myObject->AddEventSubscriber(EventSubscriber<TriggerCollisionEvent>::GetTypeIndex(), EventSubscriber<TriggerCollisionEvent>::GetInstanceIndex());

		myRenderSpheres.Resize(myObject->GetComponentCount<ColliderComponent>());

	}

	void RenderColliderComponent::Render() const
	{
		for (unsigned short iSphere = 0; iSphere < myRenderSpheres.Size(); ++iSphere)
		{
			//Engine::GetDebugger().RenderShape(myRenderSpheres[iSphere], myRenderColor);
		}
	}

	void RenderColliderComponent::Update(const Time & aDeltaTime)
	{
		for (unsigned short iSphere = 0; iSphere < myRenderSpheres.Size(); ++iSphere)
		{
			myRenderSpheres[iSphere] = GetGameObject().GetComponent<ColliderComponent>(iSphere)->GetCollider().GetBasicSphere();
		}
		myRenderColor = NoCollisionColor;

		if (myHasCollided == true)
		{
			myRenderColor = CollisionColor;

			if (myStopWatch.GetElapsedTime() > 0.1f)
			{
				myHasCollided = false;
			}
		}
		else if (myHasTriggered == true)
		{
			myRenderColor = TriggerColor;

			if (myStopWatch.GetElapsedTime() > 0.1f)
			{
				myHasTriggered = false;
			}
		}
	}

	void RenderColliderComponent::RecieveEvent(const CollisionEvent & aEvent)
	{
		myHasCollided = true;
		myStopWatch.Restart();
	}

	void RenderColliderComponent::RecieveEvent(const TriggerCollisionEvent& aEvent)
	{
		myHasTriggered = true;
		myStopWatch.Restart();
	}

}

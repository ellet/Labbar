#include "stdafx.h"
#include "TestHandleCollisionComponent.h"
#include "Engine\Component\Collider\CollisionEvent.h"
#include "Game\Component\Health\HealthComponent.h"


TestHandleCollisionComponent::TestHandleCollisionComponent()
{
	myHasCollided = true;
}

TestHandleCollisionComponent::~TestHandleCollisionComponent()
{

}

void TestHandleCollisionComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

bool TestHandleCollisionComponent::HasCollided()
{
	if (myHasCollided == true)
	{
		myHasCollided = false;
		return true;
	}

	return false;
}

void TestHandleCollisionComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	myHasCollided = true;
	myObject->SetScale(myObject->GetScale() * 0.9f);
	myObject->GetComponent<HealthComponent>()->RemoveHealth(10.f);
}

void TestHandleCollisionComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	myObject->Remove();
}

void TestHandleCollisionComponent::ToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");
	serializer.StepOut();
	serializer.WriteNode("type", "TestHandleCollisionComponent");
}

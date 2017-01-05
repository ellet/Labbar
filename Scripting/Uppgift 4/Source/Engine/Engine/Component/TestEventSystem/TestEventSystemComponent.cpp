#include "stdafx.h"
#include "TestEventSystemComponent.h"
#include "Engine\GameObject\GameObject.h"
#include "TestEvent.h"


namespace SB
{
	TestEventSystemComponent::TestEventSystemComponent()
	{
	}


	TestEventSystemComponent::~TestEventSystemComponent()
	{
	}

	void TestEventSystemComponent::Initialize()
	{
		myObject->AddEventSubscriber(EventSubscriber<TestEvent>::GetTypeIndex(), EventSubscriber<TestEvent>::GetInstanceIndex());
	}

	void TestEventSystemComponent::RecieveEvent(const TestEvent & aEvent)
	{
		myObject->SetPosition(myObject->GetPosition() + aEvent.myTestPos);
	}

}

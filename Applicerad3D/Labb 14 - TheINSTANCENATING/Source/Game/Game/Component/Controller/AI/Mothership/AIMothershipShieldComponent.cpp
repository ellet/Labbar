#include "stdafx.h"
#include "AIMothershipShieldComponent.h"
#include "Engine\Physics\PhysicsComponent.h"
#include "AIMothershipComponent.h"

AIMothershipShieldComponent::AIMothershipShieldComponent()
{
}


AIMothershipShieldComponent::~AIMothershipShieldComponent()
{
}

void AIMothershipShieldComponent::SetPositionAndRotation(const SB::Vector3f & aPosition, const SB::Quaternion & aRotation)
{
	myPhysicsComponent->SetObjectPosition(aPosition);
	myObject->SetRotation(aRotation);
}

void AIMothershipShieldComponent::Initialize()
{
	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
}

void AIMothershipShieldComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	if (myMothership != nullptr)
	{
		myMothership->ShieldsReportingFailure(myShieldNumber);
		myMothership = nullptr;
	}
}
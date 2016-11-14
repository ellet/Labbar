#include "stdafx.h"
#include "AISwarmerComponent.h"
#include "..\Engine\Engine\Physics\PhysicsComponent.h"
#include "..\Engine\Engine\Physics\CollisionData.h"
#include <Utilities\Math\Quaternion.h>
#include "Engine\Component\Collider\CollisionEvent.h"
#include "..\..\Health\HealthComponent.h"
#include "Engine\Component\Collider\ColliderComponent.h"
#include "Game\Component\Health\ObjectOutOfHealthMessage.h"
#include "Mothership\AIMothershipComponent.h"

AISwarmerComponent::AISwarmerComponent()
{
	myMothership = nullptr;
	myMotherShipSlotNumber = -1;
	mySpeed = 0.f;
}


AISwarmerComponent::~AISwarmerComponent()
{
}

void AISwarmerComponent::Update(const SB::Time & aDeltaTime)
{
	myDistanceSqrdToPlayer = (myPlayer->GetPosition() - myObject->GetPosition()).Length2();
	if (myMothership == nullptr)
	{
		myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myPlayer->GetPosition(), aDeltaTime.InSeconds(), 10.f);
		myVelocityDir = myPlayer->GetPosition() - myObject->GetPosition();
		myVelocityDir.Normalize();
		myPhysicsComponent->SetSpeed(mySpeed);
		myPhysicsComponent->SetForceDirection(myVelocityDir);
	}
	else
	{
		CheckForPlayer();
	}
}

void AISwarmerComponent::Initialize()
{
	SetPlayer(myObject->GetScene().FindObject("Player"));
	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();

	//speed
	//float radius = myObject->GetPosition().Length();
	//mySpeed = (radius * 2.f * M_PIF);

	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::eEnemySwarmer);
	myObject->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(0 | CollisionFilter::ePlayer);
	//myRotationSpeed = (mySpeed / ((myObject->GetPosition() * myObject->GetParent()->GetScale().x).Length() * 2.f * M_PIF)) * 360.f;
	//if (myObject->GetParent() != nullptr)
	//{
	//	if (myUseParentScale == false)
	//	{
	//		const SB::Vector3f& parScale = myObject->GetParent()->GetScale();
	//		const SB::Vector3f& objScale = myObject->GetScale();
	//		myObject->SetScale(SB::Vector3f(objScale.x / parScale.x, objScale.y / parScale.y, objScale.z / parScale.z));
	//	}
	//}
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
	BaseComponent::Initialize();
}

void AISwarmerComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	if (aEvent.myCollisionData->myGameObject->GetIdentifier() == "Player")
	{
		////Add death stuff
		//myPlayer->GetComponent<HealthComponent>()->RemoveHealth(50.f);
		myObject->Remove();
	}
}

void AISwarmerComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	if (myMothership != nullptr)
	{
		myMothership->SwarmerReportingDeathOrLeave(myMotherShipSlotNumber);
		myMothership = nullptr;
	}
}

void AISwarmerComponent::LoadData(SB::DataNode aProperties)
{
	mySpeed = aProperties["rotationSpeed"].GetFloat();
	myUseParentScale = aProperties["useParentScale"].GetBool();

	if (aProperties.HasMember("velocityDirection"))
	{
		myVelocityDir.x = aProperties["velocityDirection"][0].GetFloat();
		myVelocityDir.y = aProperties["velocityDirection"][1].GetFloat();
		myVelocityDir.z = aProperties["velocityDirection"][2].GetFloat();
	}
}

void AISwarmerComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("type", "ModelComponent");
	serializer.WriteObject("properties");
	serializer.WriteNode("useParentScale", myUseParentScale);
	serializer.WriteNode("velocityDirection", myVelocityDir);
	serializer.WriteNode("rotationSpeed", mySpeed);
	serializer.StepOut();
}

void AISwarmerComponent::SetPositionAndRotation(const SB::Vector3f & aPosition, const SB::Quaternion & aRotation)
{
	myPhysicsComponent->SetObjectPosition(aPosition);
	myObject->SetRotation(aRotation);
}
//
//void AISwarmerComponent::SwarmAroundParent(const SB::Time & aDeltaTime)
//{
//	//SB::Vector3f newObjPos(myObject->GetPosition());
//	//SB::Quaternion parRot = myObject->GetRotation();
//
//	//parRot.RotateAroundLocalZ(DEGREES_TO_RADIANSF(myRotationSpeed * aDeltaTime.InSeconds()));
//	//parRot.RotateVector(newObjPos);
//	////float angle = /*RADIANS_TO_DEGREESF*/(SB::Vector3f::GetAngleBetween(oldPos.GetNormalized(), newObjPos.GetNormalized()));
//	//newObjPos = newObjPos * myObject->GetRotation();
//	//myPhysicsComponent->SetObjectPosition(newObjPos);
//}

void AISwarmerComponent::CheckForPlayer()
{
	if (myDistanceSqrdToPlayer <= (100.f * 100.f))
	{
		LeaveMothership();
	}
}

void AISwarmerComponent::LeaveMothership()
{
	if (myMothership != nullptr)
	{
		myMothership->SwarmerReportingDeathOrLeave(myMotherShipSlotNumber);
		myMothership = nullptr;
		mySpeed = 60.f;
	}
}
//
//void AISwarmerComponent::LeaveParent()
//{
//	//const SB::Vector3f& parScale = myObject->GetParent()->GetScale();
//	//const SB::Vector3f& objScale = myObject->GetScale();
//	//myObject->SetScale(SB::Vector3f(objScale.x * parScale.x, objScale.y * parScale.y, objScale.z * parScale.z));
//	//SB::Vector3f samePos = myObject->GetTransformation().GetPosition();//(myObject->GetPosition() * myObject->GetParent()->GetRotation()) + myObject->GetParent()->GetPosition();
//	//myPhysicsComponent->SetObjectPosition(samePos);
//	//myObject->SetRotation(myObject->GetRotation() * myObject->GetParent()->GetRotation());
//	//myObject->SetPosition(samePos);
//	//myObject->SetParent(nullptr);
//
//}

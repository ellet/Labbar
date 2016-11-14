#include "stdafx.h"
#include "AITurretComponent.h"
#include "Game/Component/Shooting/Weapons/WeaponComponent.h"
#include <Engine/Component/Collider/CollisionFilter.h>

AITurretComponent::AITurretComponent()
{
	myMaxRotationDegrees = 5.f;
	myShootingCooldown = 1.2f;
	myCooldownTimer = 0.f;
}

AITurretComponent::~AITurretComponent()
{
}

void AITurretComponent::Update(const SB::Time & aDeltaTime)
{
	if (myObject->GetParent() == nullptr) //We died.
	{
		myObject->Remove();
		return;
	}

	myCooldownTimer -= aDeltaTime;
	LookAtPlayer(aDeltaTime);
}

void AITurretComponent::Initialize()
{
	SetPlayer(myObject->GetScene().FindObject("Player"));


	myWeaponComponent = &*myObject->GetComponent<WeaponComponent>();
	if (myWeaponComponent == nullptr)
	{
		Error("Weapon Component on object " + myObject->GetIdentifier() + " doesn't exist. The AI Turret Component is looking for it.")
	}
	myWeaponComponent->SetUser(myObject);
}

void AITurretComponent::LoadData(SB::DataNode aProperties)
{
	if (aProperties.HasMember("maxRotationDegrees"))
	{
		myMaxRotationDegrees = aProperties["maxRotationDegrees"].GetFloat();
	}
	if (aProperties.HasMember("shootingCooldown"))
	{
		myShootingCooldown = aProperties["shootingCooldown"].GetFloat();
	}
	if (aProperties.HasMember("cooldownTimer"))
	{
		myCooldownTimer = aProperties["cooldownTimer"].GetFloat();
	}
}

void AITurretComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteNode("type", "AITurretComponent");
	serializer.WriteObject("properties");
	serializer.WriteNode("maxRotationDegrees", myMaxRotationDegrees);
	serializer.WriteNode("shootingCooldown", myShootingCooldown.InSeconds());
	serializer.WriteNode("cooldownTimer", myCooldownTimer.InSeconds());
	serializer.StepOut();
}

void AITurretComponent::LookAtPlayer(const SB::Time & aDeltaTime)
{

	SB::Vector3f worldPos = myObject->GetTransformation().GetPosition();
	SB::Vector3f lookAtThisPoint = myPlayer->GetTransformation().GetPosition();
	SB::Vector3f worldPlayerPos = lookAtThisPoint;
	lookAtThisPoint = SB::Vector4f(lookAtThisPoint, 1.f) * myObject->GetTransformationWithoutLocalRotation().GetInverse();

	SB::Vector3f attachedDirectionUpwards = myObject->GetParentWorldRotation().GetUpward();
	SB::Vector3f dirToPlayer = worldPlayerPos - worldPos;

	float angle = RADIANS_TO_DEGREESF(SB::Vector3f::GetAngleBetween(attachedDirectionUpwards, dirToPlayer));
	if (attachedDirectionUpwards.Dot(dirToPlayer) < 0.5f)
	{
		angle = 180 - angle;
	}

	if (angle < 90.f)
	{
		myObject->GetRotation().RotateTowardsPoint(SB::Vector3f::Zero, lookAtThisPoint, aDeltaTime.InSeconds(), myMaxRotationDegrees);
		CheckIfWantToShoot(aDeltaTime);
	}

}

void AITurretComponent::CheckIfWantToShoot(const SB::Time & aDeltaTime)
{
	float magicDetectRangeDegrees = 3.f;

	SB::Vector3f worldPos = myObject->GetTransformation().GetPosition();
	SB::Vector3f dirToPlayer = myPlayer->GetPosition() - worldPos;
	float angleToPlayer;

	angleToPlayer = RADIANS_TO_DEGREESF(SB::Vector3f::GetAngleBetween(myObject->GetWorldRotation().GetForward(), dirToPlayer));
	if (dirToPlayer.z * myObject->GetRotation().GetForward().z < 0)
	{
 		angleToPlayer = 180 - angleToPlayer;
	}

	if (angleToPlayer < magicDetectRangeDegrees)
	{
		Shoot();
	}
}

void AITurretComponent::Shoot()
{
	if (myCooldownTimer < 0.f)
	{
		myWeaponComponent->SetLayerID(static_cast<unsigned int>(CollisionFilter::eEnemy));
		myWeaponComponent->SetCollisonFilters(CollisionFilter::ePlayer | CollisionFilter::eEnvironment);
		myWeaponComponent->FireWeapon(myObject->GetTransformation().GetPosition() + myObject->GetWorldRotation().GetForward() * 10.f, myObject->GetWorldRotation());
		myCooldownTimer = myShootingCooldown;
	}
}

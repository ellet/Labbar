#include "stdafx.h"
#include "HomingWeaponComponent.h"
#include "../Engine/Engine/SoundManager/SoundManager.h"
#include "../Projectiles/HomingShotComponent.h"
#include <Engine/Physics/PhysicsComponent.h>
#include <Engine/Component/Collider/ColliderComponent.h>
#include "../Engine/Engine/Component/Collider/RenderColliderComponent.h"
#include <Engine/Streak/StreakComponent.h>
#include <Engine/Streak/StreakLogic.h>


HomingWeaponComponent::HomingWeaponComponent() : WeaponComponent()
{
}

HomingWeaponComponent::HomingWeaponComponent(const WeaponData& aData) : WeaponComponent(aData)
{
}

HomingWeaponComponent::HomingWeaponComponent(SB::DataNode aProperties) : WeaponComponent(aProperties)
{
	myHomingData.projectileRotationDegreesPerSecond = aProperties["projectileRotationDegreesPerSecond"].GetFloat();
	myHomingData.shotSpeedMax = aProperties["shotSpeedMax"].GetFloat();
	myHomingData.shotTrackingDelay = aProperties["shotTrackingDelay"].GetFloat();
	myHomingData.targetScanRadius = aProperties["targetScanRadius"].GetFloat();
	myHomingData.targetSwitchingCooldown = aProperties["targetSwitchingCooldown"].GetFloat();
}

HomingWeaponComponent::~HomingWeaponComponent()
{
	myUser = nullptr;
}

void HomingWeaponComponent::FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation)
{
	SB::Quaternion shotDirection = GetRandomShotRotation(aWeaponOrientation);

	SB::ObjectPtr shot = CreateProjectile(GetDefaultProjectileIdentifier(), aWeaponPosition, aWeaponOrientation, shotDirection);

	SB::Engine::GetSoundManager().PostEvent(myWeaponData.shootSound.c_str());
}


void HomingWeaponComponent::ToJson()const
{
	WeaponComponent::ToJson();

	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("targetScanRadius", myHomingData.targetScanRadius);
	serializer.WriteNode("shotTrackingDelay", myHomingData.shotTrackingDelay);
	serializer.WriteNode("shotSpeedMax", myHomingData.shotSpeedMax);
	serializer.WriteNode("projectileRotationDegreesPerSecond", myHomingData.projectileRotationDegreesPerSecond);
	serializer.WriteNode("targetSwitchingCooldown", myHomingData.targetSwitchingCooldown);

	EndToJson();
}

SB::ObjectPtr HomingWeaponComponent::CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection)
{
	SB::ObjectPtr shot = myObject->GetScene().CreateObjectWithModel(aIdentifier, myProjectileModel, aPosition, myWeaponData.shotScale, aLaunchDirection);

	shot->CreateComponent<HomingShotComponent>()->SetDamage(myWeaponData.damage);
	shot->GetComponent<HomingShotComponent>()->SetParentShooter(myUser->AsPointer());
	shot->GetComponent<HomingShotComponent>()->SetData(myHomingData);

	SB::ComponentPtr<SB::PhysicsComponent> physicsComponent = shot->CreateComponent<SB::PhysicsComponent>();
	physicsComponent->SetSpeed(myWeaponData.shotSpeed);
	physicsComponent->SetForceDirection(aWeaponOrientation.GetForward());

	shot->CreateComponent<SB::ColliderComponent>()->SetRadius(myWeaponData.shotScale.z / 2.f);
	shot->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(static_cast<CollisionFilter>(myLayerID));
	shot->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(myCollisionFilter);
	shot->GetComponent<SB::ColliderComponent>()->SetIsTrigger();
	shot->CreateComponent<SB::RenderColliderComponent>();
	shot->CreateComponent<SB::StreakComponent>()->Setup(new SB::ConstantStreakProperties(SB::Vector4f::One, 0.71f), 0.1f, 10);
	SpawnShotParticles(shot);

	//Add homing target scan collider
	shot->CreateComponent<SB::ColliderComponent>()->SetRadius(myHomingData.targetScanRadius);
	shot->GetComponent<SB::ColliderComponent>(1)->SetColliderLayerID(static_cast<CollisionFilter>(myLayerID));
	shot->GetComponent<SB::ColliderComponent>(1)->SetCollisionFilter(static_cast<unsigned int>(CollisionFilter::eEnemy)); //Hardcoded to scan for enemies only, change this if we want homing enemy weapons
	shot->GetComponent<SB::ColliderComponent>(1)->SetIsTrigger();

	shot->Initialize();
	return shot;
}

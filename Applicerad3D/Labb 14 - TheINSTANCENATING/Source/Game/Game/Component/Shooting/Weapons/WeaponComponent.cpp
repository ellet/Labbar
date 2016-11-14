#include "stdafx.h"
#include "WeaponComponent.h"
#include <Engine/GameObject/GameObject.h>
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/Model/CubeModel.h"
#include "..\Projectiles\ShotComponent.h"
#include <Engine/Physics/PhysicsComponent.h>
#include <Engine/Component/Collider/ColliderComponent.h>
#include "../Engine/Engine/Component/Collider/RenderColliderComponent.h"
#include <Engine/Streak/StreakComponent.h>
#include <Engine/Streak/StreakLogic.h>
#include <Engine/ParticleSystem/ParticleComponent.h>


WeaponComponent::WeaponComponent()
{
	myWeaponModel = nullptr;
	myProjectileModel = nullptr;
	myUser = nullptr;

	SetData(WeaponData());
}

WeaponComponent::WeaponComponent(const WeaponData& aData)
{
	myWeaponModel = nullptr;
	myProjectileModel = nullptr;
	myUser = nullptr;

	SetData(aData);
}

WeaponComponent::WeaponComponent(SB::DataNode aProperties)
{
	myWeaponModel = nullptr;
	myProjectileModel = nullptr;
	myUser = nullptr;

	LoadData(aProperties);
}

WeaponComponent::~WeaponComponent()
{
	myUser = nullptr;
}


void WeaponComponent::LoadData(SB::DataNode aProperties)
{
	WeaponData data;
	data.damage = aProperties["damage"].GetFloat();
	data.identifier = aProperties["identifier"].GetString();
	data.weaponModelPath = aProperties["weaponModelPath"].GetString();
	data.weaponIconPath = aProperties["weaponIconPath"].GetString();
	data.projectileModelPath = aProperties["projectileModelPath"].GetString();
	data.shootSound = aProperties["shootSound"].GetString();
	data.shotCooldown = aProperties["shotCooldown"].GetFloat();
	data.barrelOffset = SB::Vector3f(aProperties["barrelOffset"][0].GetFloat(), aProperties["barrelOffset"][1].GetFloat(), aProperties["barrelOffset"][2].GetFloat());
	data.shotScale = SB::Vector3f(aProperties["shotScale"][0].GetFloat(), aProperties["shotScale"][1].GetFloat(), aProperties["shotScale"][2].GetFloat());
	data.shotSpeed = aProperties["shotSpeed"].GetFloat();

	if (aProperties.HasMember("impactSound") == true)
		data.impactSound = aProperties["impactSound"].GetString();
	else
		data.impactSound = "";

	if (aProperties.HasMember("impactEffects") == true)
	{
		for(unsigned short i = 0; i < aProperties["impactEffects"].Capacity(); ++i)
		{			
			data.impactEffects.Add(aProperties["impactEffects"][i].GetString());
		}
	}

	if (aProperties.HasMember("muzzleFlashModelPath") == true)
		data.muzzleFlashModelPath = aProperties["muzzleFlashModelPath"].GetString();
	else
		data.muzzleFlashModelPath = "";

	if (aProperties.HasMember("shootEffect") == true)
		data.shootEffect = aProperties["shootEffect"].GetString();
	else
		data.shootEffect = "";

	if (aProperties.HasMember("firingRotationVelocityMax") == true)
		data.firingRotationVelocityMax = aProperties["firingRotationVelocityMax"].GetFloat();
	else
		data.firingRotationVelocityMax = 0.f;

	if (aProperties.HasMember("firingRotationVelocityAccelerationTime") == true)
		data.firingRotationVelocityAccelerationTime = aProperties["firingRotationVelocityAccelerationTime"].GetFloat();
	else
		data.firingRotationVelocityAccelerationTime = 0.f;

	if (aProperties.HasMember("overheatDuration") == true)
		data.overheatDuration = aProperties["overheatDuration"].GetFloat();
	else
		data.overheatDuration = 0.f;

	if (aProperties.HasMember("overheatPerShot") == true)
		data.overheatPerShot = aProperties["overheatPerShot"].GetUShort();
	else
		data.overheatPerShot = 0;

	if (aProperties.HasMember("isOwned") == true)
		data.isOwned = aProperties["isOwned"].GetBool();
	else
		data.isOwned = true;

	SetData(data);
}

void WeaponComponent::ToJson()const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteObject("properties");

	serializer.WriteNode("identifier", myWeaponData.identifier);
	serializer.WriteNode("weaponModelPath", myWeaponData.weaponModelPath);
	serializer.WriteNode("projectileModelPath", myWeaponData.projectileModelPath);
	serializer.WriteNode("muzzleFlashModelPath", myWeaponData.muzzleFlashModelPath);
	serializer.WriteNode("weaponIconPath", myWeaponData.weaponIconPath);
	serializer.WriteNode("shootSound", myWeaponData.shootSound);
	serializer.WriteNode("impactSound", myWeaponData.impactSound);
	serializer.WriteNode("shootEffect", myWeaponData.shootEffect);

	serializer.WriteArray("impactEffects");
	for (unsigned short i = 0; i < myWeaponData.impactEffects.Size(); ++i)
	{
		//serializer.WriteObject();
		serializer.WriteArrayValue(myWeaponData.impactEffects[i]);
		//serializer.StepOut();
	}
	serializer.StepOut();

	serializer.WriteNode("shotScale", myWeaponData.shotScale);
	serializer.WriteNode("barrelOffset", myWeaponData.barrelOffset);
	serializer.WriteNode("shotCooldown", myWeaponData.shotCooldown);
	serializer.WriteNode("damage", myWeaponData.damage);
	serializer.WriteNode("shotSpeed", myWeaponData.shotSpeed);
	serializer.WriteNode("firingRotationVelocityMax", myWeaponData.firingRotationVelocityMax);
	serializer.WriteNode("firingRotationVelocityAccelerationTime", myWeaponData.firingRotationVelocityAccelerationTime.InSeconds());
	serializer.WriteNode("overheatDuration", myWeaponData.overheatDuration.InSeconds());
	serializer.WriteNode("overheatPerShot", myWeaponData.overheatPerShot);
	serializer.WriteNode("isOwned", myWeaponData.isOwned);
	serializer.WriteNode("firingType", myWeaponData.firingType);

	EndToJson();
}

void WeaponComponent::FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation)
{
	SB::Quaternion shotDirection = GetRandomShotRotation(aWeaponOrientation);

	/*SB::Matrix44f barrelMatrix;
	barrelMatrix.SetPosition(myBarrelOffset);
	SB::Matrix44f weaponMatrix = SB::Matrix44f::CreateScale(myObject->GetScale().x, myObject->GetScale().y, myObject->GetScale().z) * myObject->GetRotation().GenerateMatrix() * SB::Matrix44f::CreateTranslation(aWeaponPosition);*/

	SB::ObjectPtr shot = CreateProjectile(GetDefaultProjectileIdentifier(), aWeaponPosition, aWeaponOrientation, shotDirection);

}


//PRIVATE FUNCTIONS:

void WeaponComponent::SetData(const WeaponData& aData)
{
	myWeaponData = aData;

	//Set weapon & projectile models
	if (myWeaponData.weaponModelPath != "")
		myWeaponModel = SB::Engine::GetResourceManager().Get<SB::AssimpModel>(myWeaponData.weaponModelPath);
	else
		myWeaponModel = nullptr;

	if (myWeaponData.projectileModelPath != "")
		myProjectileModel = SB::Engine::GetResourceManager().Get<SB::AssimpModel>(myWeaponData.projectileModelPath);
	else
		myProjectileModel = std::make_shared<SB::CubeModel>(nullptr);

	//Set muzzle flash model
	if (myWeaponData.muzzleFlashModelPath != "")
		myMuzzleFlashModel = SB::Engine::GetResourceManager().Get<SB::AssimpModel>(myWeaponData.muzzleFlashModelPath);
	else
		myMuzzleFlashModel = nullptr;
}

SB::ObjectPtr WeaponComponent::CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection)
{
	SB::ObjectPtr shot = myObject->GetScene().CreateObjectWithModel(aIdentifier, myProjectileModel, aPosition, myWeaponData.shotScale, aLaunchDirection);

	shot->CreateComponent<ShotComponent>()->SetDamage(myWeaponData.damage);

 	shot->GetComponent<ShotComponent>()->SetParentShooter(myUser->AsPointer());

	SB::ComponentPtr<SB::PhysicsComponent> physicsComponent = shot->CreateComponent<SB::PhysicsComponent>();
	physicsComponent->SetSpeed(myWeaponData.shotSpeed);
	physicsComponent->SetForceDirection(aWeaponOrientation.GetForward());

	shot->CreateComponent<SB::ColliderComponent>()->SetRadius(myWeaponData.shotScale.z / 2.f);
	shot->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(static_cast<CollisionFilter>(myLayerID));
	shot->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(myCollisionFilter);
	shot->GetComponent<SB::ColliderComponent>()->SetIsTrigger();
	shot->CreateComponent<SB::RenderColliderComponent>();
	shot->CreateComponent<SB::StreakComponent>()->Setup(new SB::ConstantStreakProperties(SB::Vector4f::One, 0.01f), 0.025f, 10);

	SpawnShotParticles(shot);


	shot->Initialize();
	return shot;
}

std::string WeaponComponent::GetDefaultProjectileIdentifier() const
{
	std::string shotName = myObject->GetIdentifier();
	shotName += "_Projectile_";
	shotName += myWeaponData.identifier;
	return shotName;
}

SB::Quaternion WeaponComponent::GetRandomShotRotation(const SB::Quaternion& aWeaponOrientation)
{
	SB::Quaternion shotDirection = aWeaponOrientation;
	//shotDirection.RotateAroundLocalX(myRandomizer.GetRandomValue(-0.02f, 0.02f));
	//shotDirection.RotateAroundLocalY(myRandomizer.GetRandomValue(-0.02f, 0.02f));
	shotDirection.RotateAroundLocalZ(DEGREES_TO_RADIANSF(myRandomizer.GetRandomValue(-180.f, 180.f)));
	return shotDirection;
}

void WeaponComponent::SpawnShotParticles(SB::ObjectPtr aShot)
{
	if (myWeaponData.shootEffect != "")
	{
		SB::ComponentPtr<SB::ParticleComponent> particles = aShot->CreateComponent<SB::ParticleComponent>();
		particles->SetEmitter(myWeaponData.shootEffect, false);
	}	
}

//Step out of the properties node and end the weapon component entry
void WeaponComponent::EndToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();

	serializer.StepOut();

	serializer.WriteNode("type", "WeaponComponent");
}


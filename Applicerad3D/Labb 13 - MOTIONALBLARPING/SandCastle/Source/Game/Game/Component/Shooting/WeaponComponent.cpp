#include "stdafx.h"
#include "WeaponComponent.h"
#include <Engine/GameObject/GameObject.h>
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/Model/CubeModel.h"
#include "ShotComponent.h"
#include <Engine/Physics/PhysicsComponent.h>
#include <Engine/Component/Collider/ColliderComponent.h>
#include "../Engine/Engine/Component/Collider/RenderColliderComponent.h"
#include <Engine/Streak/StreakComponent.h>
#include <Engine/ParticleSystem/ParticleComponent.h>
#include "../Engine/Engine/SoundManager/SoundManger.h"


WeaponComponent::WeaponComponent()
{
	myWeaponModel = nullptr;
	myProjectileModel = nullptr;

	SetData(WeaponData());
}

WeaponComponent::WeaponComponent(const WeaponData& aData)
{
	myWeaponModel = nullptr;
	myProjectileModel = nullptr;

	SetData(aData);
}

WeaponComponent::~WeaponComponent()
{
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

	SetData(data);
}

void WeaponComponent::FireWeapon(const SB::Vector3f& aWeaponPosition, const SB::Quaternion& aWeaponOrientation)
{

	std::string id = myIdentifier;
	const SB::Vector3f& objPos = myObject->GetTransformation().GetPosition();
	SB::Quaternion shotDirection = aWeaponOrientation;
	//shotDirection.RotateAroundLocalX(myRandomizer.GetRandomValue(-0.02f, 0.02f));
	//shotDirection.RotateAroundLocalY(myRandomizer.GetRandomValue(-0.02f, 0.02f));

	SB::ObjectPtr shot = CreateProjectile(GetDefaultProjectileIdentifier(), aWeaponPosition + myBarrelOffset, aWeaponOrientation, shotDirection);

	SB::Engine::GetSoundManager().PostEvent(myShootSound.c_str());
}


//PRIVATE FUNCTIONS:

void WeaponComponent::SetData(const WeaponData& aData)
{
	myDamage = aData.damage;
	myIdentifier = aData.identifier;
	myShootSound = aData.shootSound;
	myShotCooldown = aData.shotCooldown;
	myBarrelOffset = aData.barrelOffset;
	myShotScale = aData.shotScale;
	myShotSpeed = aData.shotSpeed;

	myWeaponModelPath = aData.weaponModelPath;
	myWeaponIconPath = aData.weaponIconPath;
	myProjectileModelPath = aData.projectileModelPath;

	//Set weapon & projectile models
	if (myWeaponModelPath != "")
		myWeaponModel = SB::Engine::GetResourceManager().Get<SB::AssimpModel>(myWeaponModelPath);
	else
		myWeaponModel = nullptr;

	if (myProjectileModelPath != "")
		myProjectileModel = SB::Engine::GetResourceManager().Get<SB::AssimpModel>(myProjectileModelPath);
	else
		myProjectileModel = std::make_shared<SB::CubeModel>(nullptr);
}

SB::ObjectPtr WeaponComponent::CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection)
{
	SB::ObjectPtr shot = myObject->GetScene().CreateObjectWithModel(aIdentifier, myProjectileModel, aPosition, myShotScale, aLaunchDirection);

	shot->CreateComponent<ShotComponent>()->SetDamage(myDamage);

	SB::ComponentPtr<SB::PhysicsComponent> physicsComponent = shot->CreateComponent<SB::PhysicsComponent>();
	physicsComponent->SetSpeed(myShotSpeed);
	physicsComponent->SetForceDirection(aWeaponOrientation.GetForward());

	shot->CreateComponent<SB::ColliderComponent>()->SetRadius(myShotScale.z / 2.f);
	shot->GetComponent<SB::ColliderComponent>()->SetColliderLayedID(static_cast<CollisionFilter>(myLayerID));
	shot->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(myCollisionFilter);
	shot->CreateComponent<SB::RenderColliderComponent>();
	shot->CreateComponent<SB::StreakComponent>()->Setup(SB::Vector4f::One, 0.01f, 1.0f, 6);
	HardCodedShotParticlesToRemoveAfterCheckup(shot);

	shot->Initialize();
	return shot;
}

std::string WeaponComponent::GetDefaultProjectileIdentifier() const
{
	std::string shotName = "PlayerShot_";
	shotName += myIdentifier;
	return shotName;
}

void WeaponComponent::HardCodedShotParticlesToRemoveAfterCheckup(SB::ObjectPtr aShot)
{
	SB::ComponentPtr<SB::ParticleComponent> particleees = aShot->CreateComponent<SB::ParticleComponent>();

	SB::ParticleSettings tempSettings;

	tempSettings.myAmountOfParticles = 100;
	tempSettings.myStartColor = SB::Vector4f::One;
	tempSettings.myEndColor = SB::Vector4f::One;
	tempSettings.myMinMaxVelocityX = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxVelocityY = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxVelocityZ = SB::Vector2f(-1.f, 1.f);
	tempSettings.myMinMaxLifeTime = SB::Vector2f(5.f, 5.f);
	tempSettings.myMinMaxSize = SB::Vector2f(0.01f, 0.1f);
	tempSettings.myEndSizeInPercent = 0.1f;
	tempSettings.myEmitCoolDown = 0.02f;

	tempSettings.myStartColor.x = 1.f;
	tempSettings.myStartColor.y = 0.f;
	tempSettings.myStartColor.z = 0.f;
	tempSettings.myStartColor.w = 1.f;

	tempSettings.myEndColor.x = 1.f;
	tempSettings.myEndColor.y = 1.f;
	tempSettings.myEndColor.z = 0.f;
	tempSettings.myEndColor.w = 1.f;

	particleees->SetSettings(tempSettings);
}



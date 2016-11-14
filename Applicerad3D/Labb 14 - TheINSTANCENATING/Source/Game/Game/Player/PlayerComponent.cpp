#include "stdafx.h"
#include "PlayerComponent.h"
#include "Engine/Component/Collider/CollisionEvent.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Physics/CollisionData.h"
#include "Engine/ParticleSystem/ParticleComponent.h"
#include "Game/Component/Health/HealthComponent.h"
#include "Game/Component/Shooting/Projectiles/ShotComponent.h"
#include "Game/Component/Health/ObjectOutOfHealthMessage.h"
#include "Game/Player/PlayerMessages.h"
#include "PlayerShootComponent.h"
#include <Engine/Physics/PhysicsComponent.h>
#include "Engine/Camera/CameraShakeMessage.h"
#include "Engine/Component/Collider/TriggerCollisionEvent.h"
#include "Game/Game.h"
#include "../Engine/Engine/GUI/GUIElement.h"
#include "../Engine/Engine/GUI/GUIMarker.h"
#include <Engine/Scene/Scene.h>
#include <Engine/Camera/Camera.h>
#include "../Engine/Engine/Component/ComponentPtr.h"
#include "PlayerControllerComponent.h"
#include "Engine/Component/Collider/ColliderComponent.h"
#include "Engine/CollisionHandling/ColliderData.h"



bool PlayerComponent::ourGodMode = false;

PlayerComponent::PlayerComponent()
{
	myRespawnTimer = 0.f;
	myHealthRecoveryTimer = 0.f;
	myHealthRecoveryPerSecond = 0.f;
	myRespawnCooldown = 0.f;
	myCollisionCooldown = 0.f;
	myCanCollide = true;
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Initialize()
{
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::CollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::CollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<SB::TriggerCollisionEvent>::GetTypeIndex(), SB::EventSubscriber<SB::TriggerCollisionEvent>::GetInstanceIndex());
	myObject->AddEventSubscriber(SB::EventSubscriber<ObjectOutOfHealthMessage>::GetTypeIndex(), SB::EventSubscriber<ObjectOutOfHealthMessage>::GetInstanceIndex());
	SendPlayerData();
	SB::PostMaster::Post<PlayerHealthChangedMessage>(PlayerHealthChangedMessage(myObject->GetComponent<HealthComponent>()->GetCurrentHealth()));

	myGUIMarker = std::make_shared<SB::GUIMarker>("Assets/Gui/Markers/injuredMarker.dds", SB::Vector2f::Zero);
	myGUIMarker->SetActive(false);
	myGUIMarker->SetName("InjuredMarker");
	myGUIMarker->SetOrigin(SB::Vector2f(0.f, 90.f));
	myObject->GetScene().GetGUI()->GetGUIElement("MarkerRadar")->AddChild(myGUIMarker);
	myGUIMarker->CenterMe();
}

void PlayerComponent::Update(const SB::Time& aDeltaTime)
{
	UpdateHealthRecovery(aDeltaTime);
	UpdateRespawnCounter(aDeltaTime);

	if (myGUIMarker->GetActive() == true)
	{
		myMarkerTimer += aDeltaTime.InSeconds();
		myGUIMarker->SpecialUpdate();
		if (myGUIMarker->GetIsInside() == true)
		{
			myGUIMarker->SetSprite("Assets/Gui/Markers/radarDamaged.dds");
		}
		else
		{
			myGUIMarker->SetSprite("Assets/Gui/Markers/injuredMarker.dds");
		}

		if (myMarkerTimer >= 2.f)
		{
			myGUIMarker->SetActive(false);
			myMarkerTimer = 0;
		}
	}

	myCollisionCooldown += aDeltaTime.InSeconds();

	if (myCollisionCooldown.InSeconds() >= 1.f)
	{
		myCanCollide = true;
	}
}

void PlayerComponent::LoadData(SB::DataNode aProperties)
{
	if (aProperties.HasMember("respawnCooldown") == true)
		myRespawnCooldown = aProperties["respawnCooldown"].GetFloat();
	else
		myRespawnCooldown = 3.f;

	if (aProperties.HasMember("healthRecoveryPerSecond") == true)
		myHealthRecoveryPerSecond = aProperties["healthRecoveryPerSecond"].GetFloat();
	else
		myHealthRecoveryPerSecond = 5.f;

	if (aProperties.HasMember("healthRecoveryCooldown") == true)
		myHealthRecoveryCooldown = aProperties["healthRecoveryCooldown"].GetFloat();
	else
		myHealthRecoveryCooldown = 5.f;


	SB::DataDocument doc;
	SB::Data::Open("Assets/Data/Player/player.json", doc);
	myCShakePlayerCollision = doc["cShakePlayerCollision"].GetFloat();
	myCShakePlayerShotDamage = doc["cShakePlayerShotDamage"].GetFloat();
}

void PlayerComponent::ToJson()const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");

	serializer.WriteNode("respawnCooldown", myRespawnCooldown);
	serializer.WriteNode("healthRecoveryPerSecond", myHealthRecoveryPerSecond);
	serializer.WriteNode("healthRecoveryCooldown", myHealthRecoveryCooldown);

	serializer.StepOut();
	serializer.WriteNode("type", "PlayerComponent");
}


//PRIVATE FUNCTIONS:

void PlayerComponent::UpdateHealthRecovery(const SB::Time& aDeltaTime)
{
	SB::ComponentPtr<HealthComponent> healthComponent = myObject->GetComponent<HealthComponent>();

	if (healthComponent->GetIsDead() == true)
	{
		return;
	}


	if (myHealthRecoveryTimer > 0.f)
	{
		myHealthRecoveryTimer -= aDeltaTime.InSeconds();

		if (myHealthRecoveryTimer < 0.f)
		{
			myHealthRecoveryTimer = 0.f;
		}
	}
	else if (healthComponent->GetCurrentHealth() < healthComponent->GetMaxHealth())
	{
		float healAmount = myHealthRecoveryPerSecond * aDeltaTime.InSeconds();
		healthComponent->AddHealth(healAmount);
	}
}

void PlayerComponent::UpdateRespawnCounter(const SB::Time& aDeltaTime)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		myRespawnTimer += aDeltaTime.InSeconds();

		if (myRespawnTimer >= myRespawnCooldown)
		{
			Respawn();
		}
	}
}

void PlayerComponent::SendPlayerData()
{
	SavedPlayerData tempData = Game::GetInstance().GetPlayerSavedData();
	myObject->GetComponent<HealthComponent>()->SetHealth(tempData.myHealth);
	SB::PostMaster::Post<PlayerHealthChangedMessage>(tempData.myHealth);
	myObject->GetComponent<PlayerShootComponent>()->SetIsWeaponOwned(tempData.myOwnedPrimaryWeapons, ePlayerWeaponType::ePrimary);
	myObject->GetComponent<PlayerShootComponent>()->SetIsWeaponOwned(tempData.myOwnedSecondaryWeapons, ePlayerWeaponType::eSecondary);
}

void PlayerComponent::Respawn()
{
	//Load last checkpoint

	myRespawnTimer = 0.f;
	myHealthRecoveryTimer = 0.f;
	myObject->GetComponent<SB::PhysicsComponent>()->SetObjectPosition(Game::GetInstance().GetPlayerSavedData().myStartPosition);
	SendPlayerData();

	myObject->GetComponent<PlayerControllerComponent>()->LoadSave();
}

void PlayerComponent::RecieveEvent(const ObjectOutOfHealthMessage & aEvent)
{
	myRespawnTimer = 0.f;
	myHealthRecoveryTimer = 0.f;
	Game::GetInstance().GetPlayerSavedData().myHealth = 100.f;
}

void PlayerComponent::RecieveEvent(const SB::CollisionEvent & aEvent)
{
	if (ourGodMode == false)
	{
		//Player collision with objects in the world.
		if (myCanCollide == true)
		{
			SB::Vector3f objectPosition = aEvent.myCollisionData->myGameObject->GetWorldPosition();

			CalculateDamageTakenDirection(objectPosition);

			float damageTaken = pow(1.1f, (aEvent.myCollisionData->mySpeed - 1));
			if (aEvent.myCollisionData->mySpeed > 5.f)
			{
				myObject->GetComponent<HealthComponent>()->RemoveHealth(damageTaken);
				SB::PostMaster::Post(SB::CameraShakeMessage(myCShakePlayerCollision, 1.f));
			}
			myCanCollide = false;
			myCollisionCooldown = 0.f;

			const SB::ColliderComponent* colliderCmpntPtr = &*aEvent.myCollisionData->myGameObject->GetComponent<SB::ColliderComponent>(aEvent.myCollisionData->myColliderIndex);
			if (colliderCmpntPtr != nullptr)
			{
				if (*colliderCmpntPtr->GetColliderData().myLayerID == static_cast<unsigned int>(CollisionFilter::eEnemySwarmer))
				{
					myObject->GetComponent<HealthComponent>()->RemoveHealth(50.f);
				}

			}
		}

	}
}

void PlayerComponent::RecieveEvent(const SB::TriggerCollisionEvent & aEvent)
{
	if (ourGodMode == true)
	{
		return;
	}
	SB::ComponentPtr<const ShotComponent> shotComponent = aEvent.myGameObject->GetComponent<ShotComponent>();
	if (shotComponent == nullptr)
	{
		return;
	}
	if (shotComponent->GetParentShooter() == nullptr)
	{
		return;
	}

	/*if (shotComponent->GetParentShooter()->GetParent() == nullptr)
	{
		return;
	}*/

	SB::Vector3f shooterPosition = shotComponent->GetParentShooter()->GetWorldPosition();
	CalculateDamageTakenDirection(shooterPosition);

	const float Damage = shotComponent->GetDamage();
	myObject->GetComponent<HealthComponent>()->RemoveHealth(Damage);
	SB::PostMaster::Post<PlayerHealthChangedMessage>(PlayerHealthChangedMessage(myObject->GetComponent<HealthComponent>()->GetCurrentHealth()));
	SB::PostMaster::Post(SB::CameraShakeMessage(myCShakePlayerShotDamage, 1.f));
}

void PlayerComponent::CalculateDamageTakenDirection(const SB::Vector3f & aObjectPosition)
{
	myGUIMarker->SetTargetPosition(GetScreenPosition(aObjectPosition));
	SB::Vector2f direction = GetScreenPosition(aObjectPosition) - myGUIMarker->GetPosition();
	float signedDirection = myObject->GetScene().GetCamera().GetOrientation().GetForward().Dot(aObjectPosition - myObject->GetScene().GetCamera().GetTransformation().GetPosition());
	myGUIMarker->SetDirection(signedDirection);

	if (signedDirection < 0.f)
	{
		myGUIMarker->SetRotation(atan2(-direction.y, -direction.x));
	}
	else
	{
		myGUIMarker->SetRotation(atan2(direction.y, direction.x));
	}
}

SB::ReceiveResult PlayerComponent::Receive(const SetPlayerDataMessage& aMessage)
{
	Game::GetInstance().GetPlayerSavedData() = aMessage.mySavedData;
	SendPlayerData();
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerComponent::Receive(const OnSceneExitMessage& aMessage)
{
	Game::GetInstance().GetPlayerSavedData() = aMessage.mySavedData;

	//Use this if we want to save data between levels.
	/*Game::GetInstance().GetPlayerSavedData().myHealth = myObject->GetComponent<HealthComponent>()->GetCurrentHealth();
	Game::GetInstance().GetPlayerSavedData().myOwnedPrimaryWeapons = myObject->GetComponent<PlayerShootComponent>()->GetOwnedWeapons(ePlayerWeaponType::ePrimary);
	Game::GetInstance().GetPlayerSavedData().myOwnedSecondaryWeapons = myObject->GetComponent<PlayerShootComponent>()->GetOwnedWeapons(ePlayerWeaponType::eSecondary);*/

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerComponent::Receive(const PlayerTakenDamageMessage& aMessage)
{
	myHealthRecoveryTimer = myHealthRecoveryCooldown;

	myGUIMarker->SetActive(true);

	return SB::ReceiveResult::eContinue;
}

const SB::Vector2f PlayerComponent::GetScreenPosition(const SB::Vector3f & aPosition) const
{
	SB::Vector2f pos = myObject->GetScene().GetCamera().WorldToScreen(aPosition);
	pos += SB::Vector2f::One;
	pos /= 2.f;
	pos.y = 1.f - pos.y;
	pos *= SB::Vector2f(1280.f, 720.f);
	return pos;
}

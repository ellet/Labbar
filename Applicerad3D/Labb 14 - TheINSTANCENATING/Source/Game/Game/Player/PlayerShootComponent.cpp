#include "stdafx.h"
#include "PlayerShootComponent.h"
#include <Engine/GameObject/GameObject.h>
#include "Engine/SoundManager/SoundManager.h"
#include "Engine/Component/Collider/CollisionFilter.h"
#include "Game/Component/Shooting/Weapons/WeaponComponent.h"
#include "Game/Component/Shooting/Weapons/HomingWeaponComponent.h"
#include "Game/Component/Shooting/Weapons/BeamWeaponComponent.h"
#include "Game/Player/WeaponMount.h"
#include "../Component/Health/HealthComponent.h"


void PlayerShootComponent::Initialize()
{
	myLeftKeySubscription = std::make_shared<SB::Subscription<SB::LeftMouseButtonDownMessage>>(
		[this] (const SB::LeftMouseButtonDownMessage& aMessage) -> SB::ReceiveResult
		{
			return this->Receive(aMessage);
		}
	);
	myLeftKeyUpSubscription = std::make_shared<SB::Subscription<SB::LeftMouseButtonUpMessage>>(
		[this](const SB::LeftMouseButtonUpMessage& aMessage) -> SB::ReceiveResult
		{
			return this->Receive(aMessage);
		}
	);
	myRightKeySubscription = std::make_shared<SB::Subscription<SB::RightMouseButtonDownMessage>>(
		[this](const SB::RightMouseButtonDownMessage& aMessage) -> SB::ReceiveResult
	{
		return this->Receive(aMessage);
	}
	);
	myRightKeyUpSubscription = std::make_shared<SB::Subscription<SB::RightMouseButtonUpMessage>>(
		[this](const SB::RightMouseButtonUpMessage& aMessage) -> SB::ReceiveResult
	{
		return this->Receive(aMessage);
	}
	);

	myShotCounter = 0;

	SetWeaponUser();
	CreateWeaponNodes();
	InitWeapons();
}

void PlayerShootComponent::OnRemoved()
{
	myWeaponRoot = nullptr;

	for (unsigned short i=0; i<myWeaponMounts.Size(); i++)
	{
		myWeaponMounts[i]->OnRemoved();
	}
}

PlayerShootComponent::~PlayerShootComponent()
{
	myLeftKeySubscription = nullptr;
	myLeftKeyUpSubscription = nullptr;
	myRightKeySubscription = nullptr;
	myRightKeyUpSubscription = nullptr;
}


void PlayerShootComponent::LoadData(SB::DataNode aProperties)
{
	//Don't use the aProperties node in this case, we'll open a separate document for weapon data
	LoadWeapons();
}

void PlayerShootComponent::Update(const SB::Time& aDeltaTime)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		Reset();
	}

	UpdateWeaponMounts(aDeltaTime);
}

void PlayerShootComponent::EquipWeapon(const ePlayerWeaponType aWeaponType, const std::string& aWeaponIdentifier)
{
	myWeaponMounts[static_cast<unsigned short>(aWeaponType)]->EquipWeapon(aWeaponIdentifier);
}

void PlayerShootComponent::EquipWeapon(const ePlayerWeaponType aWeaponType, const unsigned short aWeaponIndex)
{
	EquipWeapon(aWeaponType, myWeaponMounts[static_cast<unsigned short>(aWeaponType)]->GetWeaponIdentifierAtIndex(aWeaponIndex));
}


SB::ReceiveResult PlayerShootComponent::Receive(const SB::LeftMouseButtonDownMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}

	myWeaponMounts[static_cast<unsigned short>(ePlayerWeaponType::ePrimary)]->SetIsFiring(true);
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::LeftMouseButtonUpMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}


	myWeaponMounts[static_cast<unsigned short>(ePlayerWeaponType::ePrimary)]->SetIsFiring(false);
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::RightMouseButtonDownMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}

	myWeaponMounts[static_cast<unsigned short>(ePlayerWeaponType::eSecondary)]->SetIsFiring(true);
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::RightMouseButtonUpMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}

	myWeaponMounts[static_cast<unsigned short>(ePlayerWeaponType::eSecondary)]->SetIsFiring(false);
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::AnyKeyDownMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}

	switch (aMessage.key)
	{
	case SB::KeyboardKey::eNum1:
		EquipWeapon(ePlayerWeaponType::ePrimary, "Gatling Gun");
		break;
	case SB::KeyboardKey::eNum2:
		EquipWeapon(ePlayerWeaponType::ePrimary, "Blaster");
		break;
	case SB::KeyboardKey::eNum3:
		EquipWeapon(ePlayerWeaponType::eSecondary, "Rocket Launcher");
		break;
	case SB::KeyboardKey::eNum4:
		EquipWeapon(ePlayerWeaponType::eSecondary, "Railgun");
		break;
	}
	return SB::ReceiveResult::eContinue;
}

void PlayerShootComponent::SetIsWeaponOwned(const SB::GrowingArray<bool> aOwnedFlags, const ePlayerWeaponType aWeaponType)
{
	if (aWeaponType == ePlayerWeaponType::ePrimary)
	{
		assert(aOwnedFlags.Size() == myPrimaryWeapons.Size() && "Ownership flags on Primary Weapons mismatched list sizes");
		for (unsigned short i = 0; i < aOwnedFlags.Size(); ++i)
		{
			myPrimaryWeapons[i]->SetIsOwned(aOwnedFlags[i]);
		}
	}
	else
	{
		assert(aOwnedFlags.Size() == mySecondaryWeapons.Size() && "Ownership flags on Secondary Weapons mismatched list sizes");
		for (unsigned short i = 0; i < aOwnedFlags.Size(); ++i)
		{
			mySecondaryWeapons[i]->SetIsOwned(aOwnedFlags[i]);
		}
	}
}

SB::GrowingArray<bool> PlayerShootComponent::GetOwnedWeapons(const ePlayerWeaponType aWeaponType)
{
	SB::GrowingArray<bool> tempBools;
	if (aWeaponType == ePlayerWeaponType::ePrimary)
	{
		for (unsigned short i = 0; i < myPrimaryWeapons.Size(); i++)
		{
			tempBools.Add(myPrimaryWeapons[i]->GetIsOwned());
		}
	}
	else
	{
		for (unsigned short i = 0; i < mySecondaryWeapons.Size(); i++)
		{
			tempBools.Add(mySecondaryWeapons[i]->GetIsOwned());
		}
	}
	return tempBools;
	
}

int PlayerShootComponent::GetTimesFired() const
{
	return myShotCounter;
}


void PlayerShootComponent::ToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");
	serializer.StepOut();
	serializer.WriteNode("type", "PlayerShootComponent");
}

//PRIVATE FUNCTIONS:

void PlayerShootComponent::Reset()
{
	for (unsigned short i = 0; i < myWeaponMounts.Size(); i++)
	{
		myWeaponMounts[i]->Reset();
	}
}

//Load the list of all weapons from dedicated json document
void PlayerShootComponent::LoadWeapons()
{
	SB::DataDocument doc;
	SB::Data::Open("Assets/Data/Weapons/weapons.json", doc);

	//Load primary weapons
	for (unsigned short i = 0; i < doc["primaryWeapons"].Capacity(); ++i)
	{
		myPrimaryWeapons.Add(LoadWeapon(doc["primaryWeapons"][i]));
		myPrimaryWeapons.GetLast()->SetLayerID(static_cast<unsigned int>(CollisionFilter::ePlayer));
		myPrimaryWeapons.GetLast()->SetCollisonFilters(CollisionFilter::eEnemy | CollisionFilter::eEnemySwarmer | CollisionFilter::eEnvironment);
	}

	//Load secondary weapons
	for (unsigned short i = 0; i < doc["secondaryWeapons"].Capacity(); ++i)
	{
		mySecondaryWeapons.Add(LoadWeapon(doc["secondaryWeapons"][i]));
		mySecondaryWeapons.GetLast()->SetLayerID(static_cast<unsigned int>(CollisionFilter::ePlayer));
		mySecondaryWeapons.GetLast()->SetCollisonFilters(CollisionFilter::eEnemy | CollisionFilter::eEnemySwarmer | CollisionFilter::eEnvironment);
	}
}

std::shared_ptr<WeaponComponent> PlayerShootComponent::LoadWeapon(SB::DataNode aWeaponData)
{
	eFiringType firingType = static_cast<eFiringType>(aWeaponData["firingType"].GetUShort());

	switch (firingType)
	{
	case eFiringType::eStandard:
		return std::make_shared<WeaponComponent>(aWeaponData);
		break;
	case eFiringType::eHoming:
		return std::make_shared<HomingWeaponComponent>(aWeaponData);
		break;
	case eFiringType::eBeam:
		return std::make_shared<BeamWeaponComponent>(aWeaponData);
		break;
	default:
		Error("PlayerShootComponent::LoadWeapon attempted to load Weapon of unknown firing type");
		break;
	}
}

//Create the hierarchy of nodes which weapons are then attached to
void PlayerShootComponent::CreateWeaponNodes()
{
	//Create the weapon root object, which we will use to "mount" our equipped weapons onto (as offset children)
	SB::ObjectPtr owner = myObject->AsPointer();
	myWeaponRoot = myObject->GetScene().CreateGameObject("Player_WeaponRoot");
	myWeaponRoot->SetParent(owner);
	myWeaponRoot->SetPosition(SB::Vector3f::Zero);
	//myWeaponRoot->SetRotation(myWeaponRoot->GetParent()->GetRotation());
	//TODO: Add model component to root here

	//Create (local) positions for each weapon node which will become their offsets from the parent Weapon Root object
	SB::GrowingArray<SB::Vector3f> primaryNodePositions;
	SB::GrowingArray<SB::Vector3f> secondaryNodePositions;
	primaryNodePositions.Add(SB::Vector3f(0.96807f, 0.50272f, -0.60526f));
	primaryNodePositions.Add(SB::Vector3f(-0.96807f, 0.50272f, -0.60526f));
	secondaryNodePositions.Add(SB::Vector3f(0.96717f, -0.58341f, -0.98036f));
	secondaryNodePositions.Add(SB::Vector3f(-0.96717f, -0.58341f, -0.98036f));

	myWeaponMounts.Add(std::make_shared<WeaponMount>(myPrimaryWeapons, myWeaponRoot, primaryNodePositions, "PrimaryWeaponUI"));
	myWeaponMounts.Add(std::make_shared<WeaponMount>(mySecondaryWeapons, myWeaponRoot, secondaryNodePositions, "SecondaryWeaponUI"));
}

//Perform final intialization of weapons and nodes and equip default loadout
void PlayerShootComponent::InitWeapons()
{	
	myWeaponRoot->Initialize();

	for (unsigned short i = 0; i < myWeaponMounts.Size(); ++i)
	{
		myWeaponMounts[i]->InitNodes();
	}

	EquipWeaponInstantly(ePlayerWeaponType::ePrimary, 0);
	EquipWeaponInstantly(ePlayerWeaponType::eSecondary, 0);
}

//Sets the owner object (player) as the user of all weapons
void PlayerShootComponent::SetWeaponUser()
{
	for(unsigned short i = 0; i < myPrimaryWeapons.Size(); ++i)
	{
		myPrimaryWeapons[i]->SetUser(myObject);
	}

	for (unsigned short i = 0; i < mySecondaryWeapons.Size(); ++i)
	{
		mySecondaryWeapons[i]->SetUser(myObject);
	}
}

void PlayerShootComponent::UpdateWeaponMounts(const SB::Time& aDeltaTime)
{
	for (unsigned short i = 0; i < myWeaponMounts.Size(); ++i)
	{
		myWeaponMounts[i]->Update(aDeltaTime);
	}
}

void PlayerShootComponent::FireWeapon(const ePlayerWeaponType aWeaponType)
{
	myWeaponMounts[static_cast<unsigned short>(aWeaponType)]->FireEquippedWeapon();
}

void PlayerShootComponent::EquipWeaponInstantly(const ePlayerWeaponType aWeaponType, const std::string& aWeaponIdentifier)
{
	myWeaponMounts[static_cast<unsigned short>(aWeaponType)]->EquipWeaponInstantly(aWeaponIdentifier);
}

void PlayerShootComponent::EquipWeaponInstantly(const ePlayerWeaponType aWeaponType, const unsigned short aWeaponIndex)
{
	EquipWeaponInstantly(aWeaponType, myWeaponMounts[static_cast<unsigned short>(aWeaponType)]->GetWeaponIdentifierAtIndex(aWeaponIndex));
}


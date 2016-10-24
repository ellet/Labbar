#include "stdafx.h"
#include "PlayerShootComponent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Model/CubeModel.h"
#include "Engine/Effect/StandardEffect.h"
#include <Engine/Component/Factory/ComponentFactory.h>
#include <Engine/GameObject/GameObject.h>
#include "../Engine/Engine/SoundManager/SoundManger.h"
#include "Game/Component/Shooting/WeaponComponent.h"
#include "../Engine/Engine/Component/ModelComponent.h"
#include "../Utilities/Utilities/Math/MathMacros.h"
#include "Engine/GUI/RootGUIElement.h"
#include "../Engine/Engine/Component/Collider/CollisionFilter.h"


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

	myIsShootingPrimary = false;
	myIsShootingSecondary = false;
	myShotCounter = 0;
	myPrimaryShotCooldown = 0.f;
	mySecondaryShotCooldown = 0.f;

	myEquippedPrimaryWeapon = nullptr;
	myEquippedSecondaryWeapon = nullptr;
	myQueuedEquippedPrimaryWeapon = nullptr;
	myQueuedEquippedSecondaryWeapon = nullptr;
	myPrimaryWeaponEquipState = eWeaponEquipState::eUnequipped;
	mySecondaryWeaponEquipState = eWeaponEquipState::eUnequipped;

	CreateWeaponNodes();
	InitWeapons();
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
	UpdateEquippingWeapons(aDeltaTime);
	UpdatePrimaryWeapon(aDeltaTime);
	UpdateSecondaryWeapon(aDeltaTime);
}

void PlayerShootComponent::EquipPrimaryWeapon(const std::string& aWeaponIdentifier)
{
	if (myEquippedPrimaryWeapon != nullptr)
	{
		//If we already have this weapon equipped, abort
		if (myEquippedPrimaryWeapon->GetIdentifier() == aWeaponIdentifier)
		{
			return;
		}
	}


	for (unsigned short i = 0; i < myPrimaryWeapons.Size(); ++i)
	{
		if (myPrimaryWeapons[i]->GetIdentifier() == aWeaponIdentifier)
		{
			myEquippedPrimaryWeapon = myPrimaryWeapons[i];
			myPrimaryShotCooldown = myEquippedPrimaryWeapon->GetShotCooldown();
			myWeaponNodes[static_cast<unsigned short>(ePlayerWeaponNodeIndex::ePrimaryLeft)]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedPrimaryWeapon->GetWeaponModel());
			myWeaponNodes[static_cast<unsigned short>(ePlayerWeaponNodeIndex::ePrimaryRight)]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedPrimaryWeapon->GetWeaponModel());
			myObject->GetScene().GetGUI()->GetGUIElement("PrimaryWeaponUI")->SetSprite(myEquippedPrimaryWeapon->GetWeaponIconPath().c_str());
			//TODO: Add any other equip behavior we desire here, such as sounds and/or animations

			return;
		}
	}

	std::string errorMessage = "EquipPrimaryWeapon in PlayerShootComponent failed: No weapon named '" + aWeaponIdentifier + "' exists";
	assert(false && errorMessage.c_str());
}

void PlayerShootComponent::EquipPrimaryWeapon(const unsigned short aWeaponIndex)
{
	EquipPrimaryWeapon(myPrimaryWeapons[aWeaponIndex]->GetIdentifier());
}

void PlayerShootComponent::EquipSecondaryWeapon(const std::string& aWeaponIdentifier)
{
	if (myEquippedSecondaryWeapon != nullptr)
	{
		//If we already have this weapon equipped, abort
		if (myEquippedSecondaryWeapon->GetIdentifier() == aWeaponIdentifier)
		{
			return;
		}
	}

	for (unsigned short i = 0; i < mySecondaryWeapons.Size(); ++i)
	{
		if (mySecondaryWeapons[i]->GetIdentifier() == aWeaponIdentifier)
		{
			myEquippedSecondaryWeapon = mySecondaryWeapons[i];
			mySecondaryShotCooldown = myEquippedSecondaryWeapon->GetShotCooldown();
			myWeaponNodes[static_cast<unsigned short>(ePlayerWeaponNodeIndex::eSecondaryLeft)]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedSecondaryWeapon->GetWeaponModel());
			myWeaponNodes[static_cast<unsigned short>(ePlayerWeaponNodeIndex::eSecondaryRight)]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedSecondaryWeapon->GetWeaponModel());
			myObject->GetScene().GetGUI()->GetGUIElement("SecondaryWeaponUI")->SetSprite(myEquippedSecondaryWeapon->GetWeaponIconPath().c_str());
			//TODO: Add any other equip behavior we desire here, such as sounds and/or animations

			return;
		}
	}

	std::string errorMessage = "EquipSecondaryWeapon in PlayerShootComponent failed: No weapon named '" + aWeaponIdentifier + "' exists";
	assert(false && errorMessage.c_str());
}

void PlayerShootComponent::EquipSecondaryWeapon(const unsigned short aWeaponIndex)
{
	EquipSecondaryWeapon(mySecondaryWeapons[aWeaponIndex]->GetIdentifier());
}


SB::ReceiveResult PlayerShootComponent::Receive(const SB::LeftMouseButtonDownMessage& aMessage)
{
	myIsShootingPrimary = true;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::LeftMouseButtonUpMessage& aMessage)
{
	myIsShootingPrimary = false;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::RightMouseButtonDownMessage& aMessage)
{
	myIsShootingSecondary = true;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::RightMouseButtonUpMessage& aMessage)
{
	myIsShootingSecondary = false;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum1>& aMessage)
{
	EquipPrimaryWeapon("Gatling Gun");
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum2>& aMessage)
{
	EquipPrimaryWeapon("Blaster");
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum3>& aMessage)
{
	EquipSecondaryWeapon("Rocket Launcher");
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerShootComponent::Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum4>& aMessage)
{
	EquipSecondaryWeapon("Railgun");
	return SB::ReceiveResult::eContinue;
}

int PlayerShootComponent::GetTimesFired() const
{
	return myShotCounter;
}


//PRIVATE FUNCTIONS:

//Create the hierarchy of nodes which weapons are then attached to
void PlayerShootComponent::CreateWeaponNodes()
{
	//Create the weapon root object, which we will use to "mount" our equipped weapons onto (as offset children)
	SB::ObjectPtr owner = myObject->AsPointer();
	myWeaponRoot = myObject->GetScene().CreateGameObject("Player_WeaponRoot");
	myWeaponRoot->SetParent(owner);

	//Create (local) positions for each weapon node which will become their offsets from the parent Weapon Root object
	SB::GrowingArray<SB::Vector3f> nodePositions;
	nodePositions.Add(SB::Vector3f(0.96807f, 0.50272f, -0.60526f));
	nodePositions.Add(SB::Vector3f(-0.96807f, 0.50272f, -0.60526f));
	nodePositions.Add(SB::Vector3f(0.96717f, -0.58341f, -0.98036f));
	nodePositions.Add(SB::Vector3f(-0.96717f, -0.58341f, -0.98036f));

	//Create the 4 nodes where weapons will be mounted
	for (unsigned short i = 0; i < 4; ++i)
	{
		std::string id = "Player_WeaponNode" + std::to_string(i);
		SB::ObjectPtr newNode = myObject->GetScene().CreateGameObject(id);
		newNode->SetPosition(nodePositions[i]);
		newNode->SetParent(myWeaponRoot);
		newNode->CreateComponent<SB::ModelComponent>()->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f)); //Actual model used is set when equipping a weapon to the node
		myWeaponNodes.Add(newNode);
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
		myPrimaryWeapons.GetLast()->SetCollisonFilters(CollisionFilter::eEnemy | CollisionFilter::eEnviorment);
		myPrimaryWeapons.GetLast()->SetLayerID(static_cast<unsigned int>(CollisionFilter::ePlayer));
	}

	//Load secondary weapons
	for (unsigned short i = 0; i < doc["secondaryWeapons"].Capacity(); ++i)
	{
		mySecondaryWeapons.Add(LoadWeapon(doc["secondaryWeapons"][i]));
		mySecondaryWeapons.GetLast()->SetCollisonFilters(CollisionFilter::eEnemy | CollisionFilter::eEnviorment);
		mySecondaryWeapons.GetLast()->SetLayerID(static_cast<unsigned int>(CollisionFilter::ePlayer));
	}
}

std::shared_ptr<WeaponComponent> PlayerShootComponent::LoadWeapon(SB::DataNode aWeaponData)
{
	WeaponData data;
	data.identifier = aWeaponData["identifier"].GetString();
	data.weaponModelPath = aWeaponData["weaponModelPath"].GetString();
	data.weaponIconPath = aWeaponData["weaponIconPath"].GetString();
	data.projectileModelPath = aWeaponData["projectileModelPath"].GetString();
	data.shootSound = aWeaponData["shootSound"].GetString();
	data.shotScale = SB::Vector3f(aWeaponData["shotScale"][0].GetFloat(), aWeaponData["shotScale"][1].GetFloat(), aWeaponData["shotScale"][2].GetFloat());
	data.barrelOffset = SB::Vector3f(aWeaponData["barrelOffset"][0].GetFloat(), aWeaponData["barrelOffset"][1].GetFloat(), aWeaponData["barrelOffset"][2].GetFloat());
	data.shotCooldown = aWeaponData["shotCooldown"].GetFloat();
	data.damage = aWeaponData["damage"].GetFloat();
	data.shotSpeed = aWeaponData["shotSpeed"].GetFloat();

	return std::make_shared<WeaponComponent>(data);
}

//Perform final intialization of weapons and nodes and equip default loadout
void PlayerShootComponent::InitWeapons()
{	
	myWeaponRoot->Initialize();

	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->Initialize();
	}

	EquipPrimaryWeapon(0);
	EquipSecondaryWeapon(0);
}

void PlayerShootComponent::UpdateEquippingWeapons(const SB::Time& aDeltaTime)
{
	//TODO

	if (myPrimaryWeaponEquipState == eWeaponEquipState::eEquipped)
	{
		return;
	}

	if (myPrimaryWeaponEquipState == eWeaponEquipState::eUnequipped)
	{

	}
}

void PlayerShootComponent::UpdatePrimaryWeapon(const SB::Time& aDeltaTime)
{
	if (myEquippedPrimaryWeapon == nullptr)
	{
		return;
	}


	if (myPrimaryShotCooldown > 0.f)
	{
		myPrimaryShotCooldown -= aDeltaTime;
	}

	if (myIsShootingPrimary == true)
	{
		if (myPrimaryShotCooldown > 0.f)
		{
			return;
		}

		FireWeapon(myEquippedPrimaryWeapon, true);

		myPrimaryShotCooldown = myEquippedPrimaryWeapon->GetShotCooldown();
	}
}

void PlayerShootComponent::UpdateSecondaryWeapon(const SB::Time& aDeltaTime)
{
	if (myEquippedSecondaryWeapon == nullptr)
	{
		return;
	}


	if (mySecondaryShotCooldown > 0.f)
	{
		mySecondaryShotCooldown -= aDeltaTime;
	}

	if (myIsShootingSecondary == true)
	{
		if (mySecondaryShotCooldown > 0.f)
		{
			return;
		}

		FireWeapon(myEquippedSecondaryWeapon, false);

		mySecondaryShotCooldown = myEquippedSecondaryWeapon->GetShotCooldown();
	}
}

void PlayerShootComponent::FireWeapon(std::shared_ptr<WeaponComponent> aWeapon, const bool aIsPrimaryWeapon)
{
	assert(aWeapon != nullptr && "PlayerShootComponent::FireWeapon attempted to fire a nullptr Weapon");

	const SB::Camera& camera = myObject->GetScene().GetCamera();

	//DEBUGGING AHOY:
	/*
	SB::Vector3f cameraPos = camera.GetPosition();
	SB::Vector3f playerPos = myObject->GetPosition();
	SB::Vector3f rootPos = myWeaponRoot->GetPosition();
	SB::Vector3f nodeAPos = myWeaponNodes[0]->GetPosition();
	SB::Vector3f nodeBPos = myWeaponNodes[1]->GetPosition();
	SB::Vector3f nodeCPos = myWeaponNodes[2]->GetPosition();
	SB::Vector3f nodeDPos = myWeaponNodes[3]->GetPosition();
	*/
	//END DEBUGGING AHOY

	SB::Vector3f weaponPosition;
	SB::Quaternion weaponOrientation;
	unsigned short weaponIndex;

	if (myShotCounter % 2 == 0)
	{
		if (aIsPrimaryWeapon == true)
			weaponIndex = static_cast<unsigned short>(ePlayerWeaponNodeIndex::ePrimaryLeft);
		else
			weaponIndex = static_cast<unsigned short>(ePlayerWeaponNodeIndex::eSecondaryLeft);
	}
	else
	{
		if (aIsPrimaryWeapon == true)
			weaponIndex = static_cast<unsigned short>(ePlayerWeaponNodeIndex::ePrimaryRight);
		else
			weaponIndex = static_cast<unsigned short>(ePlayerWeaponNodeIndex::eSecondaryRight);
	}

	aWeapon->SetGameObject(*myWeaponNodes[weaponIndex]);
	weaponPosition = myWeaponNodes[weaponIndex]->GetTransformation().GetPosition();
	weaponOrientation = camera.GetOrientation();

	++myShotCounter;

	aWeapon->FireWeapon(weaponPosition, weaponOrientation);
}

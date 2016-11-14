#include "stdafx.h"
#include "WeaponMount.h"
#include "Game/Component/Shooting/Weapons/WeaponComponent.h"
#include "Engine/Component/ModelComponent.h"
#include "Engine/Camera/Camera.h"
#include "PlayerControllerComponent.h"
#include "PlayerMessages.h"
#include "../Engine/Engine/SoundManager/SoundManager.h"
#include "../Engine/Engine/SoundManager/SpeakerComponent.h"

WeaponMount::WeaponMount(const SB::GrowingArray<std::shared_ptr<WeaponComponent>>& aAvailableWeapons, const SB::ObjectPtr& aWeaponRoot, const SB::GrowingArray<SB::Vector3f>& aWeaponNodeLocalPositions, const std::string& aWeaponGUIIdentifier)
	: myWeapons(aAvailableWeapons)
{
	static unsigned short weaponMountCounter = 0; //Used for automatic ID assignment purposes

	myWeaponNodes.Reserve(aWeaponNodeLocalPositions.Size());
	myMuzzleNodes.Reserve(aWeaponNodeLocalPositions.Size());

	myWeaponMountID = weaponMountCounter;
	myWeaponRoot = aWeaponRoot;
	myEquippedWeapon = nullptr;
	myQueuedEquippedWeapon = nullptr;
	mySpeakerComponent = nullptr;
	myWeaponGUIIdentifier = aWeaponGUIIdentifier;
	myShotCooldown = 0.f;
	myWeaponEquipState = eWeaponEquipState::eUnequipped;
	myIsFiring = false;
	myCurrentlyFiringNodeIndex = 0;
	myCurrentBarrelRotationVelocity = 0.f;
	myOldBarrelRotationVelocity = 0.f;
	myOverheatTimer = 0.f;
	SetCurrentOverheatAmount(0.f);
	myHasOverheated = false;


	const float RetractDistance = -2.f;
	const float RetractTime = 0.5f;
	const SB::Vector3f RetractVector(0.f, 0.f, -RetractDistance);

	myWeaponSwapCooldown = RetractTime;
	myWeaponSwapTimer = myWeaponSwapCooldown;
	myWeaponSwapStep = RetractDistance / RetractTime;

	for (unsigned short i = 0; i < aWeaponNodeLocalPositions.Size(); ++i)
	{
		//Create a weapon node for each position; set parent in Init
		std::string nodeID = "Player_WeaponMount" + std::to_string(weaponMountCounter) + "_Node" + std::to_string(i);
		SB::ObjectPtr newNode = aWeaponRoot->GetScene().CreateGameObject(nodeID);
		newNode->SetParent(aWeaponRoot);
		newNode->SetPosition(aWeaponNodeLocalPositions[i]);
		//newNode->SetRotation(newNode->GetParent()->GetRotation());
		newNode->CreateComponent<SB::ModelComponent>()->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f)); //Actual model used is set when equipping a weapon to the node
		newNode->GetComponent<SB::ModelComponent>()->SetModel(nullptr);
		myWeaponNodes.Add(newNode);

		myExtendedPositions.Add(aWeaponNodeLocalPositions[i]);
		myRetractedPositions.Add(SB::Vector3f(aWeaponNodeLocalPositions[i] + RetractVector));

		//Create a muzzle object as a child to the weapon node
		std::string muzzleID = "Player_WeaponMount" + std::to_string(weaponMountCounter) + "_Muzzle" + std::to_string(i);
		SB::ObjectPtr newMuzzle = aWeaponRoot->GetScene().CreateGameObject(muzzleID);
		newMuzzle->SetParent(newNode);
		newMuzzle->SetPosition(SB::Vector3f::Zero); //Position is set when a weapon is equipped based on its barrel/muzzle offset
		//newMuzzle->SetRotation(newMuzzle->GetParent()->GetRotation());
		myMuzzleNodes.Add(newMuzzle);
	}
	//for (unsigned short i = 0; i < myWeapons.Size(); i++)
	//{
	//	if (myWeapons[i]->GetIdentifier() == "Gatling Gun")
	//	{
	//		PlayerWeaponSoundID newID;
	//		newID.myRTPCidentifier = "GatlingGunRPM";
	//		newID.myRTPCvalue = 0;
	//		newID.mySoundID = SB::Engine::GetSoundManager().RegisterObjectAtFreeID();
	//		myPlayerWeaponSoundIDs[myWeapons[i]->GetIdentifier()] = newID;
	//	}
	//}

	assert(myWeaponNodes.Size() == myMuzzleNodes.Size() && "WeaponMount created with mismatched WeaponNode and MuzzleNode counts");
	assert(myWeaponNodes.Size() > 0 && "WeaponMount created with no Weapon Nodes to fire weapons from");
	++weaponMountCounter;
}

//Initialize node objects
void WeaponMount::InitNodes()
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->Initialize();
		myMuzzleNodes[i]->Initialize();
	}
	mySpeakerComponent = &*myWeapons[0]->GetUser()->GetComponent<SB::SpeakerComponent>();
	if (mySpeakerComponent == nullptr)
	{
		Error("Weapon mount on object " + myWeapons[0]->GetUser()->GetIdentifier() + " is missing a Speaker component");
	}
	for (unsigned short i = 0; i < myWeapons.Size(); i++)
	{
		if (myWeapons[i]->GetIdentifier() == "Gatling Gun")
		{
			mySpeakerComponent->RegisterRTPC("GatlingGunRPM");
		}
	}

}

WeaponMount::~WeaponMount()
{
}

void WeaponMount::OnRemoved()
{
	myWeaponRoot = nullptr;
	myWeaponNodes.RemoveAll();
	myMuzzleNodes.RemoveAll();
}

void WeaponMount::Update(const SB::Time& aDeltaTime)
{
	UpdateRTPC();
	UpdateEquipping(aDeltaTime);
	UpdateBarrelRotation(aDeltaTime);
	UpdateOverheat(aDeltaTime);
	UpdateFiring(aDeltaTime);
}

void WeaponMount::EquipWeapon(const std::string& aWeaponIdentifier)
{
	//If we're in the process of equipping a weapon, abort
	if (myWeaponEquipState != eWeaponEquipState::eEquipped)
	{
		return;
	}
	if (myHasOverheated == true)
	{
		TriggerOverheatInputErrorFeedback();
		return;
	}

	if (myEquippedWeapon != nullptr)
	{
		//If we already have this weapon equipped, abort
		if (myEquippedWeapon->GetIdentifier() == aWeaponIdentifier)
		{
			return;
		}
	}

	if (myQueuedEquippedWeapon != nullptr)
	{
		//If we already have this weapon queued to be equipped, abort
		if (myQueuedEquippedWeapon->GetIdentifier() == aWeaponIdentifier)
		{
			return;
		}
	}


	for (unsigned short i = 0; i < myWeapons.Size(); ++i)
	{
		if (myWeapons[i]->GetIdentifier() == aWeaponIdentifier)
		{
			if (myWeapons[i]->GetIsOwned() == false)
			{
				std::string errorMessage = "Tried to equip weapon which you do not own: '" + myWeapons[i]->GetIdentifier() + "'";
				std::cout << errorMessage.c_str() << std::endl;
				return;
			}

			myQueuedEquippedWeapon = myWeapons[i];
			assert(myQueuedEquippedWeapon != myEquippedWeapon && "Queued weapon to be equipped was set to already equipped weapon in WeaponMount::EquipWeapon");

			if (myEquippedWeapon != nullptr)
			{
				StartRetractingWeapon();
			}
			else
			{
				StartExtendingWeapon();
			}

			return;
		}
	}


	std::string errorMessage = "EquipWeapon in WeaponMount failed: No weapon named '" + aWeaponIdentifier + "' exists in PlayerShootComponent";
	assert(false && errorMessage.c_str());
}

void WeaponMount::EquipWeapon(const unsigned short aWeaponIndex)
{
	EquipWeapon(myWeapons[aWeaponIndex]->GetIdentifier());
}

void WeaponMount::EquipWeaponInstantly(const std::string& aWeaponIdentifier)
{
	if (myEquippedWeapon != nullptr)
	{
		//If we already have this weapon equipped, abort
		if (myEquippedWeapon->GetIdentifier() == aWeaponIdentifier)
		{
			return;
		}
	}


	for (unsigned short i = 0; i < myWeapons.Size(); ++i)
	{
		if (myWeapons[i]->GetIdentifier() == aWeaponIdentifier)
		{
			myEquippedWeapon = myWeapons[i];
			myShotCooldown = myEquippedWeapon->GetShotCooldown();
			for (unsigned short j = 0; j < myWeaponNodes.Size(); ++j)
			{
				//Set model for all weapon nodes
				myWeaponNodes[j]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedWeapon->GetWeaponModel());
				myMuzzleNodes[j]->SetPosition(myEquippedWeapon->GetBarrelOffset());
			}
			myWeaponRoot->GetScene().GetGUI()->GetGUIElement(myWeaponGUIIdentifier)->SetSprite(myEquippedWeapon->GetWeaponIconPath().c_str());

			//Add any other equip behavior we desire here, such as sounds and/or animations

			FinalizeEquip();

			return;
		}
	}


	std::string errorMessage = "EquipWeapon in WeaponMount failed: No weapon named '" + aWeaponIdentifier + "' exists in PlayerShootComponent";
	assert(false && errorMessage.c_str());
}

void WeaponMount::EquipWeaponInstantly(const unsigned short aWeaponIndex)
{
	EquipWeaponInstantly(myWeapons[aWeaponIndex]->GetIdentifier());
}

void WeaponMount::FireEquippedWeapon()
{
	FireWeapon(myEquippedWeapon);
}

void WeaponMount::FireWeapon(std::shared_ptr<WeaponComponent> aWeapon)
{
	assert(aWeapon != nullptr && "PlayerShootComponent::FireWeapon attempted to fire a nullptr Weapon");

	AddOverheat();

	aWeapon->SetGameObject(*myMuzzleNodes[myCurrentlyFiringNodeIndex]);

	SB::Vector3f weaponPosition = myMuzzleNodes[myCurrentlyFiringNodeIndex]->GetTransformation().GetPosition();
	SB::Quaternion weaponOrientation = myWeaponRoot->GetScene().FindObject("Player")->GetComponent<PlayerControllerComponent>()->GetAimDirection();
	//SB::Quaternion weaponOrientation = myMuzzleNodes[myCurrentlyFiringNodeIndex]->GetWorldRotation();

	++myCurrentlyFiringNodeIndex;
	if (myCurrentlyFiringNodeIndex >= myMuzzleNodes.Size())
	{
		myCurrentlyFiringNodeIndex = 0;
	}
	if (aWeapon->GetIdentifier() == "Gatling Gun")
	{
		mySpeakerComponent->PostSoundEvent(aWeapon->GetShootSound().c_str());
	}
	else
	{
		SB::Engine::GetSoundManager().PostEvent(aWeapon->GetShootSound().c_str());
	}
	aWeapon->FireWeapon(weaponPosition, weaponOrientation);
}


const std::string& WeaponMount::GetWeaponIdentifierAtIndex(const unsigned short aWeaponIndex)
{
	return myWeapons[aWeaponIndex]->GetIdentifier();
}


void WeaponMount::Reset()
{
	ResetOverheat();
	ResetOverheatTimer();
	myIsFiring = false;
}

//PRIVATE FUNCTIONS:

void WeaponMount::UpdateEquipping(const SB::Time& aDeltaTime)
{
	switch (myWeaponEquipState)
	{
	case eWeaponEquipState::eEquipped:
	{
		return;
	}
	break;

	case eWeaponEquipState::eEquipping:
	{
		PerformWeaponExtensionStep(aDeltaTime);

		myWeaponSwapTimer -= aDeltaTime;
		if (myWeaponSwapTimer <= 0.f)
		{
			FinalizeEquip();
		}
	}
	break;

	case eWeaponEquipState::eUnequipping:
	{
		PerformWeaponRetractionStep(aDeltaTime);

		myWeaponSwapTimer -= aDeltaTime;
		if (myWeaponSwapTimer <= 0.f)
		{
			FinalizeUnequip();
		}
	}
	break;

	case eWeaponEquipState::eUnequipped:
	{
		SwapQueuedWeaponWithCurrentlyEquipped();
		StartExtendingWeapon();
	}
	break;
	}
}

void WeaponMount::UpdateBarrelRotation(const SB::Time& aDeltaTime)
{
	if (GetCanEquippedWeaponRotate() == false)
	{
		return;
	}
	myOldBarrelRotationVelocity = myCurrentBarrelRotationVelocity;

	const float RotationAmount = (myEquippedWeapon->GetFiringRotationVelocityMax() / myEquippedWeapon->GetFiringRotationVelocityAccelerationTime().InSeconds()) * aDeltaTime.InSeconds();

	if (myIsFiring == true)
	{
		const float RotationVelocityCap = myEquippedWeapon->GetFiringRotationVelocityMax();
		if (myCurrentBarrelRotationVelocity < RotationVelocityCap)
		{
			//Accelerate rotation
			myCurrentBarrelRotationVelocity += RotationAmount;
			if (myCurrentBarrelRotationVelocity > RotationVelocityCap)
			{
				myCurrentBarrelRotationVelocity = RotationVelocityCap;
			}
		}
	}
	else
	{
		if (myCurrentBarrelRotationVelocity > 0.f)
		{
			//Decelerate rotation
			myCurrentBarrelRotationVelocity -= RotationAmount;
			if (myCurrentBarrelRotationVelocity < 0.f)
			{
				myCurrentBarrelRotationVelocity = 0.f;
			}
		}
	}

	if (myCurrentBarrelRotationVelocity > 0.f)
	{
		RotateWeaponNodes(myCurrentBarrelRotationVelocity * aDeltaTime.InSeconds());
	}
}

void WeaponMount::UpdateOverheat(const SB::Time& aDeltaTime)
{
	if (myHasOverheated == true)
	{
		myOverheatTimer += aDeltaTime;

		if (myOverheatTimer >= myEquippedWeapon->GetOverheatDuration() && myIsFiring == false)
		{
			ResetOverheatTimer();
		}
	}
	else //Not currently overheated, so tick down any accumulated overheat percentage if we're not firing
	{
		const float OverheatDropoffPerSecond = 15.f; //TODO: Allow data adjustment of this value

		if (myCurrentOverheatAmount > 0.f /*&& myIsFiring == false*/)
		{
			SetCurrentOverheatAmount(myCurrentOverheatAmount - (OverheatDropoffPerSecond * aDeltaTime.InSeconds()));
			if (myCurrentOverheatAmount <= 0.f)
			{
				ResetOverheat();
			}
		}
	}
}

void WeaponMount::UpdateFiring(const SB::Time& aDeltaTime)
{
	if (myEquippedWeapon == nullptr || myWeaponEquipState != eWeaponEquipState::eEquipped || myHasOverheated == true)
	{
		return;
	}


	if (myShotCooldown > 0.f)
	{
		myShotCooldown -= aDeltaTime;
	}

	if (myIsFiring == true)
	{
		if (myShotCooldown > 0.f)
		{
			return;
		}

		FireWeapon(myEquippedWeapon);
		myShotCooldown = myEquippedWeapon->GetShotCooldown();
	}
}

void WeaponMount::UpdateRTPC()
{
	for (unsigned short i = 0; i < myWeapons.Size(); i++)
	{
		if (myWeapons[i]->GetIdentifier() == "Gatling Gun")
		{
			if (myCurrentBarrelRotationVelocity >= myOldBarrelRotationVelocity)
			{
				mySpeakerComponent->SetRTPC("GatlingGunRPM", static_cast<int>((myCurrentBarrelRotationVelocity / myEquippedWeapon->GetFiringRotationVelocityMax()) * 100.f));
			}
			else
			{
				mySpeakerComponent->PostSoundEvent("Stop_GatlingGun");
			}
		}
	}
}

void WeaponMount::SwapQueuedWeaponWithCurrentlyEquipped()
{
	myEquippedWeapon = myQueuedEquippedWeapon;
	myShotCooldown = myEquippedWeapon->GetShotCooldown();
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		//Set model for all weapon nodes
		myWeaponNodes[i]->GetComponent<SB::ModelComponent>()->SetModel(myEquippedWeapon->GetWeaponModel());
		myMuzzleNodes[i]->SetPosition(myEquippedWeapon->GetBarrelOffset());
	}
	myWeaponRoot->GetScene().GetGUI()->GetGUIElement(myWeaponGUIIdentifier)->SetSprite(myEquippedWeapon->GetWeaponIconPath().c_str());

	ResetWeaponNodeRotations();
	//ResetOverheat();
	//ResetOverheatTimer();

	//Add any other equip behavior we desire here, such as sounds and/or animations
}

void WeaponMount::StartRetractingWeapon()
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->SetPosition(myExtendedPositions[i]);
	}

	myWeaponEquipState = eWeaponEquipState::eUnequipping;
	myWeaponSwapTimer = myWeaponSwapCooldown;
}

void WeaponMount::StartExtendingWeapon()
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->SetPosition(myRetractedPositions[i]);
	}

	myWeaponEquipState = eWeaponEquipState::eEquipping;
	myWeaponSwapTimer = myWeaponSwapCooldown;
}

void WeaponMount::PerformWeaponRetractionStep(const SB::Time& aDeltaTime)
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->AddPosition(SB::Vector3f(0.f, 0.f, -myWeaponSwapStep * aDeltaTime.InSeconds()));
	}
}

void WeaponMount::PerformWeaponExtensionStep(const SB::Time& aDeltaTime)
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->AddPosition(SB::Vector3f(0.f, 0.f, myWeaponSwapStep * aDeltaTime.InSeconds()));
	}
}

//Sets unequipped state and snaps weapons to intended positions
void WeaponMount::FinalizeUnequip()
{
	myWeaponEquipState = eWeaponEquipState::eUnequipped;

	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->SetPosition(myRetractedPositions[i]);
	}
}

//Sets equipped state and removes the queued weapon, allowing firing of the newly equipped weapon, and snaps weapons to intended positions
void WeaponMount::FinalizeEquip()
{
	myWeaponEquipState = eWeaponEquipState::eEquipped;
	myQueuedEquippedWeapon = nullptr;

	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->SetPosition(myExtendedPositions[i]);
	}
}

void WeaponMount::RotateWeaponNodes(const float aAngleDegrees)
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->GetRotation().RotateAroundLocalZ(DEGREES_TO_RADIANSF(aAngleDegrees));
	}
}

void WeaponMount::ResetWeaponNodeRotations()
{
	for (unsigned short i = 0; i < myWeaponNodes.Size(); ++i)
	{
		myWeaponNodes[i]->SetRotation(SB::Quaternion());
	}

	myCurrentBarrelRotationVelocity = 0.f;
}

bool WeaponMount::GetCanEquippedWeaponRotate() const
{
	if (myEquippedWeapon != nullptr)
	{
		return (myEquippedWeapon->GetFiringRotationVelocityAccelerationTime() > 0 && myEquippedWeapon->GetFiringRotationVelocityMax() > 0);
	}

	return false;
}

void WeaponMount::AddOverheat()
{
	assert(myEquippedWeapon != nullptr && "WeaponMount::AddOverheat has no equipped weapon to add overheat from");

	SetCurrentOverheatAmount(myCurrentOverheatAmount + myEquippedWeapon->GetOverheatPerShot());
	if (myCurrentOverheatAmount >= 100.f)
	{
		SetCurrentOverheatAmount(100.f);
		TriggerOverheat();
	}
}

void WeaponMount::TriggerOverheat()
{
	myHasOverheated = true;
	myIsFiring = false;
	//TODO: Spawn smoke particles & play a sound, possibly flash GUI bar red
}

//Exclusively resets the timer and sets overheated state to false
void WeaponMount::ResetOverheatTimer()
{
	myOverheatTimer = 0.f;
	myHasOverheated = false;
}

//Resets overheat amount to 0 and clears overheated state
void WeaponMount::ResetOverheat()
{
	SetCurrentOverheatAmount(0.f);
	myHasOverheated = false;
}

//Trigger error sound/feedback when player attempts to swap equipped weapons and/or fire during overheat
void WeaponMount::TriggerOverheatInputErrorFeedback()
{
	assert(myHasOverheated == true && "Attempted to trigger Overheat input error feedback when weapon isn't overheating");

	//TODO: Play sound, flash GUI red, and other feedback to signal input as unavailable whilst overheating
}

void WeaponMount::SetCurrentOverheatAmount(const float aNewValue)
{
	myCurrentOverheatAmount = aNewValue;
	SB::PostMaster::Post<OverheatChangedMessage>(OverheatChangedMessage(myCurrentOverheatAmount, GetIsPrimaryWeaponMount()));
}

#include "stdafx.h"
#include "PlayerControllerComponent.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Engine/SoundManager/SoundManger.h"
#include "Engine/Camera/Controllers/FirstPersonCameraController.h"
#include <Engine/Component/ModelComponent.h>
#include <Engine/Physics/PhysicsComponent.h>
#include <Engine/Component/Collider/ColliderComponent.h>
//#include <Engine/CloseGameMessage.h>
#include <Engine/Scene/SceneStack/PopSceneMessage.h>

PlayerControllerComponent::PlayerControllerComponent()
{
	const float MovementSpeed = 10.f;
	const float RotationSpeed = 3.f;
	const float MouseRotationSpeed = 1.f;

	myRotationAccelerationCap = RotationSpeed / 3.f;

	myDriftMovementSpeed = MovementSpeed;
	myDriftRotationSpeed = RotationSpeed - myRotationAccelerationCap;

	myCurrentMovementSpeed = MovementSpeed;
	myCurrentRotationSpeed = RotationSpeed;

	myBoostMovementSpeed = myDriftMovementSpeed * 7.5f;
	myBoostRotationSpeed = (RotationSpeed / 2.f) - myRotationAccelerationCap;
	
	myMouseRotationSpeed = MouseRotationSpeed;

	InitMovementStates();

	myMaxMoveSpeed = 20.f;
	myMaxBoostSpeed = 30.f;

	myFirstPersonCameraController = nullptr;
}

void PlayerControllerComponent::Initialize()
{
	myObject->SetIdentifier("Player");
	//myCockpit = myObject->GetScene().CreateAndAddModel("Cockpit", "Assets/Models/Player/Cockpit/cockpit.fbx", SB::Vector3f(0.f, 0.f, 0.f), SB::Vector3f::One);
	/*myCockpit->SetParent(myObject->AsPointer());
	myCockpit->GetComponent<SB::ModelComponent>()->SetMatrix(SB::Matrix44f::CreateScale(1.f, 1.f, 1.f) * SB::Matrix44f::CreateRotateAroundY(Pi));
	myCockpit->Initialize();*/

	GetGameObject().GetComponent<SB::ColliderComponent>()->SetColliderLayedID(CollisionFilter::ePlayer);
	GetGameObject().GetComponent<SB::ColliderComponent>()->SetCollisionFilter(CollisionFilter::eEnemy | CollisionFilter::eEnviorment);

	myOutercrosshairSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Gui/Muspekare/sight.dds"));
	myInnercrosshairSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Gui/Muspekare/innersight.dds"));

	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();
	if (myPhysicsComponent == nullptr)
	{
		Error("PlayerControllerComponent requires a PhysicsComponent to be attached on the same object!");
	}
}

PlayerControllerComponent::~PlayerControllerComponent()
{
}

void PlayerControllerComponent::Update(const SB::Time& aDeltaTime)
{
	UpdateAcceleration(aDeltaTime);
	
	UpdateMouseOrientation(aDeltaTime);

	bool isMoving = false;
	if (GetIsMoving() == true || GetIsRotating() == true)
	{
		isMoving = true;
	}

	float movemenetAcceleration = 125.f;

	bool forward = myMoveForward && !myMoveBackward;
	bool backward = myMoveBackward && !myMoveForward;

	if (forward)
	{
		myVelocity += (myObject->GetRotation().GetForward() * movemenetAcceleration * aDeltaTime.InSeconds());
	}
	if (backward)
	{
		myVelocity += (myObject->GetRotation().GetBackward() * movemenetAcceleration * aDeltaTime.InSeconds());
	}

	if (myMoveLeft)
	{
		myVelocity += myObject->GetRotation().GetLeft() * movemenetAcceleration * aDeltaTime.InSeconds();
	}
	if (myMoveRight)
	{
		myVelocity += myObject->GetRotation().GetRight() * movemenetAcceleration * aDeltaTime.InSeconds();
	}

	if (myMoveUp)
	{
		myVelocity += myObject->GetRotation().GetUpward() * movemenetAcceleration * aDeltaTime.InSeconds();
	}
	if (myMoveDown)
	{
		myVelocity += myObject->GetRotation().GetDownward() * movemenetAcceleration * aDeltaTime.InSeconds();
	}


	if (myRollLeft)
	{
		myObject->GetRotation().RotateAroundLocalZ(myDriftRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myRollRight)
	{
		myObject->GetRotation().RotateAroundLocalZ(-myDriftRotationSpeed * aDeltaTime.InSeconds());
	}


	if (myPitchForward)
	{
		myObject->GetRotation().RotateAroundLocalX(-myCurrentRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myPitchBackward)
	{
		myObject->GetRotation().RotateAroundLocalX(myCurrentRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateLeft)
	{
		myObject->GetRotation().RotateAroundLocalY(-myCurrentRotationSpeed * aDeltaTime.InSeconds());
	}
	if (myRotateRight)
	{
		myObject->GetRotation().RotateAroundLocalY(myCurrentRotationSpeed * aDeltaTime.InSeconds());
	}

	if (isMoving)
	{
		SB::Engine::GetSoundManager().PostEvent("Player_Thruster");
	}
	else
	{
		SB::Engine::GetSoundManager().PostEvent("Stop_Thruster");
	}

	float length = myVelocity.Length();
	SB::Vector3f direction = length == 0.f ? SB::Vector3f::Zero : myVelocity.GetNormalized();

	length *= MAX(0.f, 1.f - aDeltaTime.InSeconds() * 4.f);
	if (length > myMaxMoveSpeed)
	{
		length = myMaxMoveSpeed;
	}
	myVelocity = direction * length;

	myPhysicsComponent->SetSpeed(length);
	myPhysicsComponent->SetForceDirection(direction);
}

void PlayerControllerComponent::ActivateFirstPersonCamera()
{
	if (myObject == nullptr)
	{
		Error("ActivateFirstPersonCamera on PlayerControllerComponent failed due to null owner object")
	}	

	if (myFirstPersonCameraController == nullptr)
	{
		myFirstPersonCameraController = std::make_shared<SB::FirstPersonCameraController>(myObject);
	}

	myObject->GetScene().PushCameraController(myFirstPersonCameraController);
}

SB::ReceiveResult PlayerControllerComponent::Receive(const DrawCrosshairEvent& aMessage)
{
	SB::Vector2f crosshairLocation = SB::Vector2f(1280.f, 720.f) / 2.f + this->myRotationDelta * 0.2f;

	myOutercrosshairSprite.SetPosition(crosshairLocation);
	myOutercrosshairSprite.SetOrigin(myOutercrosshairSprite.GetTextureRectSize() / 2.f);
	myOutercrosshairSprite.Render();

	myInnercrosshairSprite.SetPosition(crosshairLocation);
	myInnercrosshairSprite.SetOrigin(myInnercrosshairSprite.GetTextureRectSize() / 2.f);
	myInnercrosshairSprite.Render();

	SB::Vector3f localVelocity = (myObject->GetScene().GetCamera().GetOrientation() * myVelocity);
	localVelocity /= myMaxMoveSpeed;

	SB::Quaternion q;
	q.RotateAroundLocalZ(-myRotationDelta.x * 0.0005f - localVelocity.x * 0.1f);
	q.RotateAroundLocalX(myRotationDelta.y * 0.0002f - localVelocity.y * 0.05f);
	q.RotateAroundLocalY(Pi);
	myObject->GetScene().FindObject("Player_WeaponRoot")->SetRotation(q);

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::AnyKeyDownMessage& aMessage)
{
	switch (aMessage.key)
	{
	case SB::KeyboardKey::eEscape:
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
		break;
	case SB::KeyboardKey::eQ:
		myRollLeft = true;
		break;
	case SB::KeyboardKey::eE:
		myRollRight = true;
		break;

	case SB::KeyboardKey::eA:
		myMoveLeft = true;
		break;
	case SB::KeyboardKey::eD:
		myMoveRight = true;
		break;
	case SB::KeyboardKey::eW:
		myMoveForward = true;
		break;
	case SB::KeyboardKey::eS:
		myMoveBackward = true;
		break;

	case SB::KeyboardKey::eLeft:
		myRotateLeft = true;
		break;
	case SB::KeyboardKey::eRight:
		myRotateRight = true;
		break;
	case SB::KeyboardKey::eUp:
		myPitchForward = true;
		break;
	case SB::KeyboardKey::eDown:
		myPitchBackward = true;
		break;

	case SB::KeyboardKey::eControl:
		myMoveDown = true;
		break;
	case SB::KeyboardKey::eSpace:
		myMoveUp = true;
		break;

	case SB::KeyboardKey::eShift:
		SetIsBoosting(true);
		break;
	}
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::RawMouseMoveMessage& aMessage)
{
	myRotationDelta += SB::Vector2f(static_cast<float>(aMessage.deltaX), static_cast<float>(aMessage.deltaY));

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::AnyKeyUpMessage& aMessage)
{
	switch (aMessage.key)
	{
	case SB::KeyboardKey::eQ:
		myRollLeft = false;
		break;
	case SB::KeyboardKey::eE:
		myRollRight = false;
		break;

	case SB::KeyboardKey::eA:
		myMoveLeft = false;
		break;
	case SB::KeyboardKey::eD:
		myMoveRight = false;
		break;
	case SB::KeyboardKey::eW:
		myMoveForward = false;
		break;
	case SB::KeyboardKey::eS:
		myMoveBackward = false;
		break;

	case SB::KeyboardKey::eLeft:
		myRotateLeft = false;
		break;
	case SB::KeyboardKey::eRight:
		myRotateRight = false;
		break;
	case SB::KeyboardKey::eUp:
		myPitchForward = false;
		break;
	case SB::KeyboardKey::eDown:
		myPitchBackward = false;
		break;

	case SB::KeyboardKey::eControl:
		myMoveDown = false;
		break;
	case SB::KeyboardKey::eSpace:
		myMoveUp = false;
		break;

	case SB::KeyboardKey::eShift:
		SetIsBoosting(false);
		break;
	}
	return SB::ReceiveResult::eContinue;
}

void PlayerControllerComponent::LoadData(SB::DataNode aProperties)
{
	PlayerControllerData data;
	data.movementSpeed = aProperties["movementSpeed"].GetFloat();
	data.mouseRotationSpeed = aProperties["mouseRotationSpeed"].GetFloat();
	data.keyboardRotationSpeed = aProperties["keyboardRotationSpeed"].GetFloat();
	data.boostMovementSpeedMultiplier = aProperties["boostMovementSpeedMultiplier"].GetFloat();
	data.boostRotationSpeedMultiplier = aProperties["boostRotationSpeedMultiplier"].GetFloat();

	InternalInit(data);
}


//PRIVATE FUNCTIONS:

void PlayerControllerComponent::InternalInit(const PlayerControllerData& aInitData)
{
	myRotationAccelerationCap = aInitData.keyboardRotationSpeed / 3.f;

	myDriftMovementSpeed = aInitData.movementSpeed;
	myDriftRotationSpeed = aInitData.keyboardRotationSpeed - myRotationAccelerationCap;

	myCurrentMovementSpeed = aInitData.movementSpeed;
	myCurrentRotationSpeed = aInitData.keyboardRotationSpeed;

	myBoostMovementSpeed = myDriftMovementSpeed * aInitData.boostMovementSpeedMultiplier;
	myBoostRotationSpeed = (aInitData.keyboardRotationSpeed * aInitData.boostRotationSpeedMultiplier) - myRotationAccelerationCap;

	myMouseRotationSpeed = aInitData.mouseRotationSpeed;

	InitMovementStates();

	myFirstPersonCameraController = nullptr;
}

//Set all movement state flags to false for initialization purposes
void PlayerControllerComponent::InitMovementStates()
{
	myRotateLeft = false;
	myRotateRight = false;
	myMoveLeft = false;
	myMoveRight = false;
	myMoveForward = false;
	myMoveBackward = false;

	myPitchForward = false;
	myPitchBackward = false;
	myRollLeft = false;
	myRollRight = false;
	myMoveDown = false;
	myMoveUp = false;

	myBoosting = false;
}

void PlayerControllerComponent::SetIsBoosting(const bool aIsBoosting)
{
	myBoosting = aIsBoosting;

	//Uncomment movement speed change below to disable gradual acceleration in favor of instant boost speed on/off
	if (aIsBoosting == true)
	{
		//myCurrentMovementSpeed = myBoostMovementSpeed;
		myCurrentRotationSpeed = myBoostRotationSpeed;
	}
	else
	{
		//myCurrentMovementSpeed = myDriftMovementSpeed;
		myCurrentRotationSpeed = myDriftRotationSpeed;
	}
}

void PlayerControllerComponent::UpdateMouseOrientation(const SB::Time &aDeltaTime)
{
	SB::Vector2f moveAmount = myRotationDelta * MIN(1.f, aDeltaTime.InSeconds() * 4.f);

	myRotationDelta -= moveAmount;

	moveAmount /= 500.f; //Manual adjustment to bring mouse rotation to more appropriate base levels
	moveAmount *= myMouseRotationSpeed;
	myObject->GetRotation().RotateAroundLocalY(moveAmount.x);
	myObject->GetRotation().RotateAroundLocalX(moveAmount.y);
}

void PlayerControllerComponent::UpdateAcceleration(const SB::Time& aDeltaTime)
{
	//Update movement acceleration
	const float AccelerationSpeed = (myBoostMovementSpeed - myDriftMovementSpeed) / 1.f;
	const float DecelerationSpeed = AccelerationSpeed * 2.f;

	if (myBoosting == true)
	{
		if (myCurrentMovementSpeed < myBoostMovementSpeed)
		{
			myCurrentMovementSpeed += AccelerationSpeed * aDeltaTime.InSeconds();

			if (myCurrentMovementSpeed > myBoostMovementSpeed)
				myCurrentMovementSpeed = myBoostMovementSpeed;
		}
	}
	else
	{
		if (myCurrentMovementSpeed > myDriftMovementSpeed)
		{
			myCurrentMovementSpeed -= DecelerationSpeed * aDeltaTime.InSeconds();

			if (myCurrentMovementSpeed < myDriftMovementSpeed)
				myCurrentMovementSpeed = myDriftMovementSpeed;
		}
	}


	//Update rotation acceleration
	float currentRotateSpeedCap = GetCurrentRotateAccelerationCap();
	float currentRotateSpeedBase = GetCurrentRotateAccelerationBase();
	const float RotateAccelerationSpeed = (currentRotateSpeedCap - currentRotateSpeedBase) / 1.f;
	if (GetIsRotating() == false)
	{
		myCurrentRotationSpeed = currentRotateSpeedBase;
		/*
		if (myCurrentRotationSpeed > currentRotateSpeedBase)
		{
		myCurrentRotationSpeed -= RotateAccelerationSpeed * aDeltaTime.InSeconds();
		if (myCurrentRotationSpeed < currentRotateSpeedBase)
		myCurrentRotationSpeed = currentRotateSpeedBase;
		}
		*/
	}
	else
	{
		if (myCurrentRotationSpeed < currentRotateSpeedCap)
		{
			myCurrentRotationSpeed += RotateAccelerationSpeed * aDeltaTime.InSeconds();
			if (myCurrentRotationSpeed > currentRotateSpeedCap)
				myCurrentRotationSpeed = currentRotateSpeedCap;
		}
	}
}

bool PlayerControllerComponent::GetIsMoving() const
{
	return (myMoveUp == true || myMoveDown == true || myMoveForward == true || myMoveBackward == true || myMoveLeft == true || myMoveRight == true);
}

bool PlayerControllerComponent::GetIsRotating() const
{
	return (myRotateLeft == true || myRotateRight == true || myRollLeft == true || myRollRight == true || myPitchForward == true || myPitchBackward == true);
}

bool PlayerControllerComponent::GetIsStrafing() const
{
	return (myMoveLeft == true || myMoveRight == true || myMoveUp == true || myMoveDown == true);
}

float PlayerControllerComponent::GetCurrentRotateAccelerationCap() const
{
	if (myBoosting == false)
	{
		return myDriftRotationSpeed + myRotationAccelerationCap;
	}
	
	return myBoostRotationSpeed + myRotationAccelerationCap;
}

float PlayerControllerComponent::GetCurrentRotateAccelerationBase() const
{
	if (myBoosting == false)
	{
		return myDriftRotationSpeed;
	}

	return myBoostRotationSpeed;
}

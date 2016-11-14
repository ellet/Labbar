#include "stdafx.h"
#include "PlayerControllerComponent.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Camera/CameraShakeMessage.h"
#include "Engine/Scene/Scene.h"
#include "Engine/SoundManager/SoundManager.h"
#include "Engine/Camera/Controllers/FirstPersonCameraController.h"
#include <Engine/Component/ModelComponent.h>
#include <Engine/Physics/PhysicsComponent.h>
#include <Engine/Component/Collider/ColliderComponent.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include "Game/GenericGameMessages.h"
#include <Engine/Sprite/SpriteEffect.h>
#include <Engine/Rendering/SpriteRenderer.h>
#include "../Component/Health/HealthComponent.h"
#include "SpaceGameCameraController.h"
#include <Engine/Debugging/CommandLineParameters.h>
#include <Engine/Streak/StreakComponent.h>
#include <Engine/Streak/StreakLogic.h>

class EnemyComponent;

struct WarpDriveData
{
	SB::Vector2f resolution;
	float timer;
	float junk;
};

PlayerControllerComponent::PlayerControllerComponent()
{
	myStreakRoot = nullptr;

	InitPlayerData();

	myGameAreaCenterPosition = SB::Vector3f::Zero;
	myGameAreaRadius = 25.f;

	myFirstPersonCameraController = nullptr;

	myRestrictPlayer = false;
	myPlayerHitEnemyFlag = false;

	myPlayerIsEntering = true;
	myMoveToNextLevel = false;
	myWarpDriveTimer = 0.f;
	myCShakeHyperJump = 0.f;
	myCShakePlayerEnterJump = 0.f;

	// Disable intro if starting from unity
	if (SB::CommandLineParameters::GetInstance().GetFirstValue("level", "") != "")
	{
		myPlayerIsEntering = false;
	}

	myFromBoostTransitionMultiplier = 0.f;
	myEnableNextLevel = false;
}

void PlayerControllerComponent::Initialize()
{
	myFirstPersonCameraController = std::make_shared<SpaceGameCameraController>(myObject);

	myThirdPersonNode = myObject->GetScene().CreateGameObject("Third Person Node");
	myThirdPersonNode->SetPosition(SB::Vector3f(0.f, 10.f, -40.f));
	myThirdPersonNode->SetParent(myObject->AsPointer());
	myThirdPersonNode->Initialize();
	myThirdPersonCameraController = std::make_shared<SpaceGameCameraController>(&*myThirdPersonNode);

	myObject->AddEventSubscriber(SB::EventSubscriber<ShotHitEvent>::GetTypeIndex(), SB::EventSubscriber<ShotHitEvent>::GetInstanceIndex());

	myObject->SetIdentifier("Player");
	myCockpit = myObject->GetScene().CreateAndAddModel("Cockpit", "Assets/Models/Player/Cockpit/cockpit.fbx", SB::Vector3f(0.f, 0.f, 0.f), SB::Vector3f::One);
	myFirstPersonModels.Add(&*myCockpit->GetComponent<SB::ModelComponent>(0));

	myCockpit->SetParent(myObject->AsPointer());
	myCockpit->GetComponent<SB::ModelComponent>()->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * SB::Matrix44f::CreateRotateAroundY(Pi));

	{
		SB::ComponentPtr<SB::ModelComponent> mc = myCockpit->CreateComponent<SB::ModelComponent>();
		mc->SetModel("Assets/Models/Player/CockpitFrame/cockpitFrame.fbx");
		mc->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * SB::Matrix44f::CreateRotateAroundY(Pi));
		myFirstPersonModels.Add(&*mc);
	}

	{
		SB::ComponentPtr<SB::ModelComponent> mc = myCockpit->CreateComponent<SB::ModelComponent>();
		mc->SetModel("Assets/Models/Player/Interceptor/interceptor.fbx");
		mc->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * SB::Matrix44f::CreateRotateAroundY(Pi));
		mc->Prepare(true);
		myThirdPersonModels.Add(&*mc);
	}

	myCockpit->Initialize();

	for (unsigned short i = 0; i < myFirstPersonModels.Size(); i++)
	{
		myFirstPersonModels[i]->DisableAutomaticRender();
	}

	for (unsigned short i = 0; i < myThirdPersonModels.Size(); i++)
	{
		myThirdPersonModels[i]->DisableAutomaticRender();
	}

	GetGameObject().GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::ePlayer);
	GetGameObject().GetComponent<SB::ColliderComponent>()->SetCollisionFilter(CollisionFilter::eEnemy | CollisionFilter::eEnvironment);

	myOutercrosshairSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Gui/Muspekare/sight.dds"));
	myInnercrosshairSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Gui/Muspekare/innersight.dds"));
	myHitMarkerSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Gui/Muspekare/PlayerHitMarker.dds"));

	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();
	if (myPhysicsComponent == nullptr)
	{
		Error("PlayerControllerComponent requires a PhysicsComponent to be attached on the same object!");
	}

	myNoiseTexture = SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Textures/noise2.dds");
	myWarpdriveExitEffect = std::make_shared<SB::SpriteEffect>("shaders/warpdrive/warpdrive.fx", "PShaderExiting");
	myWarpdriveEnterEffect = std::make_shared<SB::SpriteEffect>("shaders/warpdrive/warpdrive.fx", "PShaderEntering");
	myWarpDriveCBuffer = std::make_shared<SB::ConstantBuffer<WarpDriveData>>();

	mySpawnPosition = myObject->GetPosition();
}

void PlayerControllerComponent::OnRemoved()
{
	myStreakRoot = nullptr;
	myCockpit = nullptr;
}

PlayerControllerComponent::~PlayerControllerComponent()
{
}

void PlayerControllerComponent::Update(const SB::Time& aDeltaTime)
{
	myFromBoostTransitionMultiplier += aDeltaTime.InSeconds() * 8.f;
	if (myFromBoostTransitionMultiplier > 1.f)
	{
		myFromBoostTransitionMultiplier = 1.f;
	}

	CalculateLocalVelocity(aDeltaTime);

	if (myMoveToNextLevel == true)
	{
		myWarpDriveTimer += aDeltaTime;
		float time = myWarpDriveTimer.InSeconds();

		if (time >= 4.f)
		{
			SB::PostMaster::Post(ProgressToNextLevelMessage()); //LEVEL CLEAREEED
		}

		float warpSpeed = 0.f;
		const float zoomInAmount = 0.1f;

		if (time > 1.0f)
		{
			SB::PostMaster::Post(SB::CameraShakeMessage(myCShakeHyperJump, 5.f));
			warpSpeed = (1.f + std::sinf(-HalfPi + min(1.f, (time - 1.0f) * 2.f) * HalfPi)) * 500.f;
			myFirstPersonCameraController->SetFoVFactor((1.f - zoomInAmount) + (warpSpeed / 500.f) * (0.25f + zoomInAmount));
		}
		else
		{
			float p = time / 1.0f;
			myFirstPersonCameraController->SetFoVFactor(1.f - (1.f + std::sinf(-HalfPi + p * Pi)) / 2.f * zoomInAmount);
		}

		myPhysicsComponent->SetSpeed(0.f);
		myPhysicsComponent->SetObjectPosition(myObject->GetPosition() + myObject->GetScene().GetCamera().GetOrientation().GetForward() * warpSpeed * aDeltaTime.InSeconds());
		return;
	}
	else if (myPlayerIsEntering == true)
	{
		myWarpDriveTimer += aDeltaTime;
		float time = myWarpDriveTimer.InSeconds();

		if (time >= 2.5f)
		{
			myPlayerIsEntering = false;
			myWarpDriveTimer = 0.f;
			myPhysicsComponent->SetObjectPosition(mySpawnPosition);
			myFirstPersonCameraController->SetFoVFactor(1.f);
			return;
		}
		SB::PostMaster::Post(SB::CameraShakeMessage(myCShakePlayerEnterJump * (1.f - time / 2.5f), 0.5f));

		float p = time / 2.5f;
		myFirstPersonCameraController->SetFoVFactor(1.25f - max(0.f, time - 2.0f) * .5f);

		SB::Vector3f warpVector = SB::Vector3f(0.f, 0.f, 500.f * 2.5f) * myObject->GetScene().GetCamera().GetOrientation();

		myPhysicsComponent->SetObjectPosition(mySpawnPosition - warpVector * std::sinf((1.f - p) * HalfPi));
		return;
	}

	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		myBoosting = false;
		return;
	}

	UpdateMouseOrientation(aDeltaTime);

	float movementAcceleration = myMoveAcceleration; // moveAcceleration

	bool forward = myMoveForward && !myMoveBackward;
	bool backward = myMoveBackward && !myMoveForward;
	bool left = myMoveLeft && !myMoveRight;
	bool right = myMoveRight && !myMoveLeft;
	bool up = myMoveUp && !myMoveDown;
	bool down = myMoveDown && !myMoveUp;

	if (myBoosting == true)
	{
		SB::PostMaster::Post(SB::CameraShakeMessage(myCShakeBoost, 0.5f));
		forward = true;
		movementAcceleration = myBoostAcceleration;
	}

	if (forward)
	{
		myVelocity += (myObject->GetRotation().GetForward() * movementAcceleration * aDeltaTime.InSeconds());
	}

	if (myBoosting == false)
	{
		if (backward)
		{
			myVelocity += (myObject->GetRotation().GetBackward() * movementAcceleration * aDeltaTime.InSeconds());
		}

		if (left)
		{
			myVelocity += myObject->GetRotation().GetLeft() * movementAcceleration * aDeltaTime.InSeconds();
		}
		if (right)
		{
			myVelocity += myObject->GetRotation().GetRight() * movementAcceleration * aDeltaTime.InSeconds();
		}

		if (up)
		{
			myVelocity += myObject->GetRotation().GetUpward() * movementAcceleration * aDeltaTime.InSeconds();
		}
		if (down)
		{
			myVelocity += myObject->GetRotation().GetDownward() * movementAcceleration * aDeltaTime.InSeconds();
		}
	}

	if (myRollLeft)
	{
		myObject->GetRotation().RotateAroundLocalZ(1.f * aDeltaTime.InSeconds());
	}
	if (myRollRight)
	{
		myObject->GetRotation().RotateAroundLocalZ(-1.f * aDeltaTime.InSeconds());
	}

	if (GetIsMoving() == true || GetIsRotating() == true)
	{
		SB::Engine::GetSoundManager().PostEvent("Player_Thruster");
	}
	else
	{
		SB::Engine::GetSoundManager().PostEvent("Stop_Thruster");
	}
	SB::Engine::GetSoundManager().SetListenerPosition(myObject->GetPosition(), myObject->GetRotation().GetForward());
	ApplyVelocity(aDeltaTime);

	RotatePlayerModel();
}

void PlayerControllerComponent::ActivateFirstPersonCamera()
{
	myObject->GetScene().PushCameraController(myFirstPersonCameraController);
}

void PlayerControllerComponent::ActivateThirdPersonCamera()
{
	myObject->GetScene().PushCameraController(myThirdPersonCameraController);
}

void PlayerControllerComponent::DebugRender() const
{
	SB::Engine::GetDebugDrawer().RenderSphere(myGameAreaCenterPosition, myGameAreaRadius, SB::Vector4f(1.f, 1.f, 0.f, 1.f));
}

SB::Quaternion PlayerControllerComponent::GetAimDirection()
{
	SB::Quaternion cameraOrientation = myObject->GetScene().GetCamera().GetOrientation();

	SB::Vector2f crosshairLocation = GetCrosshairLocation();
	crosshairLocation /= SB::Vector2f(1280.f, 720.f);
	crosshairLocation *= 2.f;
	crosshairLocation -= SB::Vector2f::One;
	crosshairLocation.y *= -1.f;

	SB::Vector3f cameraSpaceAim = myObject->GetScene().GetCamera().ScreenToWorld(SB::Vector3f(crosshairLocation.x, crosshairLocation.y, 0.5f));
	//& SB::Vector3f cameraObjectDelta = myObject->GetWorldPosition() - myObject->GetScene().GetCamera().GetPosition();
	//& cameraSpaceAim

	SB::Quaternion aim = SB::Quaternion::CreateFromVectorsYlf(myObject->GetScene().GetCamera().GetPosition(), cameraSpaceAim, cameraOrientation.GetUpward());

	return aim;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const DrawCrosshairEvent& aMessage)
{
	if (myMoveToNextLevel == true)
	{
		return SB::ReceiveResult::eContinue;
	}

	SB::Vector2f crosshairLocation = GetCrosshairLocation();

	myOutercrosshairSprite.SetPosition(crosshairLocation);
	myOutercrosshairSprite.SetOrigin(myOutercrosshairSprite.GetTextureRectSize() / 2.f);
	myOutercrosshairSprite.Render();

	myInnercrosshairSprite.SetPosition(crosshairLocation);
	myInnercrosshairSprite.SetOrigin(myInnercrosshairSprite.GetTextureRectSize() / 2.f);
	myInnercrosshairSprite.Render();

	if (myPlayerHitEnemyFlag == true)
	{
		if (myHitMarkerTimer.GetElapsedTime() > 0.1f)
		{
			myPlayerHitEnemyFlag = false;
		}

		myHitMarkerSprite.SetPosition(crosshairLocation);
		myHitMarkerSprite.SetOrigin(myHitMarkerSprite.GetTextureRectSize() / 2.f);
		myHitMarkerSprite.Render();
	}


	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const DrawWarpDriveEvent& aMessage)
{
	if (myWarpDriveTimer > 0.f)
	{
		myWarpDriveCBuffer->UpdateData(WarpDriveData
		{
			SB::Engine::GetRenderer().GetRenderTargetResolution(),
			myWarpDriveTimer.InSeconds(),
			0.f
		});
		myWarpDriveCBuffer->BindToPS(1);

		SB::Engine::GetRenderer().GetSpriteRenderer().RenderFullscreenQuad(myNoiseTexture, myPlayerIsEntering ? myWarpdriveEnterEffect : myWarpdriveExitEffect);
	}

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const DrawCockpitEvent& aMessage)
{
	if (IsFirstPersonCameraActive())
	{
		for (unsigned short i = 0; i < myFirstPersonModels.Size(); i++)
		{
			myFirstPersonModels[i]->TriggerRender();
		}
	}
	else
	{
		for (unsigned short i = 0; i < myThirdPersonModels.Size(); i++)
		{
			myThirdPersonModels[i]->TriggerRender();
		}
	}

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::AnyKeyDownMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}


	switch (aMessage.key)
	{
	case SB::KeyboardKey::eF5:
		SB::PostMaster::Post(SaveLevelMessage());

		break;
	case SB::KeyboardKey::eF8:
		LoadSave();
		break;
	case SB::KeyboardKey::eReturn:
		if (myEnableNextLevel == true)
		{
			myMoveToNextLevel = true;
			myObject->GetScene().GetGUI()->GetGUIElement("WarpPrompt")->SetActive(false);
			myEnableNextLevel = false;
		}
		break;
	case SB::KeyboardKey::eEscape:
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::ePauseMenu, SB::eSceneType::eSub, nullptr));
		break;
	case SB::KeyboardKey::eO:
		myMoveToNextLevel = true;
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

	case SB::KeyboardKey::eControl:
		myMoveDown = true;
		break;
	case SB::KeyboardKey::eShift:
		myMoveUp = true;
		break;

	case SB::KeyboardKey::eSpace:
		myBoosting = !myBoosting;
		if (myBoosting == false)
		{
			RemoveBoostStreaks();
			myFromBoostTransitionMultiplier = 0.25f;
		}
		else
		{
			CreateBoostStreaks();
		}
		break;

	case SB::KeyboardKey::eC:
		ToggleCamera();
		break;
	}
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::RawMouseMoveMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true || myMoveToNextLevel == true || myPlayerIsEntering == true)
	{
		return SB::ReceiveResult::eContinue;
	}


	myRotationDelta += SB::Vector2f(static_cast<float>(aMessage.deltaX), static_cast<float>(aMessage.deltaY));

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const SB::AnyKeyUpMessage& aMessage)
{
	if (myObject->GetComponent<HealthComponent>()->GetIsDead() == true)
	{
		return SB::ReceiveResult::eContinue;
	}


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

	case SB::KeyboardKey::eControl:
		myMoveDown = false;
		break;
	case SB::KeyboardKey::eShift:
		myMoveUp = false;
		break;
	}
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult PlayerControllerComponent::Receive(const LevelClearedMessage& aMessage)
{
	myEnableNextLevel = true;
	myObject->GetScene().GetGUI()->GetGUIElement("WarpPrompt")->SetActive(true);
	//myMoveToNextLevel = true;
	return SB::ReceiveResult::eContinue;
}


void PlayerControllerComponent::RecieveEvent(const ShotHitEvent& aEvent)
{
	if (aEvent.myObjectHit->GetComponentCount<EnemyComponent>() > 0)
	{
		myPlayerHitEnemyFlag = true;
		myHitMarkerTimer.Restart();
		SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	}
}

void PlayerControllerComponent::LoadData(SB::DataNode aProperties)
{
	PlayerControllerData data;

	data.restrictMovement = aProperties["RestrictPlayer"].GetBool();
	data.GameAreaCenterPosition = SB::Vector3f(aProperties["CenterPosition"][0].GetFloat(), aProperties["CenterPosition"][1].GetFloat(), aProperties["CenterPosition"][2].GetFloat());
	data.GameAreaRadius = aProperties["GameAreaRadius"].GetFloat();


	InternalInit(data);
}

void PlayerControllerComponent::ToJson() const
{
	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteObject("properties");

	serializer.WriteNode("RestrictPlayer", myRestrictPlayer);
	serializer.WriteNode("CenterPosition", myGameAreaCenterPosition);
	serializer.WriteNode("GameAreaRadius", myGameAreaRadius);

	serializer.StepOut();

	serializer.WriteNode("type", "PlayerControllerComponent");
}

void PlayerControllerComponent::LoadSave() const
{
	SB::Data::ClearDocumentFromCache(SB::Engine::GetJsonSerializer().GetSaveDataPath());
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	//Get last save, be it scene start or actual save file
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, SB::Engine::GetJsonSerializer().GetSaveDataPath()));
}

void PlayerControllerComponent::ToggleCamera()
{
	if (IsThirdPersonCameraActive())
	{
		myObject->GetScene().PopCameraController();
	}
	else if (IsFirstPersonCameraActive())
	{
		myObject->GetScene().PushCameraController(myThirdPersonCameraController);
	}
}

bool PlayerControllerComponent::IsFirstPersonCameraActive() const
{
	return myObject->GetScene().IsCameraControllerActive(myFirstPersonCameraController);
}

bool PlayerControllerComponent::IsThirdPersonCameraActive() const
{
	return myObject->GetScene().IsCameraControllerActive(myThirdPersonCameraController);
}

void PlayerControllerComponent::CalculateLocalVelocity(const SB::Time & aDeltaTime)
{
	myLocalVelocity = (myObject->GetScene().GetCamera().GetOrientation() * myVelocity);

	SB::Vector3f smoothingDelta = mySmoothLocalVelocity - myLocalVelocity;
	const float originalLength = smoothingDelta.Length();

	if (originalLength == 0.f)
	{
		return;
	}

	float newLength = originalLength;

	newLength -= aDeltaTime.InSeconds() * 100.f;
	
	if (newLength < 0.f)
	{
		newLength = 0.f;
	}

	mySmoothLocalVelocity = myLocalVelocity + smoothingDelta / originalLength * newLength;
}

//PRIVATE FUNCTIONS:

void PlayerControllerComponent::RotatePlayerModel()
{
	SB::Vector3f localVelocity = mySmoothLocalVelocity / myMaxMoveSpeed;

	SB::Quaternion q;

	float cockpitRotationStrength = 1.f;

	bool firstPerson = IsFirstPersonCameraActive();
	if (firstPerson == true)
	{
		q.RotateAroundLocalZ(-myRotationDelta.x * 0.0005f - localVelocity.x * 0.1f);
		q.RotateAroundLocalX(myRotationDelta.y * 0.0002f - localVelocity.y * 0.05f);
		q.RotateAroundLocalY(Pi);
		myObject->GetScene().FindObject("Player_WeaponRoot")->SetRotation(q);

		q = SB::Quaternion();
	}
	else
	{
		cockpitRotationStrength = myBoosting ? 10.f : 5.f;
		localVelocity *= 3.f;

		SB::Vector3f cameraOffset = SB::Vector3f(myRotationDelta.x * 0.01f - localVelocity.x,
		                                         -myRotationDelta.y * 0.01f - localVelocity.y, -localVelocity.z);

		cameraOffset = cameraOffset * myObject->GetScene().GetCamera().GetOrientation();

		myThirdPersonCameraController->SetPlayerControllerDynamicOffset(cameraOffset);
	}

	q.RotateAroundLocalZ((-myRotationDelta.x * 0.0005f - localVelocity.x * 0.1f) * 0.25f * cockpitRotationStrength);
	q.RotateAroundLocalX((myRotationDelta.y * 0.0002f - localVelocity.y * 0.05f) * 0.25f * cockpitRotationStrength);

	myCockpit->SetRotation(q);
}

void PlayerControllerComponent::InternalInit(const PlayerControllerData& aInitData)
{
	myRestrictPlayer = aInitData.restrictMovement;

	myGameAreaCenterPosition = aInitData.GameAreaCenterPosition;
	myGameAreaRadius = aInitData.GameAreaRadius;

	InitPlayerData();

	myFirstPersonCameraController = nullptr;
}

//Set all movement state flags to false for initialization purposes
void PlayerControllerComponent::InitPlayerData()
{
	myMoveLeft = false;
	myMoveRight = false;
	myMoveForward = false;
	myMoveBackward = false;
	myMoveDown = false;
	myMoveUp = false;

	myRollLeft = false;
	myRollRight = false;

	myBoosting = false;

	myMaxMoveSpeed = 20.f;
	myMaxBoostSpeed = 60.f;

	SB::DataDocument doc;
	SB::Data::Open("Assets/Data/Player/player.json", doc);
	myMaxMoveSpeed = doc["moveMaxSpeed"].GetFloat();
	myMaxBoostSpeed = doc["boostMaxSpeed"].GetFloat();

	myMoveAcceleration = doc["moveAcceleration"].GetFloat();
	myBoostAcceleration = doc["boostAcceleration"].GetFloat();

	myBoostTurnSpeed = doc["boostTurnSpeed"].GetFloat();
	myRotationSensitivity = doc["rotationSensitivity"].GetFloat();
	myCrosshairMoveAmount = doc["crosshairMoveAmount"].GetFloat();

	myMoveNormalizeCrosshairSpeed = doc["moveNormalizeCrosshairSpeed"].GetFloat();

	myCShakeHyperJump = doc["cShakeHyperJump"].GetFloat();
	myCShakePlayerEnterJump = doc["cShakePlayerEnterJump"].GetFloat();
	myCShakeBoost = doc["cShakeBoost"].GetFloat();
}

void PlayerControllerComponent::UpdateMouseOrientation(const SB::Time& aDeltaTime)
{
	SB::Vector2f moveAmount = myRotationDelta * MIN(1.f, aDeltaTime.InSeconds() * 4.f) * myFromBoostTransitionMultiplier;

	if (myBoosting == false)
	{
		float length = myRotationDelta.Length();
		length -= moveAmount.Length();
		if (length < 0.f)
		{
			length = 0.f;
		}
		myRotationDelta = myRotationDelta.GetNormalized() * length * myMoveNormalizeCrosshairSpeed;
	}
	else
	{
		moveAmount *= myBoostTurnSpeed;
	}

	moveAmount *= (1.f / 500.f) * myRotationSensitivity; //Manual adjustment to bring mouse rotation to more appropriate base levels
	myObject->GetRotation().RotateAroundLocalY(moveAmount.x);
	myObject->GetRotation().RotateAroundLocalX(moveAmount.y);
}


bool PlayerControllerComponent::GetIsMoving() const
{
	return (myMoveUp == true || myMoveDown == true || myMoveForward == true || myMoveBackward == true || myMoveLeft == true || myMoveRight == true);
}

bool PlayerControllerComponent::GetIsRotating() const
{
	return (myRollLeft == true || myRollRight == true || myRotationDelta.Length() > 10.f);
}

bool PlayerControllerComponent::GetIsStrafing() const
{
	return (myMoveLeft == true || myMoveRight == true || myMoveUp == true || myMoveDown == true);
}

float PlayerControllerComponent::GetMaxSpeed()
{
	return myBoosting ? myMaxBoostSpeed : myMaxMoveSpeed;
}

void PlayerControllerComponent::CreateBoostStreaks()
{
	SB::ObjectPtr streakRoot = myObject->GetScene().CreateGameObject("Streak Root");
	streakRoot->SetParent(myCockpit->AsPointer());
	streakRoot->Initialize();
	myStreakRoot = &*streakRoot;

	SB::GrowingArray<SB::Vector4f> colors;
	SB::GrowingArray<float> sizes;

	colors.Add(SB::Vector4f(255.f / 255.f, 237.f / 255.f, 0.f / 255.f, 1.f));
	colors.Add(SB::Vector4f(255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.f));

	sizes.Add(0.5f);
	sizes.Add(0.f);

	SB::Time totalTime = 0.75f;
	int segments = 40;

	CreateStreakAt(SB::Vector3f(5.08f, 1.41f, -5.24f + 3.f), new SB::UnityStreakLogic(colors, sizes), totalTime.InSeconds() / static_cast<float>(segments), segments);
	CreateStreakAt(SB::Vector3f(-5.08f, 0.56f, -9.39f + 3.f), new SB::UnityStreakLogic(colors, sizes), totalTime.InSeconds() / static_cast<float>(segments), segments);

	sizes.RemoveAll();
	sizes.Add(1.0f);
	sizes.Add(0.f);

	CreateStreakAt(SB::Vector3f(0.f, 0.56f, -9.39f + 3.f), new SB::UnityStreakLogic(colors, sizes), 1.0f / 80.f, 80);
}

void PlayerControllerComponent::RemoveBoostStreaks()
{
	myStreakRoot->Remove();
	myStreakRoot = nullptr;
}

void PlayerControllerComponent::CreateStreakAt(const SB::Vector3f& aOffset, SB::StreakLogic* aStreakLogic, const SB::Time & aTimeBetweenSegments, int aNumberOfSegments)
{
	if (myStreakRoot == nullptr)
	{
		Error("No streak root!");
	}

	SB::ObjectPtr streak = myObject->GetScene().CreateGameObject("Streak");
	streak->SetParent(myStreakRoot->AsPointer());
	streak->SetPosition(aOffset);
	streak->CreateComponent<SB::StreakComponent>()->Setup(aStreakLogic, aTimeBetweenSegments, aNumberOfSegments);
	streak->Initialize();
}

SB::Vector2f PlayerControllerComponent::GetCrosshairLocation()
{
	return SB::Vector2f(1280.f, 720.f) / 2.f + this->myRotationDelta * myCrosshairMoveAmount; // crosshairMoveAmount
}

void PlayerControllerComponent::ApplyVelocity(const SB::Time& aDeltaTime)
{
	float length = myVelocity.Length();
	SB::Vector3f direction = length == 0.f ? SB::Vector3f::Zero : myVelocity.GetNormalized();

	length *= MAX(0.f, 1.f - aDeltaTime.InSeconds() * 4.f);
	if (length > GetMaxSpeed())
	{
		length = GetMaxSpeed();
	}
	myVelocity = direction * length;

	const SB::Vector3f UpdatePosition = GetGameObject().GetPosition() + (myVelocity * aDeltaTime.InSeconds());
	const SB::Vector3f LengthFromGameCenter = UpdatePosition - myGameAreaCenterPosition;

	if (myRestrictPlayer == false || LengthFromGameCenter.Length() < myGameAreaRadius)
	{
		myPhysicsComponent->SetSpeed(length);
		myPhysicsComponent->SetForceDirection(direction);
	}
	else
	{
		myPhysicsComponent->SetSpeed(0);
		myPhysicsComponent->SetForceDirection(SB::Vector3f::Zero);
	}
}

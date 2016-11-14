#pragma once
#include "..\Game\Game\Component\Controller\ControllerComponent.h"
#include "..\Game\DrawCrosshairEvent.h"
#include "../Component/Shooting/Projectiles/ShotHitEvent.h"
#include <Engine/Sprite/SpriteEffect.h>
#include "..\Game\Game\GenericGameMessages.h"
#include <memory>

namespace SB
{
	class StreakLogic;
	class FirstPersonCameraController;
	class ModelComponent;
}

struct PlayerControllerData
{
	float GameAreaRadius;
	bool restrictMovement;
	SB::Vector3f GameAreaCenterPosition;
};

struct WarpDriveData;
class DrawWarpDriveEvent;
class DrawCockpitEvent;
class SpaceGameCameraController;

class PlayerControllerComponent : public SB::Subscriber<LevelClearedMessage>,
	public ControllerComponent, public SB::Subscriber<SB::AnyKeyDownMessage>, public SB::Subscriber<SB::AnyKeyUpMessage>, 
	public SB::Subscriber<SB::RawMouseMoveMessage>, public SB::Subscriber<DrawCrosshairEvent>,
	public SB::EventSubscriber<ShotHitEvent>, public SB::Subscriber<DrawWarpDriveEvent>, public SB::Subscriber<DrawCockpitEvent>
{
public:
	PlayerControllerComponent();
	void Initialize() override;
	void OnRemoved() override;

	virtual ~PlayerControllerComponent() override;
	virtual void Update(const SB::Time& aDeltaTime) override;

	void ActivateFirstPersonCamera();
	void ActivateThirdPersonCamera();

	virtual void DebugRender() const override;

	SB::Quaternion GetAimDirection();
	SB::ReceiveResult Receive(const SB::AnyKeyUpMessage& aMessage) override;
	SB::ReceiveResult Receive(const SB::AnyKeyDownMessage& aMessage) override;
	SB::ReceiveResult Receive(const SB::RawMouseMoveMessage& aMessage) override;

	SB::ReceiveResult Receive(const DrawCrosshairEvent& aMessage) override;
	SB::ReceiveResult Receive(const DrawWarpDriveEvent& aMessage) override;
	SB::ReceiveResult Receive(const DrawCockpitEvent& aMessage) override;
	SB::ReceiveResult Receive(const LevelClearedMessage& aMessage) override;

	void RecieveEvent(const ShotHitEvent & aEvent) override;

	void LoadData(SB::DataNode aProperties) override;
	void ToJson() const override;

	void LoadSave() const;

	void ToggleCamera();
	bool IsFirstPersonCameraActive() const;
	bool IsThirdPersonCameraActive() const;

private:
	void CalculateLocalVelocity(const SB::Time & aDeltaTime);
	void RotatePlayerModel();
	void InternalInit(const PlayerControllerData& aInitData);
	void InitPlayerData();
	void UpdateMouseOrientation(const SB::Time &aDeltaTime);
	bool GetIsMoving() const;
	bool GetIsRotating() const;
	bool GetIsStrafing() const;
	float GetMaxSpeed();
	void CreateBoostStreaks();
	void RemoveBoostStreaks();
	void CreateStreakAt(const SB::Vector3f & aOffset, SB::StreakLogic * aStreakLogic, const SB::Time & aTimeBetweenSegments, int aNumberOfSegments);

	SB::Vector2f GetCrosshairLocation();

	void ApplyVelocity(const SB::Time & aDeltaTime);

	float myFromBoostTransitionMultiplier;

	float myCShakeHyperJump;
	float myCShakePlayerEnterJump;
	float myCShakeBoost;

	SB::GrowingArray<SB::ModelComponent*> myFirstPersonModels;
	SB::GrowingArray<SB::ModelComponent*> myThirdPersonModels;
	
	std::shared_ptr<SpaceGameCameraController> myFirstPersonCameraController;
	std::shared_ptr<SpaceGameCameraController> myThirdPersonCameraController;

	SB::ObjectPtr myCockpit;
	// Local component reference, therefore regular pointer
	
	SB::PhysicsComponent * myPhysicsComponent;
	SB::Vector3f myVelocity;
	SB::Vector3f myLocalVelocity;
	SB::Vector3f mySmoothLocalVelocity;

	SB::Sprite myOutercrosshairSprite;
	SB::Sprite myInnercrosshairSprite;
	
	SB::Sprite myHitMarkerSprite;
	
	SB::Stopwatch myHitMarkerTimer;

	SB::ObjectPtr myThirdPersonNode;

	float myMaxMoveSpeed;
	float myMaxBoostSpeed;

	SB::Vector3f myGameAreaCenterPosition;
	float myGameAreaRadius;

	//Movement/Rotation speed/acceleration:
	SB::Vector2f myRotationDelta;
	
	//Movement/Rotation states:
	bool myMoveLeft;
	bool myMoveRight;
	bool myMoveForward;
	bool myMoveBackward;
	bool myMoveDown;
	bool myMoveUp;

	bool myRestrictPlayer;

	bool myRollLeft;
	bool myRollRight;

	bool myPlayerHitEnemyFlag;
	bool myEnableNextLevel;

	bool myBoosting;
	float myCrosshairMoveAmount;
	float myMoveAcceleration;
	float myBoostAcceleration;
	float myBoostTurnSpeed;
	float myRotationSensitivity;
	float myMoveNormalizeCrosshairSpeed;

	std::shared_ptr<SB::Texture> myNoiseTexture;
	std::shared_ptr<SB::Effect> myWarpdriveExitEffect;
	std::shared_ptr<SB::Effect> myWarpdriveEnterEffect;
	std::shared_ptr<SB::ConstantBuffer<WarpDriveData>> myWarpDriveCBuffer;
	SB::Time myWarpDriveTimer;
	bool myMoveToNextLevel;
	bool myPlayerIsEntering;
	SB::Vector3f mySpawnPosition;

	SB::GameObject * myStreakRoot;
};


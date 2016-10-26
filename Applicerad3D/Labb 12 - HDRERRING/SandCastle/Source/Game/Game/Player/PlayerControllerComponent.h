#pragma once
#include "..\Game\Game\Component\Controller\ControllerComponent.h"
#include "..\Game\DrawCrosshairEvent.h"

namespace SB
{
	class FirstPersonCameraController;
}

struct PlayerControllerData
{
	float movementSpeed;
	float mouseRotationSpeed;
	float keyboardRotationSpeed;
	float boostMovementSpeedMultiplier;
	float boostRotationSpeedMultiplier;
};

class PlayerControllerComponent : public ControllerComponent, public SB::Subscriber<SB::AnyKeyDownMessage>, public SB::Subscriber<SB::AnyKeyUpMessage>, public SB::Subscriber<SB::RawMouseMoveMessage>, public SB::Subscriber<DrawCrosshairEvent>
{
public:
	PlayerControllerComponent();
	void Initialize() override;
	virtual ~PlayerControllerComponent() override;

	virtual void Update(const SB::Time& aDeltaTime) override;

	void ActivateFirstPersonCamera();

	SB::ReceiveResult Receive(const DrawCrosshairEvent& aMessage) override;
	SB::ReceiveResult Receive(const SB::AnyKeyUpMessage& aMessage) override;
	SB::ReceiveResult Receive(const SB::AnyKeyDownMessage& aMessage) override;
	SB::ReceiveResult Receive(const SB::RawMouseMoveMessage& aMessage) override;

	void LoadData(SB::DataNode aProperties) override;

private:
	void InternalInit(const PlayerControllerData& aInitData);
	void InitMovementStates();
	void SetIsBoosting(const bool aIsBoosting);
	void UpdateMouseOrientation(const SB::Time &aDeltaTime);
	void UpdateAcceleration(const SB::Time& aDeltaTime);
	bool GetIsMoving() const;
	bool GetIsRotating() const;
	bool GetIsStrafing() const;
	float GetCurrentRotateAccelerationCap() const;
	float GetCurrentRotateAccelerationBase() const;

private:
	std::shared_ptr<SB::FirstPersonCameraController> myFirstPersonCameraController;
	SB::ObjectPtr myCockpit;
	// Local component reference, therefore regular pointer
	SB::PhysicsComponent * myPhysicsComponent;
	SB::Vector3f myVelocity;

	SB::Sprite myOutercrosshairSprite;
	SB::Sprite myInnercrosshairSprite;

	float myMaxMoveSpeed;
	float myMaxBoostSpeed;

	//Movement/Rotation speed/acceleration:
	SB::Vector2f myRotationDelta;
	float myMouseRotationSpeed;

	float myCurrentMovementSpeed;
	float myCurrentRotationSpeed;
	float myDriftMovementSpeed;
	float myDriftRotationSpeed;
	float myBoostMovementSpeed;
	float myBoostRotationSpeed;

	float myRotationAccelerationCap;

	//Movement/Rotation states:
	bool myRotateLeft;
	bool myRotateRight;
	bool myMoveLeft;
	bool myMoveRight;
	bool myMoveForward;
	bool myMoveBackward;

	bool myPitchForward;
	bool myPitchBackward;
	bool myRollLeft;
	bool myRollRight;
	bool myMoveDown;
	bool myMoveUp;

	bool myBoosting;
};


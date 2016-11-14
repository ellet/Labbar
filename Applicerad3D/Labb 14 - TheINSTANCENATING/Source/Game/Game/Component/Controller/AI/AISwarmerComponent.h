#pragma once
#include "AIControllerComponent.h"
namespace SB
{
	class Randomizer;
	class PhysicsComponent;
	struct CollisionEvent;
}

struct ObjectOutOfHealthMessage;
class AIMothershipComponent;
class AISwarmerComponent :
	public AIControllerComponent, public SB::EventSubscriber<SB::CollisionEvent>, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	AISwarmerComponent();
	~AISwarmerComponent();
	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Initialize() override;
	virtual void RecieveEvent(const SB::CollisionEvent & aEvent) override;
	virtual void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;

	virtual void LoadData(SB::DataNode aProperties) override;


	virtual void ToJson() const override;

	_inline void SetMothership(AIMothershipComponent* aMothership, unsigned short aMothershipSlotNumber)
	{
		myMothership = aMothership;
		myMotherShipSlotNumber = static_cast<short>(aMothershipSlotNumber);
	}
	void SetPositionAndRotation(const SB::Vector3f & aPosition, const SB::Quaternion & aRotation);
private:
	void CheckForPlayer();
	void LeaveMothership();
	//void SwarmAroundParent(const SB::Time & aDeltaTime);
	//void LeaveParent();

	SB::Vector3f myVelocityDir;
	SB::PhysicsComponent* myPhysicsComponent;
	AIMothershipComponent* myMothership;
	float mySpeed;
	float myDistanceSqrdToPlayer;
	float myRotationSpeed;
	short myMotherShipSlotNumber;
	bool myUseParentScale;
};


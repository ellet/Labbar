#pragma once
#include "..\AIControllerComponent.h"


class AISwarmerComponent;
class AIMothershipShieldComponent;
struct SwarmerSlot
{
	SB::Vector3f mySlotPosition;
	AISwarmerComponent* mySwarmer;
	float myRespawnTimer;
};
struct ShieldGeneratorSlot
{
	SB::Vector3f mySlotPosition;
	AIMothershipShieldComponent* myShieldGenerator;
};

class AIMothershipComponent :
	public AIControllerComponent
{
public:
	AIMothershipComponent();
	~AIMothershipComponent();

	void Update(const SB::Time & aDeltaTime) override;
	void Initialize() override;
	void LoadData(SB::DataNode aProperties) override;

	virtual void ToJson() const override;

	_inline void SwarmerReportingDeathOrLeave(unsigned short aSlotNumber)
	{
		mySwarmerSlots[aSlotNumber].mySwarmer = nullptr;
	}
	void ShieldsReportingFailure(unsigned short aSlotNumber);
private:
	void SpawnSwarmers(const SB::Time & aDeltaTime);
	void SpawnShieldGenerators();
	void RunDeathEventFunction(const SB::Time & aDeltaTime);
	
	SB::GrowingArray<SwarmerSlot> mySwarmerSlots;
	SB::GrowingArray<ShieldGeneratorSlot> myShieldGenerators;
	SB::Vector3f myVelocityDirection;
	float myUnqiueDeathEventTimer;
	SB::PhysicsComponent * myPhysicsComponent;
	float mySwarmerRespawnTime;
	float myPhaseSpeedMultiplier;
	int mySpawnedSwarmers;
	int myCurrentPhase;
	bool myHasBeenDefeated;
	void UpdateSwarmerPositions(const SB::Time & aDeltaTime);
	void UpdateShieldPositions(const SB::Time & aDeltaTime);
};


#pragma once
#include "Game/Health/HealthMessages.h"

class WaveEncounter;


//Note: Wave will need to subscribe to health changed messages and filter out based on if they have an enemy component, and thus decrease/increase remaining wave health accordingly
class Wave : public SB::JsonObject, public SB::Subscriber<EnemyTakeDamageMessage>, public SB::Subscriber<EnemyRecoverHealthMessage>
{
public:
	Wave(SB::DataNode aProperties);
	~Wave();

	void Initialize();
	void Update(const SB::Time& aDeltaTime);

	void LoadData(SB::DataNode aProperties);
	void ToJson(SB::JsonSerializer& aSerializer) const override;

	inline float GetPercentageRemaining() const
	{
		return myRemainingWaveHealth / myTotalWaveHealth;
	}
	inline bool GetHasEnemiesRemaining() const
	{
		return myRemainingWaveHealth > 0.f;
	}

	SB::ReceiveResult Receive(const EnemyTakeDamageMessage& aMessage) override;
	SB::ReceiveResult Receive(const EnemyRecoverHealthMessage& aMessage) override;

private:
	void SpawnEncounter();
	inline void SetRemainingWaveHealth(const float aValue)
	{
		myRemainingWaveHealth = CLAMP(aValue, 0.f, myTotalWaveHealth);
	}

	SB::GrowingArray<std::shared_ptr<WaveEncounter>> myWaveEncounters;
	SB::Time myWaveTimer; //TODO: Add saving/loading
	float myRemainingWaveHealth;
	float myTotalWaveHealth;
	unsigned short mySpawnCap; //Max # of enemies spawned at once -- 0 = unlimited
};


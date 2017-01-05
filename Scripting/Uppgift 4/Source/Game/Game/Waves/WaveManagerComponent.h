#pragma once
#include "Game/Waves/WaveMessages.h"

class Wave;


class WaveManagerComponent : public SB::BaseComponent, public SB::Subscriber<ActivateSpawnPointMessage>
{
public:
	WaveManagerComponent();
	~WaveManagerComponent();

	virtual void Initialize() override;
	virtual void Update(const SB::Time& aDeltaTime) override;
	virtual void Render(const SB::Camera& aCamera) const override;

	virtual void LoadData(SB::DataNode aProperties) override;
	virtual void ToJson(SB::JsonSerializer& aSerializer) const override;

	SB::ReceiveResult Receive(const ActivateSpawnPointMessage& aMessage) override;

private:
	void AdvanceToNextWave();
	void TriggerArenaCompletion();
	std::string DetermineWaveFeedbackText() const;

	SB::GrowingArray<std::shared_ptr<Wave>> myWaves;
	SB::GrowingArray<SB::ObjectPtr> mySpawnPoints;
	SB::Text myWaveFeedbackText;
	unsigned short myCurrentWave;
	bool myIsCompleted;
};


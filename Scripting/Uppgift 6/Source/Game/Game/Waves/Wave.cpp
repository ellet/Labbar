#include "stdafx.h"
#include "Wave.h"
#include "WaveEncounter.h"



Wave::Wave(SB::DataNode aProperties)
{
	myWaveEncounters.Reserve(32);
	myTotalWaveHealth = 0;
	myRemainingWaveHealth = 0;
	mySpawnCap = 0;

	LoadData(aProperties);
}

Wave::~Wave()
{
}

void Wave::Initialize()
{
	//TODO
}

void Wave::Update(const SB::Time& aDeltaTime)
{
	//TODO: Implement this with enemy health and actual spawning -- for now it's just hardcoded to be done in 2 seconds

	myWaveTimer += aDeltaTime.InSeconds();

	if (myWaveTimer.InSeconds() >= 2.f)
	{
		SetRemainingWaveHealth(0.f);
	}
}

void Wave::LoadData(SB::DataNode aProperties)
{
	for(unsigned short i = 0; i < aProperties["waveEncounters"].Capacity(); ++i)
	{
		myWaveEncounters.Add(std::make_shared<WaveEncounter>(aProperties["waveEncounters"][i]));
		//TODO: Add health to total pool here based on how much health the prefab enemy has
	}

	mySpawnCap = aProperties["spawnCap"].GetUShort();

	if (aProperties.HasMember("totalWaveHealth") == true)
		myTotalWaveHealth = aProperties["totalWaveHealth"].GetFloat();

	if (aProperties.HasMember("remainingWaveHealth") == true)
		myRemainingWaveHealth = aProperties["remainingWaveHealth"].GetFloat();
	else
		myRemainingWaveHealth = myTotalWaveHealth;
	


	//TODO: !!!REMOVE THIS AS SOON AS ENEMIES ARE SPAWNING!!!
	myTotalWaveHealth = 100.f;
	myRemainingWaveHealth = 100.f;

}

void Wave::ToJson(SB::JsonSerializer &aSerializer) const
{
	aSerializer.WriteArray("waveEncounters");
	for(unsigned short i = 0; i < myWaveEncounters.Size(); ++i)
	{
		aSerializer.WriteObject();
		myWaveEncounters[i]->ToJson(aSerializer);
		aSerializer.StepOut();
	}
	aSerializer.StepOut();

	aSerializer.WriteNode("spawnCap", mySpawnCap);
	aSerializer.WriteNode("remainingWaveHealth", myRemainingWaveHealth);
	aSerializer.WriteNode("totalWaveHealth", myTotalWaveHealth);
}


SB::ReceiveResult Wave::Receive(const EnemyTakeDamageMessage& aMessage)
{
	SetRemainingWaveHealth(myRemainingWaveHealth - aMessage.damageAmount);
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult Wave::Receive(const EnemyRecoverHealthMessage& aMessage)
{
	SetRemainingWaveHealth(myRemainingWaveHealth + aMessage.recoverAmount);
	return SB::ReceiveResult::eContinue;
}


//PRIVATE FUNCTIONS:

void Wave::SpawnEncounter()
{
	//TODO: Spawn first in list, then remove it (as a stack)
}

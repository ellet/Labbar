#include "stdafx.h"
#include "WaveEncounter.h"


WaveEncounter::WaveEncounter(SB::DataNode aProperties)
{
	myEnemyPrefab = "";
	mySpawnDelay = 0.f;

	LoadData(aProperties);
}

WaveEncounter::~WaveEncounter()
{
}

void WaveEncounter::Initialize()
{
	//TODO
}

void WaveEncounter::LoadData(SB::DataNode aProperties)
{
	myEnemyPrefab = aProperties["enemyPrefab"].GetString();
	mySpawnDelay = aProperties["spawnDelay"].GetFloat();
	mySpawnPoint.spawnPointIndex = aProperties["spawnPointIndex"].GetUShort();
	mySpawnPoint.randomizeSpawnPoint = aProperties["randomizeSpawnPoint"].GetBool();
}

void WaveEncounter::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("enemyPrefab", myEnemyPrefab);
	aSerializer.WriteNode("spawnDelay", mySpawnDelay);
	aSerializer.WriteNode("spawnPointIndex", mySpawnPoint.spawnPointIndex);
	aSerializer.WriteNode("randomizeSpawnPoint", mySpawnPoint.randomizeSpawnPoint);
}

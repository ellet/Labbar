#pragma once

struct SpawnPoint
{
	SpawnPoint()
	{
		spawnPointIndex = 0;
		randomizeSpawnPoint = false;
	}
	SpawnPoint(const unsigned short aSpawnPointIndex, const bool aRandomizeSpawnPoint)
	{
		spawnPointIndex = aSpawnPointIndex;
		randomizeSpawnPoint = aRandomizeSpawnPoint;
	}

	unsigned short spawnPointIndex;
	bool randomizeSpawnPoint;
};


class WaveEncounter : public SB::JsonObject
{
public:
	WaveEncounter(SB::DataNode aProperties);
	~WaveEncounter();

	void Initialize();

	void LoadData(SB::DataNode aProperties);
	void ToJson(SB::JsonSerializer& aSerializer) const override;

private:
	std::string myEnemyPrefab;
	SpawnPoint mySpawnPoint;
	float mySpawnDelay;
};


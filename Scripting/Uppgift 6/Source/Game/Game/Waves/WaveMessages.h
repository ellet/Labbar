#pragma once

struct ActivateSpawnPointMessage
{
	ActivateSpawnPointMessage(SB::ObjectPtr aSpawnPoint)
	{
		spawnPoint = aSpawnPoint;
	}

	SB::ObjectPtr spawnPoint;
};

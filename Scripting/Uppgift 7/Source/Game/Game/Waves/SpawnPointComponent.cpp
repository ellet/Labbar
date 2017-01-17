#include "stdafx.h"
#include "SpawnPointComponent.h"
#include "Game/Waves/WaveMessages.h"

unsigned short SpawnPointComponent::ourTotalSpawnPointCount = 0;


SpawnPointComponent::SpawnPointComponent()
{
	myIndex = ourTotalSpawnPointCount;
	++ourTotalSpawnPointCount;
}

SpawnPointComponent::~SpawnPointComponent()
{
}

void SpawnPointComponent::Initialize()
{
	ActivateSpawnPoint();
}

void SpawnPointComponent::Render(const SB::Camera& aCamera) const
{
	//TODO: Render a representative model in Debug to display the spawn point
}

void SpawnPointComponent::LoadData(SB::DataNode aProperties)
{
	//TODO
}

void SpawnPointComponent::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("type", "SpawnPointComponent");

	aSerializer.WriteObject("properties");
	aSerializer.StepOut();
}

void SpawnPointComponent::OnRemoved()
{
	--ourTotalSpawnPointCount;
}


//PRIVATE FUNCTIONS:

//Send a message to Wave Manager that we've added a new spawn point to be included in the list used to spawn encounters during waves
void SpawnPointComponent::ActivateSpawnPoint()
{
	SB::PostMaster::Post(ActivateSpawnPointMessage(myObject->AsPointer()));
}
#include "stdafx.h"
#include "CreateDummyNetMessage.h"

#include "ConnectNetMessage.h"
#include "Serialization\SerializeCommands.h"
#include "Serialization\SerializeHelper.h"

CreateDummyNetMessage::CreateDummyNetMessage()
{
	myObjectID = NetworkMessageTypes::eDummyCreate;
}


CreateDummyNetMessage::~CreateDummyNetMessage()
{
}

void CreateDummyNetMessage::DoImporantSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myObjectType);
	SERIALIZE(aStreamType, myGameObjectID);
}

void CreateDummyNetMessage::DoImporantDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myObjectType);
	DESERIALIZE(aStreamType, myGameObjectID);
}

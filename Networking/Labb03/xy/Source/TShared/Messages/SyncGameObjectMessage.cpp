#include "stdafx.h"
#include "SyncGameObjectMessage.h"

#include "ConnectNetMessage.h"
#include "Serialization\SerializeCommands.h"
#include "Serialization\SerializeHelper.h"

SyncGameObjectMessage::SyncGameObjectMessage()
{
	myObjectID = NetworkMessageTypes::eSyncGameObject;
}


SyncGameObjectMessage::~SyncGameObjectMessage()
{
}

void SyncGameObjectMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, X);
	SERIALIZE(aStreamType, Y);
	SERIALIZE(aStreamType, objectID);
}

void SyncGameObjectMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, X);
	DESERIALIZE(aStreamType, Y);
	DESERIALIZE(aStreamType, objectID);
}

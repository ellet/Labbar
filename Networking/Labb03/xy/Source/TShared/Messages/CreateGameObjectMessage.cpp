#include "stdafx.h"
#include "CreateGameObjectMessage.h"

#include "Serialization\SerializeHeader.h"
#include "Serialization\SerializeHelper.h"
#include "Serialization\SerializeCommands.h"

CreateGameObjectMessage::CreateGameObjectMessage()
{
	myObjectID = NetworkMessageTypes::eCreationMessage;
}


CreateGameObjectMessage::~CreateGameObjectMessage()
{
}

void CreateGameObjectMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myID);
	SERIALIZE(aStreamType, myType);
}

void CreateGameObjectMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myID);
	DESERIALIZE(aStreamType, myType);
}

#include "stdafx.h"
#include "GameCodeNetMessage.h"
#include "Serialization\SerializeHeader.h"
#include "Serialization\SerializeHelper.h"
#include "Serialization\SerializeCommands.h"


GameCodeNetMessage::GameCodeNetMessage()
{
	myObjectID = NetworkMessageTypes::eInputMessage;
}


GameCodeNetMessage::~GameCodeNetMessage()
{
}

void GameCodeNetMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myGameMessage);
}

void GameCodeNetMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myGameMessage);
}

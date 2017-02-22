#include "stdafx.h"
#include "ChatNetMessage.h"

#include "Serialization/SerializeHelper.h"
#include "Serialization/SerializeCommands.h"

ChatNetMessage::ChatNetMessage()
{
	myObjectID = NetworkMessageTypes::eMessage;
	mySpeakerName = "Speaker not set";
	myMessage = "Message not set";
}


ChatNetMessage::~ChatNetMessage()
{
}


void ChatNetMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, mySpeakerName);
	SERIALIZE(aStreamType, myMessage);
}

void ChatNetMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, mySpeakerName);
	DESERIALIZE(aStreamType, myMessage);
}

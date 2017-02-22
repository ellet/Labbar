#include "stdafx.h"
#include "NetMessage.h"

#include "Serialization/SerializeHelper.h"
#include "Serialization/SerializeCommands.h"

NetMessage::NetMessage()
{
	myObjectID = NetworkMessageTypes::enumLength;
}

NetMessage::~NetMessage()
{

}

void NetMessage::InternalSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myObjectID);
	SERIALIZE(aStreamType, myTimeStamp);
	SERIALIZE(aStreamType, mySenderID);
	SERIALIZE(aStreamType, myTargetID);

	DoSerialize(aStreamType);
}

void NetMessage::InternalDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myObjectID);
	DESERIALIZE(aStreamType, myTimeStamp);
	DESERIALIZE(aStreamType, mySenderID);
	DESERIALIZE(aStreamType, myTargetID);

	DoDeSerialize(aStreamType);
}



void NetMessage::PackMessage()
{
	InternalSerialize(myStream);

	if (myStream.size() > 512)
	{
		Error("Network message larger then 512 bytes");
	}
}

void NetMessage::UnPackMessage(const char * aMessage, const unsigned short aSize)
{
	StreamType inputStream;
	inputStream.resize(static_cast<size_t>(aSize));
	memcpy(&inputStream[0], aMessage, aSize);

	InternalDeSerialize(inputStream);
}

bool NetMessage::isImportant(const NetworkMessageTypes aMessageType)
{
	return aMessageType > NetworkMessageTypes::eIMPORTANTCUTTOF;
}

bool NetMessage::isImportant()
{
	return isImportant(myObjectID);
}

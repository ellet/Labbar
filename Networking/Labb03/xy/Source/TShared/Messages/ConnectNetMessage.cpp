#include "stdafx.h"
#include "ConnectNetMessage.h"
#include "Serialization\SerializeCommands.h"
#include "Serialization\SerializeHelper.h"


ConnectNetMessage::ConnectNetMessage()
{
	myObjectID = NetworkMessageTypes::eConnection;
	myUserName = "user name not set";
}


ConnectNetMessage::~ConnectNetMessage()
{
}

void ConnectNetMessage::SetUserName(const std::string & aName)
{
	myUserName = aName;
}

void ConnectNetMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myUserName);
}

void ConnectNetMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myUserName);
}

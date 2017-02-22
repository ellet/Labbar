#include "stdafx.h"
#include "DisconnectNetMessage.h"


DisconnectNetMessage::DisconnectNetMessage()
{
	myObjectID = NetworkMessageTypes::eDisconnect;
}


DisconnectNetMessage::~DisconnectNetMessage()
{
}

void DisconnectNetMessage::DoSerialize(StreamType & aStreamType)
{
}

void DisconnectNetMessage::DoDeSerialize(StreamType & aStreamType)
{
}

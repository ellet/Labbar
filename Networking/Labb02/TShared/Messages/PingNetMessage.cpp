#include "stdafx.h"
#include "PingNetMessage.h"


PingNetMessage::PingNetMessage()
{
	myID = NetworkMessageTypes::ePing;
}


PingNetMessage::~PingNetMessage()
{
}

void PingNetMessage::DoSerialize(StreamType & aStreamType)
{	
}

void PingNetMessage::DoDeSerialize(StreamType & aStreamType)
{
}

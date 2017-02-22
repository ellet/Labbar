#include "stdafx.h"
#include "ImportantNetMessage.h"

#include "Serialization\SerializeHeader.h"
#include "Serialization\SerializeHelper.h"
#include "Serialization\SerializeCommands.h"

ImportantNetMessage::ImportantNetMessage()
{

}

ImportantNetMessage::~ImportantNetMessage()
{

}

void ImportantNetMessage::DoImporantSerialize(StreamType & aStreamType)
{

}

void ImportantNetMessage::DoImporantDeSerialize(StreamType & aStreamType)
{

}

void ImportantNetMessage::DoSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myImpID);

	DoImporantSerialize(aStreamType);
}

void ImportantNetMessage::DoDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myImpID);

	DoImporantDeSerialize(aStreamType);
}

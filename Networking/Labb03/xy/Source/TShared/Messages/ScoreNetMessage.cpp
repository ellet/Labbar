#include "stdafx.h"
#include "ScoreNetMessage.h"

#include "ConnectNetMessage.h"
#include "Serialization\SerializeCommands.h"
#include "Serialization\SerializeHelper.h"

ScoreNetMessage::ScoreNetMessage()
{
	myObjectID = NetworkMessageTypes::eScore;
}


ScoreNetMessage::~ScoreNetMessage()
{
}

void ScoreNetMessage::DoImporantSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myScore);
	SERIALIZE(aStreamType, myIsPlayer1);
}

void ScoreNetMessage::DoImporantDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myScore);
	DESERIALIZE(aStreamType, myIsPlayer1);
}

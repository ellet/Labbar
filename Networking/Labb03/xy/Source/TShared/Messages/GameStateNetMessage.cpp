#include "stdafx.h"
#include "GameStateNetMessage.h"

#include "Serialization\SerializeHeader.h"
#include "Serialization\SerializeHelper.h"
#include "Serialization\SerializeCommands.h"


GameStateNetMessage::GameStateNetMessage()
{
	myObjectID = NetworkMessageTypes::eGameStateMessage;
}

GameStateNetMessage::~GameStateNetMessage()
{

}

void GameStateNetMessage::DoImporantSerialize(StreamType & aStreamType)
{
	SERIALIZE(aStreamType, myGameState);
}

void GameStateNetMessage::DoImporantDeSerialize(StreamType & aStreamType)
{
	DESERIALIZE(aStreamType, myGameState);
}

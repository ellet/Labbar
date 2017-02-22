#pragma once
#include "NetMessage.h"
#include "GameCode\Components\ComponentMessages.h"

class GameCodeNetMessage : public NetMessage
{
public:
	GameCodeNetMessage();
	~GameCodeNetMessage();

	CComponentMessageOnInput myGameMessage;

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;
	
};


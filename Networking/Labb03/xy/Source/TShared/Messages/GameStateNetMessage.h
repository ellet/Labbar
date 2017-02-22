#pragma once
#include "ImportantNetMessage.h"
#include "GameCode\GameStates.h"



class GameStateNetMessage : public ImportantNetMessage
{
public:
	GameStateNetMessage();
	~GameStateNetMessage();

	eGameState myGameState;

protected:
	virtual void DoImporantSerialize(StreamType & aStreamType) override;


	virtual void DoImporantDeSerialize(StreamType & aStreamType) override;

};


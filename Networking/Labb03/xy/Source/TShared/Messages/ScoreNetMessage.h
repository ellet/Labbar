#pragma once
#include "NetMessage.h"


class ScoreNetMessage : public NetMessage
{
public:
	ScoreNetMessage();
	~ScoreNetMessage();

	bool myIsPlayer1;
	int myScore;

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;


	virtual void DoDeSerialize(StreamType & aStreamType) override;

};


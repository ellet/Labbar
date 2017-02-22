#pragma once
#include "ImportantNetMessage.h"


class ScoreNetMessage : public ImportantNetMessage
{
public:
	ScoreNetMessage();
	~ScoreNetMessage();

	bool myIsPlayer1;
	int myScore;

protected:

	virtual void DoImporantSerialize(StreamType & aStreamType) override;


	virtual void DoImporantDeSerialize(StreamType & aStreamType) override;

};


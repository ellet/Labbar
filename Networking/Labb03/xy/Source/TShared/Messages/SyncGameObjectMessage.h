#pragma once
#include "NetMessage.h"


class SyncGameObjectMessage : public NetMessage
{
public:
	SyncGameObjectMessage();
	~SyncGameObjectMessage();

	float X;
	float Y;
	unsigned short objectID;

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

};


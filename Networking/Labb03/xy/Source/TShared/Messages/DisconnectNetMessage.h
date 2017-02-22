#pragma once
#include "NetMessage.h"

class DisconnectNetMessage : public NetMessage
{
public:
	DisconnectNetMessage();
	~DisconnectNetMessage();

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

};


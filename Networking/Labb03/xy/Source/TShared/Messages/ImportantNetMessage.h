#pragma once
#include "NetMessage.h"


class ImportantNetMessage : public NetMessage
{
public:
	ImportantNetMessage();
	~ImportantNetMessage();

	unsigned myImpID;

protected:
	virtual void DoImporantSerialize(StreamType & aStreamType);
	virtual void DoImporantDeSerialize(StreamType & aStreamType);

private:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

};


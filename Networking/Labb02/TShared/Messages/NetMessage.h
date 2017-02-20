#pragma once
#include "Serialization/SerializeHeader.h"
#include "NetworkMessageTypes.h"

class NetMessage
{
	friend class NetMessageManager;

public:
	virtual ~NetMessage();

	void PackMessage();
	void UnPackMessage(const char * aMessage, const unsigned short aSize);

	unsigned int GetTimeStamp() const { return myTimeStamp; }
	unsigned short GetSenderID() const { return mySenderID; }
	unsigned short GetTargetID() const { return myTargetID; }

	StreamType myStream;
protected:
	NetMessage();

	unsigned int myTimeStamp;
	unsigned short mySenderID;
	unsigned short myTargetID;
	NetworkMessageTypes myID;

	virtual void DoSerialize(StreamType & aStreamType) = 0;
	virtual void DoDeSerialize(StreamType & aStreamType) = 0;

private:
	void InternalSerialize(StreamType & aStreamType);
	void InternalDeSerialize(StreamType & aStreamType);
};

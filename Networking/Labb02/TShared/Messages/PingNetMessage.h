#pragma once


class PingNetMessage : public NetMessage
{
public:
	PingNetMessage();
	~PingNetMessage();

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

};


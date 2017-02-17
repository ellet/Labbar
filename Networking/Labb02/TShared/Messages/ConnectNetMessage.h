#pragma once


class ConnectNetMessage : public NetMessage
{
public:
	ConnectNetMessage();
	~ConnectNetMessage();

	void SetUserName(const std::string & aName);
	const std::string & GetClientName() const { return myUserName; }

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

private:
	std::string myUserName;
};


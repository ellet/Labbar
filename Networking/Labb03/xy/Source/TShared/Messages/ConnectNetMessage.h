#pragma once
#include "ImportantNetMessage.h"


class ConnectNetMessage : public ImportantNetMessage
{
public:
	ConnectNetMessage();
	~ConnectNetMessage();

	void SetUserName(const std::string & aName);
	const std::string & GetClientName() const { return myUserName; }

protected:
	virtual void DoImporantSerialize(StreamType & aStreamType) override;
	virtual void DoImporantDeSerialize(StreamType & aStreamType) override;

private:
	std::string myUserName;

};


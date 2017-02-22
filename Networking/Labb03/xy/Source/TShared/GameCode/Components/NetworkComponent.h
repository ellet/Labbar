#pragma once
#include "BaseComponent.h"

class NetworkCallback;

class NetworkComponent : public CBaseComponent
{
public:
	NetworkComponent();
	~NetworkComponent();

	void SetCallback(NetworkCallback & aCallback);

	virtual void OnMessage(CComponentMessageBase * aMessage) override;

	static unsigned int myID;
private:
	NetworkCallback * myCallback;
};


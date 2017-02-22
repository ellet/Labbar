#pragma once
#include "GameCode/Components/ComponentMessages.h"
class CGameObject;
class CBaseComponent
{
	friend class CGameObject;
public:
	CBaseComponent(){}
	virtual ~CBaseComponent(){}
	virtual void OnMessage(CComponentMessageBase* /*aMessage*/){}
	void BroadcastMessage(CComponentMessageBase* aMessage);
	virtual void Update(const float /*aTimeDelta*/){}
	virtual void Render(){}

	static unsigned int myID;
protected:

	CGameObject* myOwner;
};

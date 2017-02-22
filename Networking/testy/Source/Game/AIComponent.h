#pragma once

#include "BaseComponent.h"
class CAIComponent : public CBaseComponent
{
public:
	CAIComponent();
	~CAIComponent();
	void Init(class CBall* aBall);
	virtual void Update(float aTimeDelta) override;
	/*static unsigned int GetId();*/
	static unsigned int myID;
private:
	class CBall* myBall;
};


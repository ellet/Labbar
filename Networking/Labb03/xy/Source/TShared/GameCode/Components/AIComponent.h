#pragma once


#include <GameCode\Components\BaseComponent.h>

class CAIComponent : public CBaseComponent
{
public:
	CAIComponent();
	~CAIComponent();
	void Init(class CBall* aBall);
	virtual void Update(const float aTimeDelta) override;
	/*static unsigned int GetId();*/
	static unsigned int myID;
private:
	class CBall* myBall;
};


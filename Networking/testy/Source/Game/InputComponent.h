#pragma once
#include "BaseComponent.h"

namespace Input
{
	class InputWrapper;
}
class CInputComponent : public CBaseComponent
{
public:
	CInputComponent();
	~CInputComponent();
	void Init(Input::InputWrapper* aInputWrapper);
	virtual void Update(float aTimeDelta) override;
	void OnMessage(CComponentMessageBase* aMessage) override;
	/*static unsigned int GetId();*/
	static unsigned int myID;
private:
	Input::InputWrapper* myInputWrapper;
	// maybe send keybord strokes from this class?
};


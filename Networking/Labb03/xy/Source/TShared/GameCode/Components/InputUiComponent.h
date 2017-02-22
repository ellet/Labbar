#pragma once
#include "GameCode\Components\BaseComponent.h"
#include <string>
#include <functional>

namespace DX2D
{
	class CSprite;
	class CText;
}
namespace Input
{
	class InputWrapper;
}

typedef std::function<void(std::string)> callback_function_on_ip_entered;

class CInputUiComponent : public CBaseComponent
{
public:
	CInputUiComponent();
	~CInputUiComponent();
	void Init(Input::InputWrapper* aInputWrapper, callback_function_on_ip_entered aFunc);
	virtual void Update(const float aTimeDelta) override;
	void Render() override;
	void Reset();
	/*static unsigned int GetId();*/
	static unsigned int myID;
private:
	bool IpOk();
	void AcceptIP();
	void AppendNumbers();
	DX2D::CSprite *mySprite;
	DX2D::CText* myText;
	std::string myInputText;
	std::string myInputTextBlinker;
	float myBlinkTimer;
	Input::InputWrapper* myInputWrapper;
	callback_function_on_ip_entered myFunc;
	int myFailBlinker;
	float myFailBlinkTimer;
	bool myAutoFill;
	float myAutoFillTimer;

};


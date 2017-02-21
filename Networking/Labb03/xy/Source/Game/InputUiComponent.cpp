#include "stdafx.h"
#include "InputUiComponent.h"
#include "ComponentIds.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include "..\CommonUtilites\InputWrapper.h"
#include <locale>

unsigned int CInputUiComponent::myID = EComponentIds_CInputUIComponent;

const std::string localhostIP("127.0.0.1");
CInputUiComponent::CInputUiComponent()
{
	myBlinkTimer = 0;
	myFunc = 0;
	myAutoFill = false;
	myFailBlinker = 0;
	myAutoFillTimer = 0;
}


CInputUiComponent::~CInputUiComponent()
{
}

void CInputUiComponent::Init(Input::InputWrapper* aInputWrapper, callback_function_on_ip_entered aFunc)
{
	myFunc = aFunc;
	myInputWrapper = aInputWrapper;
	mySprite = new DX2D::CSprite("sprites/ui.png");
	myText = new DX2D::CText("Text/calibril.ttf_sdf");
	myText->mySize = 1.8f;
	myText->myPosition.Set(0.2f, 0.53f);
	myInputTextBlinker = "_";
	myFailBlinkTimer = 0;
}

void CInputUiComponent::Update(float aTimeDelta)
{
	AppendNumbers();


	myBlinkTimer += aTimeDelta;
	if (myBlinkTimer > 0.2f)
	{
		if (myInputTextBlinker.size() > 0)
		{
			myInputTextBlinker.clear();
		}
		else
		{
			myInputTextBlinker = "_";
		}
		myBlinkTimer = 0.0;
	}

	myText->myText = myInputText + myInputTextBlinker;

	if (myAutoFill)
	{
		myAutoFillTimer += aTimeDelta;
		if (myAutoFillTimer > 0.02f)
		{
			myAutoFillTimer = 0.0f;
			myInputText += localhostIP[myInputText.size()];
			if (myInputText.size() > 9)
			{
				myAutoFill = false;
				AcceptIP();
			}
		}

	}
	if (myInputWrapper->GetKeyPressed(DIK_RETURN))
	{
		if (IpOk())
		{
			AcceptIP();
		}
		else
		{
			if (myInputText.size() == 0)
			{
				myAutoFill = true;
				
			}
			else
			{
				myFailBlinker = 4;
			}
		}
	}

	myText->myColor.Set(1, 1, 1, 1);
	if (myFailBlinker > 0)
	{
		myFailBlinkTimer += aTimeDelta;
		if (myFailBlinkTimer >= 0.05f)
		{
			myFailBlinkTimer = 0.0f;
			myFailBlinker--;
			if (myFailBlinker < 0)
			{
				myFailBlinker = 0;
			}

		}

		if (myFailBlinker % 2 == 0)
		{
			myText->myColor.Set(1, 0, 0, 1);
		}

	}
}


bool CInputUiComponent::IpOk()
{

	size_t n = std::count(myInputText.begin(), myInputText.end(), '.');
	if (n != 3)
	{
		return false;
	}
	if (myInputText.back() == '.')
	{
		return false;
	}
	if (myInputText.front() == '.')
	{
		return false;
	}

	short numbersInARow = 0;
	std::locale loc;

	std::string adress;
	for (int i=0; i< myInputText.size(); i++)
	{
		if (std::isdigit(myInputText[i], loc))
		{
			adress += myInputText[i];
			numbersInARow++;
			if (numbersInARow > 3)
			{
				return false;
			}
		}
		else
		{
			int number = atoi(adress.c_str());
			if (number < 0 || number > 255)
			{
				return false;
			}
			adress.clear();

			numbersInARow = 0;
		}
	}



	return true;
}
void CInputUiComponent::AcceptIP()
{
	if (myFunc)
	{
		myFunc(myInputText);
	}
}

void CInputUiComponent::Render()
{
	myText->Render();
	mySprite->Render();
}

void CInputUiComponent::Reset()
{
	myInputText = "";
	myText->myText = "";
	myText->Render();
	myAutoFill = false;
}

void CInputUiComponent::AppendNumbers()
{
	if (myInputWrapper->GetKeyPressed(DIK_1))
	{
		myInputText.append("1");
	}
	if (myInputWrapper->GetKeyPressed(DIK_2))
	{
		myInputText.append("2");
	}
	if (myInputWrapper->GetKeyPressed(DIK_3))
	{
		myInputText.append("3");
	}
	if (myInputWrapper->GetKeyPressed(DIK_4))
	{
		myInputText.append("4");
	}

	if (myInputWrapper->GetKeyPressed(DIK_5))
	{
		myInputText.append("5");
	}
	if (myInputWrapper->GetKeyPressed(DIK_6))
	{
		myInputText.append("6");
	}
	if (myInputWrapper->GetKeyPressed(DIK_7))
	{
		myInputText.append("7");
	}
	if (myInputWrapper->GetKeyPressed(DIK_8))
	{
		myInputText.append("8");
	}
	if (myInputWrapper->GetKeyPressed(DIK_9))
	{
		myInputText.append("9");
	}
	if (myInputWrapper->GetKeyPressed(DIK_0))
	{
		myInputText.append("0");
	}
	if (myInputWrapper->GetKeyPressed(DIK_PERIOD))
	{
		myInputText.append(".");
	}
	if (myInputText.size() > 0 && myInputWrapper->GetKeyPressed(DIK_BACKSPACE))
	{
		myInputText.pop_back();
	}

}
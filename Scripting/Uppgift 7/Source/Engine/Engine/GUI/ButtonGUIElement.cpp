#include "stdafx.h"
#include "ButtonGUIElement.h"
#include "Engine/GUI/SpriteGUIElement.h"

namespace SB
{
	ButtonGUIElement::ButtonGUIElement()
	{
		
	}

	ButtonGUIElement::ButtonGUIElement(const char * aTexturePath, const Vector2f& aPosition /*= Vector2f::Zero*/, const bool aIsRoot /*= false*/, const Vector2f& aScale /*= Vector2f::One*/, const Vector2f& aSize /*= Vector2f::Zero*/) :
		GUIElement(aPosition, aSize, aIsRoot)
	{
		myFunction = nullptr;
		mySpriteGUI = std::make_shared<SpriteGUIElement>(aTexturePath, aPosition, aIsRoot, aScale, aSize);

		mySize = mySpriteGUI->GetSize() * aScale;
		myPosition = mySpriteGUI->GetPosition();

		
	}

	ButtonGUIElement::~ButtonGUIElement()
	{
	}

	void ButtonGUIElement::Update(const SB::Time &aDeltaTime)
	{
		mySpriteGUI->Update(aDeltaTime);
		GUIElement::Update(aDeltaTime);
	}

	void ButtonGUIElement::Render(const GuiRenderTarget & aRenderTarget)
	{
		mySpriteGUI->Render(aRenderTarget);
		GUIElement::Render(aRenderTarget);
	}

	void ButtonGUIElement::BindClickFunction(std::function<void()> aFunction)
	{
		myFunction = aFunction;	
	}

	void ButtonGUIElement::SetIsHoverActivated(bool aValue)
	{
		mySpriteGUI->SetIsHoverActivated(aValue);
	}

	void ButtonGUIElement::AddButtonChild()
	{
		AddChild(mySpriteGUI);
		mySize = mySpriteGUI->GetSize() * myScale;
		myPosition = mySpriteGUI->GetPosition();
	}

	void ButtonGUIElement::SetName(const std::string & aName)
	{
		GUIElement::SetName(aName);
		mySpriteGUI->SetName(aName + "-button");
	}

	void ButtonGUIElement::SetAnchorPoint(const HorizontalAnchorPoint & aHorizontalPoint, const VerticalAnchorPoint & aVerticalPoint)
	{
		mySpriteGUI->SetAnchorPoint(aHorizontalPoint, aVerticalPoint);
		GUIElement::SetAnchorPoint(aHorizontalPoint, aVerticalPoint);
	}

	bool ButtonGUIElement::LeftClickFunction()
	{
		if (GUIElement::LeftClickFunction() == true)
		{
			if (myFunction != nullptr)
			{
				if (myClickSoundPath != "")
				{
					SB::Engine::GetSoundManager().PostEvent(myClickSoundPath);
				}
				myFunction();
			}
			return false;
		}
		return true;
	}

}
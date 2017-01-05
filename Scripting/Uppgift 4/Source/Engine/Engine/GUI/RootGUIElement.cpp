#include "stdafx.h"
#include "RootGUIElement.h"
#include "Engine/GenericEngineMessages.h"

namespace SB
{
	RootGUIElement::RootGUIElement()
	{
	}

	RootGUIElement::RootGUIElement(const Vector2f & aPosition, const Vector2f & aSize)
		: GUIElement(aPosition, aSize, true)
	{

	} 

	RootGUIElement::~RootGUIElement()
	{
	}

	ReceiveResult RootGUIElement::Receive(const AnyKeyUpMessage & aMessage)
	{
		if (myIsCurrentGUI == false)
		{
			return ReceiveResult::eContinue;
		}
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const AnyKeyDownMessage & aMessage)
	{
		if (myIsCurrentGUI == false)
		{
			return ReceiveResult::eContinue;
		}
		KeybindFunction(aMessage.key);
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const MouseMovedMessage& aMessage)
	{
		if (myIsCurrentGUI == false)
		{
			return ReceiveResult::eContinue;
		}
		ourMousePosition.x = static_cast<float>(aMessage.x);
		ourMousePosition.y = static_cast<float>(aMessage.y);
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const LeftMouseButtonDownMessage& aMessage)
	{
		if (myIsCurrentGUI == false)
		{
			return ReceiveResult::eContinue;
		}
		LeftClickFunction();

		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const WindowSizeChangedMessage& aMessage)
	{
		if (myRenderSize == Vector2f(1080.f * (static_cast<float>(aMessage.myWidth) / static_cast<float>(aMessage.myHeight)), 1080.f))
		{
			return ReceiveResult::eContinue;
		}
		Resize(aMessage.myWidth, aMessage.myHeight);
		return ReceiveResult::eContinue;
	}

	void RootGUIElement::SetMyIsCurrentGUI(bool aValue)
	{
		myIsCurrentGUI = aValue;
		myIsActive = aValue;
	}

	void RootGUIElement::SetPadding(const Vector4f & aPadding)
	{
		myAllowedBoundery.x += aPadding.x;
		myAllowedBoundery.y += aPadding.y;
		myAllowedBoundery.z -= aPadding.z;
		myAllowedBoundery.w -= aPadding.w;
		GUIElement::SetPadding(aPadding);
	}

}

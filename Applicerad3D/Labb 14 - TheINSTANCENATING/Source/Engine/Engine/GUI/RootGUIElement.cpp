#include "stdafx.h"
#include "RootGUIElement.h"

namespace ENGINE_NAMESPACE
{
	RootGUIElement::RootGUIElement()
	{
	}


	RootGUIElement::RootGUIElement(const Vector4f & aBorderPositions)
		: GUIElement(aBorderPositions)
	{

	} 

	RootGUIElement::RootGUIElement(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aSize)
		: GUIElement(aTexturePath, aPosition, Vector2f::One, aSize)
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

	void RootGUIElement::SetMyIsCurrentGUI(bool aValue)
	{
		myIsCurrentGUI = aValue;
	}
}

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

	RootGUIElement::RootGUIElement(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale)
		: GUIElement(aTexturePath, aPosition, aScale)
	{

	}

	RootGUIElement::~RootGUIElement()
	{
	}

	ReceiveResult RootGUIElement::Receive(const AnyKeyUpMessage & aMessage)
	{
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const AnyKeyDownMessage & aMessage)
	{
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const MouseMovedMessage& aMessage)
	{
		ourMousePosition.x = static_cast<float>(aMessage.x);
		ourMousePosition.y = static_cast<float>(aMessage.y);
		return ReceiveResult::eContinue;
	}

	ReceiveResult RootGUIElement::Receive(const LeftMouseButtonDownMessage& aMessage)
	{
		LeftClickFunction();

		return ReceiveResult::eContinue;
	}
}

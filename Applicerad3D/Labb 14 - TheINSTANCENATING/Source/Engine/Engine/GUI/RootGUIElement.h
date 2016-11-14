#pragma once
#include "Engine\GUI\GUIElement.h"

namespace ENGINE_NAMESPACE
{
	class RootGUIElement :
		public GUIElement, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>, public Subscriber<MouseMovedMessage>, public Subscriber<LeftMouseButtonDownMessage>
	{
	public:
		RootGUIElement();
		RootGUIElement(const Vector4f & aBorderPositions);
		RootGUIElement(const char * aTexturePath, const Vector2f& aPosition = Vector2f::Zero, const Vector2f& aScale = Vector2f::One);
		~RootGUIElement();
		ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;
		ReceiveResult Receive(const LeftMouseButtonDownMessage& aMessage);
		ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
		ReceiveResult Receive(const MouseMovedMessage& aMessage) override;
		void SetMyIsCurrentGUI(bool aValue);
	private:
		bool myIsCurrentGUI;
	};
}


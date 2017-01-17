#pragma once
#include "Engine\GUI\GUIElement.h"

namespace SB
{
	struct WindowSizeChangedMessage;


	class RootGUIElement :
		public GUIElement, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>, public Subscriber<MouseMovedMessage>, public Subscriber<LeftMouseButtonDownMessage>,
		public Subscriber<WindowSizeChangedMessage>
	{
	public:
		RootGUIElement();
		RootGUIElement(const Vector2f & aPosition, const Vector2f & aSize);
		~RootGUIElement();
		ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;
		ReceiveResult Receive(const LeftMouseButtonDownMessage& aMessage);
		ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
		ReceiveResult Receive(const MouseMovedMessage& aMessage) override;
		ReceiveResult Receive(const WindowSizeChangedMessage& aMessage) override;
		void SetMyIsCurrentGUI(bool aValue);

		virtual void SetPadding(const Vector4f & aPadding) override;

	private:
		bool myIsCurrentGUI;
	};
}


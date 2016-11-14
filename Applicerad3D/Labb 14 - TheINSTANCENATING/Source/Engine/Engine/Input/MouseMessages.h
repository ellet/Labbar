#pragma once

namespace ENGINE_NAMESPACE
{
	struct MouseMovedMessage
	{
		MouseMovedMessage(int aX, int aY, int aDeltaX, int aDeltaY)
		{
			x = aX;
			y = aY;
			deltaX = aDeltaX;
			deltaY = aDeltaY;
		}

		int x;
		int y;

		int deltaX;
		int deltaY;
	};

	struct RawMouseMoveMessage
	{
		RawMouseMoveMessage(int aDeltaX, int aDeltaY)
		{
			deltaX = aDeltaX;
			deltaY = aDeltaY;
		}

		int deltaX;
		int deltaY;
	};

	template <MouseButton TButton = MouseButton::eNone>
	struct MouseButtonDownMessage
	{
		MouseButtonDownMessage(MouseButton aButton)
		{
			button = aButton;
		}

		MouseButton button;
	};

	using AnyMouseButtonDownMessage = MouseButtonDownMessage<>;
	using LeftMouseButtonDownMessage = MouseButtonDownMessage<MouseButton::eLeft>;
	using MiddleMouseButtonDownMessage = MouseButtonDownMessage<MouseButton::eMiddle>;
	using RightMouseButtonDownMessage = MouseButtonDownMessage<MouseButton::eRight>;

	template <MouseButton TButton = MouseButton::eNone>
	struct MouseButtonUpMessage
	{
		MouseButtonUpMessage(MouseButton aButton)
		{
			button = aButton;
		}

		MouseButton button;
	};

	using AnyMouseButtonUpMessage = MouseButtonUpMessage<>;
	using LeftMouseButtonUpMessage = MouseButtonUpMessage<MouseButton::eLeft>;
	using MiddleMouseButtonUpMessage = MouseButtonUpMessage<MouseButton::eMiddle>;
	using RightMouseButtonUpMessage = MouseButtonUpMessage<MouseButton::eRight>;
}

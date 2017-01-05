#pragma once
#include <bitset>

namespace SB
{

	struct EndOfFrameMessage;

	class InputListener :
		public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>, public Subscriber<EndOfFrameMessage>, public Subscriber<AnyMouseButtonDownMessage>, public Subscriber<AnyMouseButtonUpMessage>
	{
	public:
		InputListener(const int aPriority = 0, const bool aBlockMessagesThroughFlag = false);
		~InputListener();

		bool GetHeldKeyDown(const KeyboardKey aKeyToCheck);
		bool GetAnyKeyDown();

		bool GetMouseButtonDown() const;
		bool GetMouseButtonDownThisFrame() const;
		bool GetMouseButtonReleasedThisFrame() const;

		bool GetPressedThisFrame(const KeyboardKey aKeyToCheck);
		bool GetReleasedThisFrame(const KeyboardKey aKeyToCheck);
		bool GetAnyKeyPressedThisFrame();
		bool GetAnyKeyReleasedThisFrame();

		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyMouseButtonDownMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyMouseButtonUpMessage & aMessage) override;

	private:
		bool myBlockInput;
		bool myAnyKeyDown;
		bool myAnyKeyDownLastFrame;

		bool myMouseButtonDown;
		bool myMouseButtonDownLastFrame;

		std::bitset<static_cast<size_t>(KeyboardKey::eCount)> myKeydownThisFrame;
		std::bitset<static_cast<size_t>(KeyboardKey::eCount)> myKeydownLastFrame;
	};

}
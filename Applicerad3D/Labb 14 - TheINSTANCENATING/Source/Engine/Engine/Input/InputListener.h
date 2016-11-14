#pragma once
#include <bitset>

namespace ENGINE_NAMESPACE
{

	struct EndOfFrameMessage;

	class InputListener :
		public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>, public Subscriber<EndOfFrameMessage>
	{
	public:
		InputListener(const int aPriority = 0, const bool aBlockMessagesThroughFlag = false);
		~InputListener();

		bool GetHeldKeyDown(const KeyboardKey aKeyToCheck);

		bool GetPressedThisFrame(const KeyboardKey aKeyToCheck);
		bool GetReleasedThisFrame(const KeyboardKey aKeyToCheck);

		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
		virtual ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;

	private:
		bool myBlockInput;

		std::bitset<static_cast<size_t>(KeyboardKey::eCount)> myKeydownThisFrame;
		std::bitset<static_cast<size_t>(KeyboardKey::eCount)> myKeydownLastFrame;
	};

}
#include "stdafx.h"
#include "InputListener.h"

namespace ENGINE_NAMESPACE
{

	InputListener::InputListener(const int aPriority /*= 0*/, const bool aBlockMessagesThroughFlag /*= false*/) : Subscriber<AnyKeyDownMessage>(aPriority), Subscriber<AnyKeyUpMessage>(aPriority)
	{
		myBlockInput = aBlockMessagesThroughFlag;
		myKeydownThisFrame.reset();
		myKeydownLastFrame.reset();
	}


	InputListener::~InputListener()
	{
	}



	bool InputListener::GetHeldKeyDown(const KeyboardKey aKeyToCheck)
	{
		return myKeydownThisFrame[static_cast<size_t>( aKeyToCheck)];
	}

	bool InputListener::GetPressedThisFrame(const KeyboardKey aKeyToCheck)
	{
		return (myKeydownThisFrame[static_cast<size_t>(aKeyToCheck)] == true && myKeydownLastFrame[static_cast<size_t>(aKeyToCheck)] == false);
	}

	bool InputListener::GetReleasedThisFrame(const KeyboardKey aKeyToCheck)
	{
		return (myKeydownThisFrame[static_cast<size_t>(aKeyToCheck)] == false && myKeydownLastFrame[static_cast<size_t>(aKeyToCheck)] == true);
	}

	ReceiveResult InputListener::Receive(const EndOfFrameMessage & aMessage)
	{
		myKeydownLastFrame = myKeydownThisFrame;
		
		return ReceiveResult::eContinue;
	}

	ReceiveResult InputListener::Receive(const AnyKeyDownMessage & aMessage)
	{
		myKeydownThisFrame.set(static_cast<size_t>(aMessage.key));

		if (myBlockInput == false)
		{
			return ReceiveResult::eContinue;
		}
		else
		{
			return ReceiveResult::eStop;
		}
	}

	ReceiveResult InputListener::Receive(const AnyKeyUpMessage & aMessage)
	{
		myKeydownThisFrame.reset(static_cast<size_t>(aMessage.key));

		if (myBlockInput == false)
		{
			return ReceiveResult::eContinue;
		}
		else
		{
			return ReceiveResult::eStop;
		}
	}

}
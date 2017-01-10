#include "stdafx.h"
#include "InputListener.h"

namespace SB
{

	InputListener::InputListener(const int aPriority /*= 0*/, const bool aBlockMessagesThroughFlag /*= false*/) : Subscriber<AnyKeyDownMessage>(aPriority), Subscriber<AnyKeyUpMessage>(aPriority)
	{
		myBlockInput = aBlockMessagesThroughFlag;
		myKeydownThisFrame.reset();
		myKeydownLastFrame.reset();
		myAnyKeyDown = false;
		myAnyKeyDownLastFrame = false;
	}


	InputListener::~InputListener()
	{
	}



	bool InputListener::GetHeldKeyDown(const KeyboardKey aKeyToCheck)
	{
		return myKeydownThisFrame[static_cast<size_t>( aKeyToCheck)];
	}


	bool InputListener::GetAnyKeyDown()
	{
		return myAnyKeyDown;
	}


	bool InputListener::GetMouseButtonDown() const
	{
		return myMouseButtonDown;
	}


	bool InputListener::GetMouseButtonDownThisFrame() const
	{
		return myMouseButtonDown == true && myMouseButtonDownLastFrame == false;
	}


	bool InputListener::GetMouseButtonReleasedThisFrame() const
	{
		return myMouseButtonDown == false && myMouseButtonDownLastFrame == true;
	}

	bool InputListener::GetPressedThisFrame(const KeyboardKey aKeyToCheck)
	{
		return (myKeydownThisFrame[static_cast<size_t>(aKeyToCheck)] == true && myKeydownLastFrame[static_cast<size_t>(aKeyToCheck)] == false);
	}

	bool InputListener::GetReleasedThisFrame(const KeyboardKey aKeyToCheck)
	{
		return (myKeydownThisFrame[static_cast<size_t>(aKeyToCheck)] == false && myKeydownLastFrame[static_cast<size_t>(aKeyToCheck)] == true);
	}


	bool InputListener::GetAnyKeyPressedThisFrame()
	{
		return myAnyKeyDown == true && myAnyKeyDownLastFrame == false;
	}


	bool InputListener::GetAnyKeyReleasedThisFrame()
	{
		return myAnyKeyDown == false && myAnyKeyDownLastFrame == true;
	}

	ReceiveResult InputListener::Receive(const EndOfFrameMessage & aMessage)
	{
		myKeydownLastFrame = myKeydownThisFrame;
		myMouseButtonDownLastFrame = myMouseButtonDown;
		myAnyKeyDownLastFrame = myAnyKeyDown;
		myAnyKeyDown = false;
		
		return ReceiveResult::eContinue;
	}

	ReceiveResult InputListener::Receive(const AnyKeyDownMessage & aMessage)
	{
		myKeydownThisFrame.set(static_cast<size_t>(aMessage.key));
		myAnyKeyDown = true;

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


	SB::ReceiveResult InputListener::Receive(const AnyMouseButtonDownMessage & aMessage)
	{
		myMouseButtonDown = true;

		if (myBlockInput == false)
		{
			return ReceiveResult::eContinue;
		}
		else
		{
			return ReceiveResult::eStop;
		}
	}


	SB::ReceiveResult InputListener::Receive(const AnyMouseButtonUpMessage & aMessage)
	{
		myMouseButtonDown = false;

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
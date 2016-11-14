#include "stdafx.h"
#include "Cursor.h"
#include "Engine/GenericEngineMessages.h"

namespace ENGINE_NAMESPACE
{
	Cursor::Cursor()
	{
		myStates.Add(eCursorState::eNormal);
		LoadCursors();
		myIsHidden = false;
		myIsConfined = true;
	}

	Cursor::~Cursor()
	{
	}

	HCURSOR Cursor::GetCurrentCursor()
	{
		HCURSOR curse;

		switch (myStates.GetLast())
		{
		case eCursorState::eNormal:
			curse = myNormalCursor;
			break;
		case eCursorState::eHover:
			curse = myHoverCursor;
			break;
		default:
			Error("Cursor Error - cursor state doesn't have support!");
		}

		return curse;
	}

	ReceiveResult Cursor::Receive(const ChangeCursorMessage & aMessage)
	{
		if (aMessage.myState == eCursorState::eChangeBack)
		{
			myStates.RemoveCyclicAtIndex(myStates.Size() - 1);
		}
		else
		{
			myStates.Add(aMessage.myState);
		}
		return ReceiveResult::eContinue;
	}

	ReceiveResult Cursor::Receive(const ShowCursorMessage & aMessage)
	{
		myIsHidden = !aMessage.myShouldShow;
		return ReceiveResult::eContinue;
	}

	ReceiveResult Cursor::Receive(const ConfineMouseMessage & aMessage)
	{
		SetConfinedState(aMessage.myConfinedFlag);
		return ReceiveResult::eContinue;
	}

	void Cursor::ShouldBeHidden(bool aStatement)
	{
		myIsHidden = aStatement;
	}

	bool Cursor::IsHidden() const
	{
		return myIsHidden;
	}

	void Cursor::SetConfinedState(const bool aConfinedFlag)
	{
		myIsConfined = aConfinedFlag;
	}

	bool Cursor::IsConfined() const
	{
		return myIsConfined;
	}

	void Cursor::LoadCursors()
	{
		myNormalCursor = LoadCursorFromFile(L"Assets/Textures/Cursors/normalCurse.cur");
		myHoverCursor = LoadCursorFromFile(L"Assets/Textures/Cursors/hoverCurse.cur");
	}

}
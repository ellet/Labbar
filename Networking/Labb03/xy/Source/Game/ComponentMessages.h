#pragma once

enum EComponentMessageId
{
	EComponentMessageId_Base = 0,
	EComponentMessageId_Input = 1,
};

class CComponentMessageBase
{
public:
	CComponentMessageBase(){}
	virtual ~CComponentMessageBase(){}

	template<class T>
	bool IsType();

	virtual unsigned short GetID() = 0;

	static unsigned short myID;
};

template<class T>
bool CComponentMessageBase::IsType()
{
	if (GetID() == T::myID)
	{
		return true;
	}
	return false;
}

class CComponentMessageOnInput : public CComponentMessageBase
{
public:
	enum EMovement
	{
		MOVE_UP,
		MOVE_DOWN,
	};
	CComponentMessageOnInput(){}
	virtual ~CComponentMessageOnInput(){}

	virtual unsigned short GetID() { return myID; }

	static unsigned short myID;
	EMovement myMovement;
};
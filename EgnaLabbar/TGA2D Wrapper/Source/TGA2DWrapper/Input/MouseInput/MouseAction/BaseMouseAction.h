#pragma once

class Event;

class BaseMouseAction
{
public:
	BaseMouseAction();
	virtual ~BaseMouseAction();

	void virtual DoOnRelease() = 0;
	void virtual DoOnClick();
	void virtual DoOnHeld();

protected:
	Event * myEvent;
};


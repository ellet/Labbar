#pragma once
#include "Event.h"

class Object;

class DoUseOnObject : public Event
{
public:
	DoUseOnObject();
	~DoUseOnObject();

	virtual void OnMouseClickEvent() override;

	void inline SetObjectToDoUseOn(Object * aObjectToMagicOn);

private:
	Object * myObjectToDoUseOn;
};

inline void DoUseOnObject::SetObjectToDoUseOn(Object * aObjectToMagicOn)
{
	myObjectToDoUseOn = aObjectToMagicOn;
}
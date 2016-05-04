#pragma once
#include "Event.h"
#include "../../Object/ElemenTypes.h"

class Object;

class UseMagicOnObject : public Event
{
public:
	UseMagicOnObject(const eElementType aElementType);
	~UseMagicOnObject();

	virtual void OnMouseClickEvent() override;

	void inline SetObjectToDoMagicOn(Object * aObjectToMagicOn);
	
private:
	eElementType myMagicType;
	Object * myObjectToDoMagicOn;
};

inline void UseMagicOnObject::SetObjectToDoMagicOn(Object * aObjectToMagicOn)
{
	myObjectToDoMagicOn = aObjectToMagicOn;
}
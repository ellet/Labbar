#pragma once
#include "Event.h"

class Object;

class ExamineObject : public Event
{
public:
	ExamineObject();
	~ExamineObject();

	inline void SetObjectToExamine(Object * const aObjectToExamine);

	virtual void OnMouseClickEvent() override;

private:
	Object * myObjectToExamin;
};


void ExamineObject::SetObjectToExamine(Object * const aObjectToExamine)
{
	myObjectToExamin = aObjectToExamine;
}
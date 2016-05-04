#pragma once
#include <string>

class Object;

class Event
{
public:
	Event();
	~Event();
	virtual bool Update(const float aDeltaTime);
	virtual void StartEvent();
	virtual void StopEvent();
	virtual void OneShotEvent();
	virtual void OnMouseClickEvent();
	virtual void OnCombineWithObjectEvent(const std::string &aOtherObjectName);
	virtual void OnUseEvent();
	std::string GetName();
	Object *GetAObject();
	void SetObject(Object *aObject);
protected:
	bool myIsActive;
	std::string myName;
	Object *myObject;
};


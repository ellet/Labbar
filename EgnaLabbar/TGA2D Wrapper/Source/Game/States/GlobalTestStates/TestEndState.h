#pragma once
#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>
#include <../Game/Object/Object.h>

class TestEndState :public BaseState
{
public:
	TestEndState();
	void Update(const float aDeltaTime);
	void ConvertToBoxShape(Object* aObject);
	void Draw() const;
	~TestEndState();
private:
	Object* myBackground1;
	Object* myUpperLeftHouse;
	Object* myUpperLeftHouseFIRE;
};


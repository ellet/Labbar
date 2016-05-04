#pragma once

#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseGameObject\BaseAnimatedObject\BaseAnimatedGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>

class TestGameState : public BaseState
{
public:

	TestGameState();
	~TestGameState();
	
	void Update(const float aDeltaTime);
	void Draw() const;

private:

	BaseGameObject *myBaseGameObject;
	BaseAnimatedGameObject *myBaseAnimationGameObject;

};
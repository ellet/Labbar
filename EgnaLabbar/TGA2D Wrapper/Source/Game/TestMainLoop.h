#pragma once

#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>
#include "Levels\LevelManager.h"
#include "EventManager\EventManager.h"
#include "EventManager\Events\AutomaticInventoryAdderTest.h"
#include "Object\TestMouseInput.h"
#include "SoundManager\SoundManager.h"
class TestMainLoop : public BaseState
{
public:

	TestMainLoop();
	~TestMainLoop();

	void Update(const float aDeltaTime);
	void Draw() const;

	void DoOnChangeTo() override;

private:
	AutomaticInventoryAdderTest *myEvent;
	bool myFirstTime;
};
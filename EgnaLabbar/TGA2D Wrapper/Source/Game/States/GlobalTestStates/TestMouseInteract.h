#pragma once

#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseGameObject\BaseAnimatedObject\BaseAnimatedGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>

#include "../Game/Object/TestMouseInput.h"

class TestMouseInteract : public BaseState
{
public:
	TestMouseInteract();
	~TestMouseInteract();

	void Init();

	void Update(const float aDeltaTime) override final;

	void Draw() const;

private:
	TestMouseInput myTestObject;
};


#pragma once
#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>

#include "../Object/MenuObjects/TestPlayButton.h"
#include "../Object/MenuObjects/TestExitButton.h"

class MainMenuState :public BaseState
{
public:
	MainMenuState();
	~MainMenuState();

	void Update(const float aDeltaTime) override;
	void Draw() const override;

	void DoOnChangeFrom();
	void DoOnChangeTo();

private:
	TestPlayButton myPlayButton;
	TestExitButton myExitButton;
	
};
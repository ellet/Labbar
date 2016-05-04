#include "stdafx.h"
#include "MainMenuState.h"
#include "../Levels\LevelManager.h"
#include "../EventManager\EventManager.h"
#include <InputWrapper/InputWrapper.h>
#include <StateManager/StateManager.h>
#include <Input/MouseInput/MouseInput.h>
#include <CollisionManager/CollisionManager.h>


MainMenuState::MainMenuState()
{
	myPlayButton.SetPosition(Vector2f(300.f, 300.f));
	myPlayButton.Inut();

	myExitButton.SetPosition(Vector2f(300.f, 500.f));
	myExitButton.Inut();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Update(const float aDeltaTime)
{
	(aDeltaTime);

	MouseInput::Update();
	CollisionManager::Update();

	if (CU::InputWrapper::GetKeyPressed((DIK_ESCAPE)) == true)
	{
		StateManager::SetActiveState(enumGameStates::eTestMainLoop);
	}

	if (CU::InputWrapper::GetKeyDown((DIK_P)) == true)
	{
		StateManager::SetActiveState(enumGameStates::eTestMainLoop);
	}

	myPlayButton.Update(aDeltaTime);
	myExitButton.Update(aDeltaTime);
	
}

void MainMenuState::Draw() const
{
	myPlayButton.Draw();
	myExitButton.Draw();
	MouseInput::Draw();
}

void MainMenuState::DoOnChangeFrom()
{
	MouseInput::SetMouseDefaultState(enumMouseStates::eMovePlayerMode);
}

void MainMenuState::DoOnChangeTo()
{
	MouseInput::SetMouseDefaultState(enumMouseStates::eNeutralMode);
}

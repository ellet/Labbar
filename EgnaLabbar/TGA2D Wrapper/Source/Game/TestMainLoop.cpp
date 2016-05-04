#include "stdafx.h"
#include "TestMainLoop.h"
#include "Settings\Settings.h"
#include "Levels\Level.h"
#include <tga2d\engine.h>
#include <InputWrapper\InputWrapper.h>
#include "EventManager\Events\AllEvents.h"
#include "Interface\InterfaceManager.h"
#include <CollisionManager\CollisionManager.h>
#include <Input/MouseInput/MouseInput.h>
#include <StateManager/StateManager.h>

TestMainLoop::TestMainLoop()
{
	SetActiveDraw(true);
	SetActiveUpdate(true);

	//myEvent = new AutomaticInventoryAdderTest();
	
	// Test code
	/*for (unsigned short i = 0; i < EventManager::GetAllEvents().Size(); i++)
	{
		if (EventManager::GetAllEvents()[i]->GetName() == "OnClickEvent")
		{
			if (dynamic_cast<OnClickEvent*>(EventManager::GetAllEvents()[i])->GetAObject()->GetName() == "Paper")
			{
				dynamic_cast<OnClickEvent*>(EventManager::GetAllEvents()[i])->OnMouseClickEvent();
			}
		}
	}*/
}


TestMainLoop::~TestMainLoop()
{
}

void TestMainLoop::Update(const float aDeltaTime)
{
	if (myFirstTime != true)
	{
		myFirstTime = true;
		//StateManager::SetActiveState(enumGameStates::eTestIntroState);
	}
	LevelManager::Update(aDeltaTime);

	if (CU::InputWrapper::GetKeyPressed(DIK_ESCAPE) == true)
	{
		StateManager::SetActiveState(enumGameStates::eMainMenuState);
	}
	if (CU::InputWrapper::GetKeyPressed(DIK_I) == true)
	{
		StateManager::SetActiveState(enumGameStates::eTestEndState);
	}
	if (CU::InputWrapper::GetKeyPressed(DIK_P) == true)
	{
		LevelManager::ChangeLevel(std::string("Level2"));
	}

	EventManager::UpdateAllEvents(aDeltaTime);
	InterfaceManager::Update(aDeltaTime);
	MouseInput::Update();
	CollisionManager::Update();
}

void TestMainLoop::Draw() const
{
	LevelManager::Draw();
	InterfaceManager::Draw();
	
	MouseInput::Draw();
}

void TestMainLoop::DoOnChangeTo()
{
	MouseInput::SetMouseState(enumMouseStates::eMovePlayerMode);
}
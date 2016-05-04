#pragma	once
#include "../CommonUtilities/DLDebug/DL_Debug.h"
#include <StateManager/StatesEnum.h>
#include <BaseClasses/BaseState/BaseState.h>

#include "GlobalTestStates\TestGameState.h"
#include "GlobalTestStates\TestMouseInteract.h"
#include "GlobalTestStates\TestCollision.h"
#include "GlobalTestStates\TestIntroState.h"
#include "GlobalTestStates\TestEndState.h"
#include "MainMenuState.h"
#include "../Game/TestMainLoop.h"

namespace StateHandling
{

	BaseState* CreateNewState(const enumGameStates aStateToCreate)
	{
		switch (aStateToCreate)
		{
		case enumGameStates::eTestState:
			return new TestGameState();
			break;

		case enumGameStates::eTestMainLoop:
			return new TestMainLoop();
			break;

		case enumGameStates::eTestMouseInteract:
			return new TestMouseInteract();
			break;
		case enumGameStates::eTestIntroState:
			return new TestIntroState();
			break;

		case enumGameStates::eTestEndState:
			return new TestEndState();
			break;

		case enumGameStates::eTestCollision:
			return new TestCollision();
			break;

		case enumGameStates::eMainMenuState:
			return new MainMenuState();
			break;

		case enumGameStates::enumLength:
		default:
			bool assertFlag = false;
			DL_ASSERT(assertFlag, "State not found in State switch, forgot to add a new one?");
			return nullptr;
			break;
		}
	}

	enumGameStates GetStateEnum(const std::string & aEnumName)
	{
		if (aEnumName == "eTestState")
		{
			return enumGameStates::eTestState;
		}
		
		else if (aEnumName == "eTestMainLoop")
		{
			return enumGameStates::eTestMainLoop;
		}

		/*else if (aEnumName == "eTestEndState")
		{
			return enumGameStates::eTestEndState;
		}*/

		else if (aEnumName == "eTestCollision")
		{
			return enumGameStates::eTestCollision;
		}
		else if (aEnumName == "eTestIntroState")
		{
			return enumGameStates::eTestIntroState;
		}

		else if (aEnumName == "eMainMenu")
		{
			return enumGameStates::eMainMenuState;
		}

		else
		{
			bool assertFlag = false;
			DL_ASSERT(assertFlag, (aEnumName + " conversion from string to StateEnum does not exist").c_str());
			return enumGameStates::enumLength;
		}

	}
}
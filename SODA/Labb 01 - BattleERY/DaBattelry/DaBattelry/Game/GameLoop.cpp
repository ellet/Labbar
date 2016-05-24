#include "stdafx.h"
#include "GameLoop.h"

#include "GameObjects/Unit/DefaultUnit.h"
#include "GameObjects/Unit/LazyUnit.h"
#include "Printing/PrinterClass.h"
#include "GameObjects/Church.h"

GameLoop::GameLoop() :
	myWorld(200, 200, false), myStartOfBattle(0)
{
}


GameLoop::~GameLoop()
{
}

void GameLoop::SetUpGame()
{
	std::cout << "Hello, please don't enter any ineligible variables. \nOnly valid numbers please.\n\nEnter a number of factions:" << std::endl;
	std::cin >> myGameSettings.myAmountOfFactions;
	std::cout << "Please enter a number of units per faction:  \n( Number of total units shouldn't exceed ~60k though, we used unsigned shorts )"  << std::endl;
	std::cin >> myGameSettings.myUnitsPerFaction;
	std::cout << "Please enter 0 for default behaviour and 1 for lazy behaviour:" << std::endl;
	unsigned short behaviour = 0;
	std::cin >> behaviour;
	switch (behaviour)
	{
	case 0:
		myGameSettings.myUnitSettingType = enumUnitTypeMode::eDefault;
		break;
	case 1:
		myGameSettings.myUnitSettingType = enumUnitTypeMode::eLazy;
		break;
	default:
		std::cout << "Didn't enter a proper value, using default behaviour then." << std::endl;
		break;
	}
	std::cout << "Please enter a number of Churches:" << std::endl;
	std::cin >> myGameSettings.myAmountOfCurches;
	std::cout << "Please enter a number of Turns:" << std::endl;
	std::cin >> myGameSettings.myNumberOfTurns;
	std::cout << "Please enter a seed number:" << std::endl;
	std::cin >> myGameSettings.myRandomizerSeed;
}

void GameLoop::RunGame()
{
	CU::TimeManager::Update();
	myStartOfBattle.SetTime(myTimer.GetTime().GetMicroSeconds());
	std::cout << "Calculating..." << std::endl;
	for (unsigned short iTurn = 0; iTurn < myGameSettings.myNumberOfTurns; ++iTurn)
	{
		CU::TimeManager::Update();
		CU::Time turnStartTime = myTimer.GetTime();

		DoTurn();

		CU::TimeManager::Update();
		CU::Time turnEndTime = myTimer.GetTime() - turnStartTime;
		if (iTurn % 100 == 0)
		{
			std::string turnMessage = "Turn # ";
			turnMessage = PT::AddWhateverToString(turnMessage, iTurn);
			PT::PrintText(turnMessage);
		}
		PT::LogTurn(iTurn +1, turnEndTime);
	}
	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit]->CountIsAlive();
	}
	PT::PrintResults();
	std::string timeMessage = "Total time elapsed: ";
	timeMessage = PT::AddWhateverToString(timeMessage, (myTimer.GetTime() - myStartOfBattle).GetSeconds());
	PT::PrintText(timeMessage);
	PT::PrintText("For more detailed information, \ncheck the text 'DAGREATBATTLEOUTPUT' Log in Bin.");
	system("pause");
}

#pragma region init

void GameLoop::Init(const CU::Vector2ui & aGridSize)
{	
	myRandomizer = Randomizer(myGameSettings.myRandomizerSeed);
	InitWorld(aGridSize);
	InitUnits();
}

void GameLoop::DoTurn()
{
	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit]->Update();
	}
	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit]->CountIsAlive();
	}
}

void GameLoop::InitWorld(const CU::Vector2ui & aGridSize)
{
	myWorld.SetSizeClear(aGridSize.x, aGridSize.y, true);
	InitChurches();
	InitBases();
	BaseUnitClass::SetWorld(&myWorld, myGameSettings.myRandomizerSeed);
}

void GameLoop::InitUnits()
{

	myUnits.Init(myGameSettings.myAmountOfFactions * myGameSettings.myUnitsPerFaction);

	unsigned short totalUnit = 0;
	for (unsigned short iFaction = 0; iFaction < myGameSettings.myAmountOfFactions; ++iFaction)
	{
		unsigned short unitCounter = 0;

		for (unsigned short iUnit = 0; iUnit < myGameSettings.myUnitsPerFaction; ++iUnit, ++totalUnit)
		{
			++unitCounter;
			if (myGameSettings.myUnitSettingType == enumUnitTypeMode::eDefault)
			{
				myUnits.Add(new DefaultUnit(totalUnit, iFaction));
			}
			else
			{
				myUnits.Add(new LazyUnit(totalUnit, iFaction));
			}
		}

		std::string temp = PT::AddWhateverToString("Faction ", iFaction);
		temp = PT::AddWhateverToString(temp + " Created and placed ", unitCounter);
		temp += " Units";

		PT::PrintText(temp);
	}

	BaseUnitClass::SetBuddies(&myUnits);
	PT::SetFactionCount(myGameSettings.myAmountOfFactions);
}

void GameLoop::InitChurches()
{
	Church::InitRandomReligion(myGameSettings.myRandomizerSeed);
	for (unsigned short iChurch = 0; iChurch < myGameSettings.myAmountOfCurches; ++iChurch)
	{
		Church prettyChurch;
		prettyChurch.ApplyChurch(myWorld);
	}
}

void GameLoop::InitBases()
{
	BaseUnitClass::ourBasePositions.Init(myGameSettings.myAmountOfFactions);
	for (unsigned short iFaction = 0; iFaction < myGameSettings.myAmountOfFactions; ++iFaction)
	{
		CU::Vector2ui basePosition;
		basePosition.x = static_cast<unsigned int>(myRandomizer.GetRandomValue(0.f, static_cast<float>(myWorld.Width())));
		basePosition.y = static_cast<unsigned int>(myRandomizer.GetRandomValue(0.f, static_cast<float>(myWorld.Height())));
		BaseUnitClass::ourBasePositions.Add(basePosition);
	}
}

#pragma endregion


void GameLoop::SetUnitType(const enumUnitTypeMode aMode)
{
	myGameSettings.myUnitSettingType = aMode;
}



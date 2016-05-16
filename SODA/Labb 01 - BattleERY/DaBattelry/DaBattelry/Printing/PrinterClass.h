#pragma once
#include <fstream>
#include <sstream>

class PrinterClass
{
public:
	static void Create();
	static void Destroy();

	static void SetFactionCount(const unsigned short aNumberOfFactions)
	{
		GetInstance().myFactionsAliveCounters.Init(aNumberOfFactions);
		GetInstance().myFactionsAliveCounters.Resize(aNumberOfFactions);
		GetInstance().ResetFactionCounters();
	}

	static void PrintText(const std::string & aMessage)
	{
		std::cout << aMessage << std::endl;
		GetInstance().myOutput << aMessage << std::endl;
	}

	static void PrintToLog(const std::string & aMessage)
	{
		GetInstance().myOutput << aMessage << std::endl;
	}

	template <typename T>
	static std::string AddWhateverToString(const std::string & aString, const T & aThingToAdd)
	{
		std::stringstream tempStream;
		tempStream << aString;
		tempStream << aThingToAdd;
		return tempStream.str();
	}

	static void LogTurn(unsigned short aTurnIndex, const CU::Time & aTime)
	{
		LogClearScreen();
		std::string turnPrint = AddWhateverToString("Turn # ", aTurnIndex);
		PrintToLog(turnPrint);
		std::string turnTime = AddWhateverToString("Turn took ", aTime.GetSeconds());
		turnTime += " seconds.";
		PrintToLog(turnTime);
		PrintWhiteSpace();
		GetInstance().LogFactionCounters();
		PrintWhiteSpace();
		std::string unitPrint = AddWhateverToString("Number of Units that moved: ", GetInstance().myNumberOfMovedUnits);
		PrintToLog(unitPrint);
		std::string combatPrint = AddWhateverToString("Number of Combats: ", GetInstance().myNumberOfCombats);
		PrintToLog(combatPrint);
		std::string deadPrint = AddWhateverToString("Number of Dead Units: ", GetInstance().myNumberOfDeadUnits);
		PrintToLog(deadPrint);
		GetInstance().myNumberOfMovedUnits = 0;
		GetInstance().myNumberOfCombats = 0;
		GetInstance().ResetFactionCounters();
	}

	static void PrintResults()
	{
		ResultClearScreen();
		PrintText("Results:");
		PrintWhiteSpace();
		GetInstance().ResultFactionCounters();
		PrintWhiteSpace();
		std::string deadPrint = AddWhateverToString("Number of Dead Units: ", GetInstance().myNumberOfDeadUnits);
		PrintText(deadPrint);
	}

	static void MovedUnit()
	{
		GetInstance().myNumberOfMovedUnits += 1;
	}

	static void PerformedCombat()
	{
		GetInstance().myNumberOfCombats += 1;
		GetInstance().myNumberOfDeadUnits += 1;
	}

	static void CountAliveBodies(const unsigned short aFactionID)
	{
		GetInstance().myFactionsAliveCounters[aFactionID] += 1;
	}

	static void PrintWhiteSpace()
	{
		PrintToLog("");
	}

private:
	static PrinterClass * ourInstance;
	static PrinterClass & GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "PrinterClass pointer is nullptr");

		return *ourInstance;
	}

	static void LogClearScreen()
	{
		PrintToLog("---------------------");
	}

	static void ResultClearScreen()
	{
		system("cls");
		PrintText("---------------------");
	}

	void LogFactionCounters()
	{
		for (unsigned short iFaction = 0; iFaction < myFactionsAliveCounters.Size(); ++iFaction)
		{
			std::string factionPrint = AddWhateverToString("Buddies alive in faction ", iFaction);
			factionPrint = AddWhateverToString(factionPrint + ": ", myFactionsAliveCounters[iFaction]);
			PrintToLog(factionPrint);
		}
	}

	void ResultFactionCounters()
	{
		for (unsigned short iFaction = 0; iFaction < myFactionsAliveCounters.Size(); ++iFaction)
		{
			std::string factionPrint = AddWhateverToString("Buddies alive in faction ", iFaction);
			factionPrint = AddWhateverToString(factionPrint + ": ", myFactionsAliveCounters[iFaction]);
			PrintText(factionPrint);
		}
	}

	void ResetFactionCounters()
	{
		for (unsigned short iFaction = 0; iFaction < myFactionsAliveCounters.Size(); ++iFaction)
		{
			myFactionsAliveCounters[iFaction] = 0;
		}
	}

	std::ofstream myOutput;
	unsigned short myNumberOfMovedUnits;
	unsigned short myNumberOfCombats;
	unsigned short myNumberOfDeadUnits;

	CU::GrowingArray<unsigned short> myFactionsAliveCounters;

	PrinterClass();
	~PrinterClass();
};

typedef PrinterClass PT;

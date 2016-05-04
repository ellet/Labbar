#pragma once
#include <iostream>
#include <sstream>
#include <vector>

namespace l1functions
{
	namespace console
	{
		void PrintMessageWithPause(const std::string &aStringToPrint, bool aClearScreen = true);

		void PrintErrorToConsole(const std::string & aStringtoPrint);

		void PrintToConsole(const std::string &aStringToPrint, bool aNewLine = true);

		void PrintNumberToConsole(const float aNumberToPrint, bool aNewLine = true);

		void PrintNumberToConsole(const int aNumberToPrint, bool aNewLine = true);

		void ConsoleWhiteSpace();

		void ClearScreen();

		void PrintVectorOfStrings(const std::vector<std::string> &aStringVectorToPrint);

		void PrintMenuWithNumbers(const std::vector<std::string> &aStringVectorToPrint);

		namespace input
		{
			int GetNumberFromUser(const int aMin, const int aMax);

			unsigned int GivePlayerMenuOptions(const std::vector<std::string> &aMenuOptions);

			unsigned int GivePlayerMenuOptionsWithBack(std::vector<std::string> &aMenuOptions);

			void ClearCIN();
		}
	}

	std::string ConvertNumberToString(float aNumberToConvert);

	std::string ConvertNumberToString(int aNumberToConvert);
}
#include "stdafx.h"
#include "consolefunctions.h"

namespace l1functions
{
	namespace console
	{
		void PrintMessageWithPause(const std::string & aStringToPrint, bool aClearScreen)
		{
			if (aClearScreen)
			{
				ClearScreen();
			}

			PrintToConsole(aStringToPrint, true);

			ConsoleWhiteSpace();

			system("pause");

		}


		void PrintErrorToConsole(const std::string & aStringtoPrint)
		{
			PrintToConsole("ERROR ERROR ERROR");

			PrintToConsole(aStringtoPrint);

			PrintToConsole("ERROR ERROR ERROR");

			system("pause");
		}

		void l1functions::console::PrintToConsole(const std::string & aStringToPrint, bool aNewLine)
		{
			std::cout << aStringToPrint;

			if (aNewLine == true)
			{
				std::cout << std::endl;
			}
		}

		void PrintNumberToConsole(const float aNumberToPrint, bool aNewLine)
		{
			PrintToConsole(ConvertNumberToString(aNumberToPrint), aNewLine);
		}

		void PrintNumberToConsole(const int aNumberToPrint, bool aNewLine)
		{
			PrintNumberToConsole(static_cast<float>(aNumberToPrint), aNewLine);
		}

		void ConsoleWhiteSpace()
		{
			std::cout << std::endl;
		}

		void ClearScreen()
		{
			system("CLS");
		}

		void PrintVectorOfStrings(const std::vector<std::string>& aStringVectorToPrint)
		{
			for (unsigned int iString = 0; iString < aStringVectorToPrint.size(); ++iString)
			{
				PrintToConsole(aStringVectorToPrint[iString]);
			}
		}

		void PrintMenuWithNumbers(const std::vector<std::string>& aStringVectorToPrint)
		{
			for (unsigned int iString = 0; iString < aStringVectorToPrint.size(); ++iString)
			{
				PrintToConsole(ConvertNumberToString(static_cast<int>(iString +1)) + ". " + aStringVectorToPrint[iString]);
			}
		}

		namespace input
		{
			bool GetTrueOrFalseFromUser(const std::string & aQuestionToAsk, bool aShowYesNo)
			{
				PrintToConsole(aQuestionToAsk);

				return GetTrueOrFalseFromUser(aShowYesNo);
			}

			bool GetTrueOrFalseFromUser(bool aShowYesNo)
			{
				if (aShowYesNo == true)
				{
					PrintToConsole("1 - Yes / 2 - No");
				}

				int userInput = GetNumberFromUser(1, 2);

				if (userInput == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			int GetNumberFromUser(const int aMin, const int aMax)
			{
				int userInput;
				do
				{
					std::cin >> userInput;
					ClearCIN();
				} while (userInput < aMin || userInput > aMax);

				return userInput;
			}

			unsigned int GivePlayerMenuOptions(const std::vector<std::string>& aMenuOptions)
			{
				PrintMenuWithNumbers(aMenuOptions);

				return GetNumberFromUser(1, static_cast<int>(aMenuOptions.size())) - 1;
			}

			unsigned int GivePlayerMenuOptionsWithBack(std::vector<std::string>& aMenuOptions)
			{
				aMenuOptions.push_back("Back");

				return GivePlayerMenuOptions(aMenuOptions);
			}

			void ClearCIN()
			{
				std::cin.ignore();
				std::cin.clear();
				std::cin.sync();
			}
		}
	}

	std::string ConvertNumberToString(float aNumberToConvert)
	{
		std::ostringstream numberConverter;
		numberConverter << aNumberToConvert;
		return numberConverter.str();
	}

	std::string ConvertNumberToString(int aNumberToConvert)
	{
		return ConvertNumberToString(static_cast<float>(aNumberToConvert));
	}
	
}
#pragma once

#include "MyGeneralFunctionsNameSpaces.h"
#include <iostream>
#include <sstream>
#include <string>


namespace MyFunctions {
namespace Console {

void DumpCIN();

bool AskTrueOrFalse(const std::string aYesNoQuestion);

int AskForNumber(const std::string aTextQuestionForNumber, const int aMinRange, const int aMaxRange);

int AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const int aMinRange, const int aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const float aMinRange, const float aMaxRange);

float AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const float aMinRange, const float aMaxRange);

}
}
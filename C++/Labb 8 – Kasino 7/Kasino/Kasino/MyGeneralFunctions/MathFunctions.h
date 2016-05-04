#pragma once
#include "MyGeneralFunctionsNameSpaces.h"
#include "stdlib.h"

namespace MyFunctions {
namespace Math {

float EnforcePositiveNumber(float aNumberToCheck);

int EnforcePositiveNumber(int aNumberToCheck);

int SlumpWholeNumber(const int aMax);

int SlumpNumberBetween(const int aMin, const int aMax);

bool CheckNumberIfEven(const int aNumberToCheck);

}
}
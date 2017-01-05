#include "stdafx.h"
#include "DebugToggleFunction.h"

namespace SB
{
	DebugToggleFunction::DebugToggleFunction(
		const std::string & aFeatureName,
		const DebugFunctionsEnumList aFeatureType,
		const std::function<void()> aPressedFunction,
		const KeyboardKey aKeyToPress /*= KeyboardKey::eNone*/,
		const bool aStartState /*= false*/) :

		myName(aFeatureName),
		myPressedKey(aKeyToPress),
		myOnPressedFunction(aPressedFunction),
		myIsActive(aStartState),
		myFeatureType(aFeatureType)
	{

	}

	DebugToggleFunction::~DebugToggleFunction()
	{
	}

	void DebugToggleFunction::TriggerOnPressed()
	{
		if (myOnPressedFunction != nullptr)
		{
			myOnPressedFunction();
		}
		//TODO:: warn if nullptr
	}

}
#pragma once
#include "Engine/Debugging/DebugFunctionsEnumList.h"


namespace ENGINE_NAMESPACE
{
	class DebugToggleFunction
	{
	public:
		DebugToggleFunction(const std::string & aFeatureName, const DebugFunctionsEnumList aFeatureType, const std::function<void()> aPressedFunction, const KeyboardKey aKeyToPress = KeyboardKey::eNone, const bool aStartState = false);
		virtual ~DebugToggleFunction();

		void TriggerOnPressed();

		const std::string & GetFeatureName()
		{return myName;}

		DebugFunctionsEnumList GetFeatureType()
		{return myFeatureType;}

		KeyboardKey GetKeyTypeForPress()
		{return myPressedKey;}
		
	private:
		std::string myName;
		KeyboardKey myPressedKey;
		DebugFunctionsEnumList myFeatureType;

		bool myIsActive;

		std::function<void()> myOnPressedFunction;
	};

}
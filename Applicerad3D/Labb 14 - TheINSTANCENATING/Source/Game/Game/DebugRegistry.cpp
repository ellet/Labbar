#include "stdafx.h"
#include "DebugRegistry.h"
#include "..\Engine\Engine\Debugging\DebugFunctions\DebugToggleFunction.h"
#include "Player\PlayerComponent.h"
#include "Engine\Engine.h"
#include "Engine\Debugging\Debugger.h"

namespace DebugFunctions
{
	void RegisterFunctions()
	{
		//GOD MODE
		SB::DebugToggleFunction * tempRegisterGodModeFunction = new SB::DebugToggleFunction("GOD MODE!!", DebugFunctionsEnumList::eGodMode, std::bind(PlayerComponent::ToggleGodMode));
		SB::Engine::GetDebugger().AddDebugFeature(*tempRegisterGodModeFunction);
	}
}
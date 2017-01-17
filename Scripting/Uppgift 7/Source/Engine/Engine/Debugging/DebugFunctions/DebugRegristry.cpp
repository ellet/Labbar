#include "stdafx.h"
#include "DebugRegristry.h"
#include "DebugToggleFunction.h"
#include "..\..\Component\ModelComponent.h"

namespace SB
{
	namespace DebugFunctions
	{

		void RegisterFunctions()
		{
			DebugToggleFunction * tempRegisterRenderFunction = new DebugToggleFunction("Render Model Axis", DebugFunctionsEnumList::eRenderModelAxis, std::bind(ModelComponent::SwitchRenderAxisFlag));
			Engine::GetDebugger().AddDebugFeature(*tempRegisterRenderFunction);
		}

	}
}
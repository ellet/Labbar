#include "stdafx.h"
#include "DebugRegristry.h"
#include "Engine\Component\Collider\RenderColliderComponent.h"
#include "DebugToggleFunction.h"
#include "..\..\Component\ModelComponent.h"

namespace ENGINE_NAMESPACE
{
	namespace DebugFunctions
	{

		void RegisterFunctions()
		{
			DebugToggleFunction * tempFunction = new DebugToggleFunction("ShowColliders", DebugFunctionsEnumList::eColliderDraw, std::bind(RenderColliderComponent::SwitchRenderColliders), KeyboardKey::eF3);
			Engine::GetDebugger().AddDebugFeature(*tempFunction);

			DebugToggleFunction * tempRegisterRenderFunction = new DebugToggleFunction("Render Model Axis", DebugFunctionsEnumList::eRenderModelAxis, std::bind(ModelComponent::SwitchRenderAxisFlag));
			Engine::GetDebugger().AddDebugFeature(*tempRegisterRenderFunction);
		}

	}
}
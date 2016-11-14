#pragma once
#include "Engine\Debugging\DebugWindowsEnum.h"

namespace ENGINE_NAMESPACE
{
	namespace DebugGUI
	{
		void ShowMainGUI(WindowFlagsList & aListOfWindowFlags);

		void ShowTogglesWindow(const GrowingArray<DebugToggleFunction*> & aArrayOfFeatures, bool & aShowWindowFlag);

		void ShowSceneSelectWindow(const GrowingArray<std::shared_ptr<Scene>> & aArrayOfScenes, bool & aPopCurrentSceneFlag,bool & aShowWindowFlag);
	}
}

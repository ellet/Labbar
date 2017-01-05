#pragma once
#include "Engine\Debugging\DebugWindowsEnum.h"

namespace SB
{
	namespace DebugGUI
	{
		void ShowMainGUI(WindowFlagsList & aListOfWindowFlags);

		void ShowTogglesWindow(const GrowingArray<DebugToggleFunction*> & aArrayOfFeatures, bool & aShowWindowFlag);

		void ShowSceneSelectWindow(const GrowingArray<std::shared_ptr<Scene>> & aArrayOfScenes, bool & aPopCurrentSceneFlag,bool & aShowWindowFlag);
	}
}

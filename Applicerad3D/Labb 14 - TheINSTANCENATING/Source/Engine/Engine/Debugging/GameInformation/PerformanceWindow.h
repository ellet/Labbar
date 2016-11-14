#pragma once

namespace ENGINE_NAMESPACE
{

	void ShowGeneralGameInformation();
	{
		if (ImGui::Begin("GeneralPerformance", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Performance stuff.");
		}
		ImGui::End();
	}

}
#include "stdafx.h"
#include "DebuggerGUI.h"
#include "imgui.h"
#include "Engine/Debugging/DebugFunctions\DebugToggleFunction.h"
#include "BaseDebugGUI.h"
#include "../Utilities/Utilities/HelperFunctions/StringHandling.h"
#include "Engine/Scene/Messages/PushSceneMessage.h"
#include "../../Scene/Messages/PopSceneMessage.h"
#include "Engine/Debugging/Debugger.h"
#include "Engine/Debugging/DebugFunctionsEnumList.h"

namespace ENGINE_NAMESPACE
{
	namespace DebugGUI
	{
		void ShowMainGUI(WindowFlagsList & aListOfWindowFlags)
		{
			static bool ShowDebugFeaturesWindow = true;

			ImGui::BeginMainMenuBar();

			if (ImGui::BeginMenu("Windows") == true)
			{
				for (unsigned short iWindow = 0; iWindow < aListOfWindowFlags.Size(); ++iWindow)
				{
					ImGui::MenuItem(EnumToString(static_cast<DebugWindowEnum>(iWindow)).c_str(), nullptr, &aListOfWindowFlags[iWindow]);
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		void ShowTogglesWindow(const GrowingArray<DebugToggleFunction*> & aArrayOfFeatures, bool & aShowWindowFlag)
		{
			if (ImGui::Begin("Debug Things", &aShowWindowFlag, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
			{
				unsigned short longestIndex = 0;
				size_t longestText = 0;

				for (unsigned short iLength = 0; iLength < aArrayOfFeatures.Size(); ++iLength)
				{
					 const size_t tempLongestText = aArrayOfFeatures[iLength]->GetFeatureName().length();

					 if (tempLongestText > longestText)
					 {
						 longestText = tempLongestText;
						 longestIndex = iLength;
					 }
				}

				for (unsigned short iFeature = 0; iFeature < aArrayOfFeatures.Size(); ++iFeature)
				{
					bool imPressed = false;

					if (longestIndex == iFeature)
					{
						imPressed = ImGui::Button(aArrayOfFeatures[iFeature]->GetFeatureName().c_str());
					}
					else
					{
						imPressed = ImGui::Button(aArrayOfFeatures[iFeature]->GetFeatureName().c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 0.f));
					}

					if (imPressed == true)
					{
						aArrayOfFeatures[iFeature]->TriggerOnPressed();
					}
				}
				ImGui::End();
			}
			
		}

		void ShowSceneSelectWindow(const GrowingArray<std::shared_ptr<Scene>> & aArrayOfScenes, bool & aPopCurrentSceneFlag, bool & aShowWindowFlag)
		{
			if (ImGui::Begin("Scene Select", &aShowWindowFlag, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
			{				

			/*	short currentSelectedNode = -1;
				static int selection_mask = (1 << 2);

				for (unsigned short iScene = 0; iScene < aArrayOfScenes.Size(); ++iScene)
				{
					ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << iScene)) ? ImGuiTreeNodeFlags_Selected : 0);
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)iScene, node_flags, aArrayOfScenes[iScene]->GetName().c_str());

					if (ImGui::IsItemClicked() == true)
					{
						currentSelectedNode = static_cast<short>(currentSelectedNode);
					}

					if (node_open == true)
					{
						PrintText("is open");
						ImGui::TreePop();
					}

						
				}
				if (currentSelectedNode >= -1)
				{
					selection_mask = 1 << currentSelectedNode;
				}*/
				

				unsigned short longestIndex = aArrayOfScenes.Size();
				size_t longestText = 0;

				for (unsigned short iLength = 0; iLength < aArrayOfScenes.Size(); ++iLength)
				{
					const size_t tempLongestText = aArrayOfScenes[iLength]->GetName().length();

					if (tempLongestText > longestText)
					{
						longestText = tempLongestText;
						longestIndex = iLength;
					}
				}

				for (unsigned short iScene = 0; iScene < aArrayOfScenes.Size(); ++iScene)
				{
					bool imPressed = false;

					std::string tempNameOfScene = aArrayOfScenes[iScene]->GetName();

					if (tempNameOfScene == "")
					{
						tempNameOfScene = "NoName";
					}

					if (longestIndex == iScene)
					{
						imPressed = ImGui::Button(tempNameOfScene.c_str());
					}
					else
					{
						imPressed = ImGui::Button(tempNameOfScene.c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 0.f));
					}
					
					if (imPressed == true)
					{
						if (aPopCurrentSceneFlag == true)
						{
							PostMaster::Post(PopSceneMessage(ePopType::eCurrent));
						}
						aPopCurrentSceneFlag = true;
						Engine::GetDebugger().LoadSceneAtIndex(iScene);
						
						Engine::GetDebugger().TriggerDebugFunction(DebugFunctionsEnumList::eDebugMode);
					}
				}
				ImGui::End();
			}
		}

	}
}

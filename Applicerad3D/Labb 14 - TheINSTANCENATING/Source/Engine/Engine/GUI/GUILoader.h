#pragma once

namespace ENGINE_NAMESPACE
{
	class GUIElement;
	class RootGUIElement;
	class JsonScene;
	class GUILoader
	{
	public:
		GUILoader();
		~GUILoader();
		void CreateGUI(const char* aFilePath);
		void SetFunctions(std::unordered_map<std::string, std::function<void()>> & aFunctionMap);
		void DisableGUI();
		void SetCurrentGUI(const std::string & aGUIName);
		std::shared_ptr<RootGUIElement> LoadGUI(const std::string & aGUIName);
	private:
		std::unordered_map<std::string, std::function<void()>>* myBoundFunctions;
		std::unordered_map<std::string, std::shared_ptr<RootGUIElement >> myCreatedGUI;
		JsonScene * myScenePtr;
		void CreateGUIChildren(std::shared_ptr<GUIElement> aGUIElement, const DataNode & aElementData);
	};
}


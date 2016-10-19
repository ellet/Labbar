#pragma once

namespace ENGINE_NAMESPACE
{
	class GUIElement;
	class RootGUIElement;
	class JsonScene;
	class GUILoader
	{
	public:
		GUILoader(std::unordered_map<std::string, std::function<void()>> & aFunctionMap);
		~GUILoader();
		std::shared_ptr<RootGUIElement> LoadGUI(const char* aFilePath);
	private:
		std::unordered_map<std::string, std::function<void()>>* myBoundFunctions;
		std::unordered_map<const char*, std::shared_ptr<RootGUIElement>> myCreatedGUI;
		JsonScene * myScenePtr;
		std::shared_ptr<RootGUIElement> CreateGUI(const char* aFilePath);
		void CreateGUIChildren(std::shared_ptr<GUIElement> aGUIElement, const DataNode & aElementData);
	};
}


#pragma once
#include "Engine/GameObject/GameObject.h"
#include "Engine/Scene/SceneStack/SceneStack.h"

namespace ENGINE_NAMESPACE
{

	class JsonScene;
	class Scene;
	class StandardEffect;


	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		std::shared_ptr<Scene> LoadJsonScene(const char* aFilePath);

		template<typename TSceneType, typename ...TArgs>
		std::shared_ptr<Scene> LoadScene(const TArgs & ...aArgs);

		inline std::shared_ptr<Scene> GetCurrentScene() const
		{
			return mySceneStack.GetCurrentScene();
		}


	private:
		std::shared_ptr<JsonScene> CreateScene(const char* aFilePath);
		ObjectPtr LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene, GrowingArray<ObjectPtr>& aLoadedObjectList);
		std::unordered_map<const char*, std::shared_ptr<Scene>> myScenes;
		//std::shared_ptr<Scene> myCurrentScene;

		SB::SceneStack mySceneStack;

	};

	template<typename TSceneType, typename ...TArgs>
	std::shared_ptr<Scene>
		SceneManager::LoadScene(const TArgs & ...aArgs)
	{
		mySceneStack.AddScene(std::make_shared<TSceneType>(aArgs...), eSceneType::eMajor);
		return mySceneStack.GetCurrentScene();
	}

}

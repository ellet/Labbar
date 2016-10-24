#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ModelComponent.h"
#include "Engine\Component\ComponentPtr.h"
#include "Engine/Component/ComponentRegistry.h"
#include "..\Game\Game\Player\PlayerControllerComponent.h"

namespace ENGINE_NAMESPACE
{

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
		myScenes.clear();
	}
	 
	std::shared_ptr<Scene> SceneManager::LoadJsonScene(const char* aFilePath)
	{
		if (myScenes.find(aFilePath) == myScenes.end())
		{
			myScenes[aFilePath] = CreateScene(aFilePath);
		}

		mySceneStack.AddScene(myScenes[aFilePath], eSceneType::eMajor); //TODO: Set this using command line and/or Json file instead

		//Ensure there is a player
		auto player = mySceneStack.GetCurrentScene()->FindObject("Player");
		if (player == nullptr)
		{
			Error("Scene has no 'Player' object. Please reconsider your life choices.");
		}

		player->GetComponent<PlayerControllerComponent>()->ActivateFirstPersonCamera();

		return myScenes[aFilePath];
	}

	std::shared_ptr<JsonScene> SceneManager::CreateScene(const char* aFilePath)
	{
		std::shared_ptr<JsonScene> newScene = std::make_shared<JsonScene>(aFilePath);

		DataDocument sceneData;
		Data::Open(aFilePath, sceneData);

		unsigned short objectCount = static_cast<unsigned short>(sceneData["hierarchy"].Capacity());

		newScene->CreateGameObjectBuffer(objectCount);

		GrowingArray<ObjectPtr> loadedObjects;
		loadedObjects.Reserve(objectCount);

		for (unsigned short i = 0; i < objectCount; ++i)
		{
			DataNode objectNode = sceneData["hierarchy"][i];
			loadedObjects.Add(LoadGameObject(objectNode, newScene, loadedObjects));
		}

		//Finalize objects from list of loaded objects
		for (unsigned short i = 0; i < loadedObjects.Size(); ++i)
		{
			loadedObjects[i]->Initialize();
		}


		return newScene;
	}

	ObjectPtr SceneManager::LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene, GrowingArray<ObjectPtr>& aLoadedObjectList)
	{
		ObjectPtr obj = aScene->CreateGameObject(aObjectNode["name"].GetString());

		for (unsigned short i = 0; i < aObjectNode["components"].Capacity(); ++i)
		{
			DataNode componentNode = aObjectNode["components"][i];
			std::string componentType = componentNode["type"].GetString();

			if (componentType == "Transform")
			{
				obj->SetPosition(Vector3f(
					componentNode["localPosition"][0].GetFloat(),
					componentNode["localPosition"][1].GetFloat(),
					componentNode["localPosition"][2].GetFloat()
				));
				obj->SetRotation(Quaternion(
					componentNode["localRotation"][0].GetFloat(),
					componentNode["localRotation"][1].GetFloat(),
					componentNode["localRotation"][2].GetFloat(),
					componentNode["localRotation"][3].GetFloat()
				));
				obj->SetScale(Vector3f(
					componentNode["localScale"][0].GetFloat(),
					componentNode["localScale"][1].GetFloat(),
					componentNode["localScale"][2].GetFloat()
				));
			}
			else
			{
				ComponentRegistry::GetInstance().CreateComponent(componentType, obj, componentNode["properties"]);
			}
		}

		for (unsigned short i = 0; i < aObjectNode["children"].Capacity(); ++i)
		{
			ObjectPtr childObject = LoadGameObject(aObjectNode["children"][i], aScene, aLoadedObjectList);
			childObject->SetParent(obj);
			aLoadedObjectList.Add(childObject);
		}

		return obj;
	}

}

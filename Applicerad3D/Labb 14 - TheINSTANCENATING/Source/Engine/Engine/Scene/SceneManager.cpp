#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ModelComponent.h"
#include "Engine\Component\ComponentPtr.h"
#include "Engine/Component/ComponentRegistry.h"
#include "..\Game\Game\Player\PlayerControllerComponent.h"
//#include "..\Game\Game\Scene\CockpitTestScene.h"
#include "PrefabScene.h"
#include "..\Game\Game\Scene\MainMenuScene.h"
#include "..\Game\Game\Scene\LevelSelectScene.h"
#include "..\Game\Game\Scene\CreditScene.h"
#include "..\Game\Game\Scene\OptionsScene.h"
#include "..\Game\Game\Player\PlayerMessages.h"
#include "..\Game\Game\Scene\ParticleEditorScene\ParticleEditorScene.h"
#include "Messages\PushSceneMessage.h"
#include "..\Game\Game\Scene\PauseMenuScene.h"


namespace ENGINE_NAMESPACE
{

	SceneManager::SceneManager()
	{
		myPrefabScene = NewSceneBindBeforeDeletion<PrefabScene>();
	}

	SceneManager::~SceneManager()
	{
		//myScenes.clear();
	}
	 
	void SceneManager::LoadPrefabs()
	{
		myPrefabScene->LoadPrefabs();
	}

	std::shared_ptr<Scene> SceneManager::LoadJsonScene(const char* aFilePath, const eSceneType aType /*= eSceneType::eMajor*/)
	{
		/*if (myScenes.find(aFilePath) == myScenes.end())
		{
			myScenes[aFilePath] = CreateScene(aFilePath);
		}*/
		return CreateScene(aFilePath);
	}

	ReceiveResult SceneManager::Receive(const CreateSceneMessage & aMessage)
	{
		std::shared_ptr<Scene> newScene;

		if (aMessage.mySceneClass == eSceneClass::eJSON)
		{
			if (aMessage.myFilePath == "")
			{
				Error("Create Scene Error - Tried to make JSON scene without specifying filepath!");
			}

			newScene = LoadJsonScene(aMessage.myFilePath.c_str(), aMessage.mySceneType);
		}
		else if (aMessage.mySceneClass == eSceneClass::ePauseMenu)
		{
			newScene = NewSceneBindBeforeDeletion<PauseMenuScene>();
		}
		else if (aMessage.mySceneClass == eSceneClass::eMainMenu)
		{
			newScene = NewSceneBindBeforeDeletion<MainMenuScene>();
		}
		else if (aMessage.mySceneClass == eSceneClass::eParticleEditor)
		{
			newScene = NewSceneBindBeforeDeletion<ParticleEditorScene>();
		}
		else if (aMessage.mySceneClass == eSceneClass::eLevelSelect)
		{
			newScene = NewSceneBindBeforeDeletion<LevelSelectScene>();
		}
		else if (aMessage.mySceneClass == eSceneClass::eCredit)
		{
			newScene = NewSceneBindBeforeDeletion<CreditScene>();
		}
		else if (aMessage.mySceneClass == eSceneClass::eOptions)
		{
			newScene = NewSceneBindBeforeDeletion<OptionsScene>();
		}
		else
		{
			Error("Scene doesn't exist");
		}


		mySceneStack.AddScene(newScene, eSceneType::eMajor);


		if (aMessage.myFunctionCall != nullptr)
		{
			aMessage.myFunctionCall(newScene);
		}


		

		//Add more scene alternatives
		return ReceiveResult::eContinue;
	}

	ReceiveResult SceneManager::Receive(const PushSceneMessage & aMessage)
	{
		mySceneStack.AddScene(aMessage.mySceneToPush, aMessage.mySceneType);
		return ReceiveResult::eContinue;
	}

	ReceiveResult SceneManager::Receive(const PopSceneMessage & aMessage)
	{
		mySceneStack.AddPopCommand(aMessage.myPop);
		return ReceiveResult::eContinue;
	}

	ReceiveResult SceneManager::Receive(const EndOfFrameMessage & aMessage)
	{
		mySceneStack.HandleQueuedCommands();
		return ReceiveResult::eContinue;
	}

	

	std::shared_ptr<JsonScene> SceneManager::CreateScene(const char* aFilePath)
	{
		std::shared_ptr<JsonScene> newScene = NewSceneBindBeforeDeletion<JsonScene>(aFilePath);

		{
			PostMasterStateBinding bind = PostMaster::Push(*newScene);

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
		}

		return newScene;
	}

	ObjectPtr SceneManager::LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene, GrowingArray<ObjectPtr>& aLoadedObjectList)
	{
		ObjectPtr obj = aScene->CreateGameObject(aObjectNode["name"].GetString());
		obj->SetShouldBeSaved(true);
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
				auto newComponent = ComponentRegistry::GetInstance().CreateComponent(componentType, obj, componentNode["properties"]);
				newComponent->SetShouldBeSaved(true);
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

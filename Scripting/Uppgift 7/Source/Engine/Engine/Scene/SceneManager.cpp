#include "stdafx.h"
#include "SceneManager.h"
#include "Engine\Scene\JsonScene.h"
#include "Engine\Scene\Scene.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ModelComponent.h"
#include "Engine\Component\ComponentPtr.h"
#include "Engine/Component/ComponentRegistry.h"
//#include "..\Game\Game\Scene\CockpitTestScene.h"
#include "PrefabScene.h"
#include "..\Game\Game\Scene\CreditsScene.h"
#include "..\Game\Game\Scene\ParticleEditorScene\ParticleEditorScene.h"
#include "Messages\PushSceneMessage.h"
#include "..\Game\Game\Scene\SplashscreenScene.h"
#include "..\Game\Game\Scene\TestScenes\YlfTestScene.h"
#include "..\Game\Game\Scene\MainMenuScene.h"
#include "..\Game\LevelSelectScene.h"
#include "..\Game\OptionsScene.h"



namespace SB
{

	SceneManager::SceneManager()
	{
		myPrefabScene = NewSceneBindBeforeDeletion<PrefabScene>();
		myCachedScenes.Resize(nullptr);
	}

	SceneManager::~SceneManager()
	{
		//myScenes.clear();
	}
	 
	void SceneManager::Update(const SB::Time &aDeltaTime)
	{
		mySceneStack.Update(aDeltaTime);
	}

	void SceneManager::Render()
	{
		mySceneStack.Render();
	}

	void SceneManager::RenderGui()
	{
		mySceneStack.RenderGui();
	}

	void SceneManager::CopyToBackbuffer()
	{
		mySceneStack.CopyToBackbuffer();
	}

	void SceneManager::LoadPrefabs()
	{
		myPrefabScene->LoadPrefabs();
	}

	std::shared_ptr<SB::Scene> SceneManager::LoadJsonScene(const char* aFilePath, const eSceneType aType /*= eSceneType::eMajor*/, const char* aSkyBoxPath)
	{
		/*if (myScenes.find(aFilePath) == myScenes.end())
		{
			myScenes[aFilePath] = CreateScene(aFilePath);
		}*/
		return CreateScene(aFilePath, aSkyBoxPath);
	}

	void SceneManager::AddPreChachedScene(std::shared_ptr<Scene> aSceneToAdd, const eSceneClass aSceneTypeAdd)
	{
		myCachedScenes[static_cast<unsigned short>(aSceneTypeAdd)] = aSceneToAdd;
	}

	ReceiveResult SceneManager::Receive(const CreateSceneMessage & aMessage)
	{
		std::shared_ptr<Scene> newScene;

		if (myCachedScenes[static_cast<unsigned short>(aMessage.mySceneClass)] == nullptr)
		{
			if (aMessage.mySceneClass == eSceneClass::eJSON)
			{
				if (aMessage.myFilePath == "")
				{
					Error("Create Scene Error - Tried to make JSON scene without specifying filepath!");
				}

				newScene = LoadJsonScene(aMessage.myFilePath.c_str(), aMessage.mySceneType, aMessage.mySkyBoxPath.c_str());
			}
			else if (aMessage.mySceneClass == eSceneClass::eParticleEditor)
			{
				newScene = NewSceneBindBeforeDeletion<ParticleEditorScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eCredits)
			{
				newScene = NewSceneBindBeforeDeletion<CreditsScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eSplashscreen)
			{
				newScene = NewSceneBindBeforeDeletion<SplashscreenScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eMainMenu)
			{
				newScene = NewSceneBindBeforeDeletion<MainMenuScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eLevelSelect)
			{
				newScene = NewSceneBindBeforeDeletion<LevelSelectScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eOptions)
			{
				newScene = NewSceneBindBeforeDeletion<OptionsScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eCredits)
			{
				newScene = NewSceneBindBeforeDeletion<CreditsScene>();
			}
			else if (aMessage.mySceneClass == eSceneClass::eYlfTest)
			{
				newScene = NewSceneBindBeforeDeletion<YlfTestScene>();
			}
			else
			{
				Error("Scene doesn't exist.\nYou made a new type of scene and forgot to handle it in SceneManager.cpp");
			}
		}
		else
		{
			newScene = myCachedScenes[static_cast<unsigned short>(aMessage.mySceneClass)];
		}

		mySceneStack.AddScene(newScene, aMessage.mySceneType);


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

	

	std::shared_ptr<SB::JsonScene> SceneManager::CreateScene(const char* aFilePath, const char* aSkyBoxPath)
	{
		std::shared_ptr<JsonScene> newScene = NewSceneBindBeforeDeletion<JsonScene>(aFilePath, aSkyBoxPath);

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

#include "stdafx.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Engine\Component\ComponentRegistry.h"

namespace SB
{
	int GameObjectFactory::Count() const
	{
		return myObjectPool.Count();
	}
	
	GameObjectFactory::~GameObjectFactory()
	{
		EnumerateActiveObjects([](GameObject & aObject ) -> void
		{
			Error(FormatString("Object \"{0}\" was never returned. {1} references remaining.", aObject.GetIdentifier(), aObject.GetReferenceCount()));
		});
	}

	GameObjectFactory::GameObjectFactory()
		: myObjectPool(512)
	{
	}

	void GameObjectFactory::ReturnMemory(unsigned short aIndex)
	{
		myObjectPool.Free(aIndex);
	}

	ObjectPtr GameObjectFactory::CreateObject(Scene & aScene, const std::string & aIdentifier)
	{
		std::atomic<int> * referenceCounter = new std::atomic<int>(1);

		unsigned short index;
		GameObject & obj = myObjectPool.Allocate(&index, aScene, aIdentifier, *referenceCounter);
		obj.SetIndexInFactory(index);

		return ObjectPtr(&obj, referenceCounter);
	}

	ObjectPtr GameObjectFactory::CreateObjectFromPrefab(Scene & aScene, const std::string & aIdentifier, const Vector3f & aPosition)
	{
		DataNode ObjectNode = myPrefabDataBase.GetGlobalPrefab(aIdentifier);

		ObjectPtr object = LoadGameObject(aScene, ObjectNode, &aPosition);
		

		return object;
	}

	void GameObjectFactory::LoadPrefabs(const std::string & aFilePath)
	{
		myPrefabDataBase.AddGlobalPrefabs(aFilePath);
	}

	ObjectPtr GameObjectFactory::LoadGameObject(Scene & aScene, const DataNode aGameObjectProperties, const Vector3f * aPosition)
	{
		ObjectPtr obj = aScene.CreateGameObject(aGameObjectProperties["name"].GetString());

		for (unsigned short i = 0; i < aGameObjectProperties["components"].Capacity(); ++i)
		{
			DataNode componentNode = aGameObjectProperties["components"][i];
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

		for (unsigned short i = 0; i < aGameObjectProperties["children"].Capacity(); ++i)
		{
			ObjectPtr childObject = LoadGameObject(aScene, aGameObjectProperties["children"][i], nullptr);
			childObject->SetParent(obj);
		}
		
		if (aPosition != nullptr)
		{
			obj->SetPosition(*aPosition);
		}

		obj->Initialize();

		return obj;
	}
}

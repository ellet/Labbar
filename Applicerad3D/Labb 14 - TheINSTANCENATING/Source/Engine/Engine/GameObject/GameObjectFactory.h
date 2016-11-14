#pragma once

#include "Engine/GameObject/PrefabDatabase.h"
#include "Utilities/Memory/MemoryPool.h"

namespace
ENGINE_NAMESPACE
{
	class Scene;
	class PrefabDatabase;

	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		~GameObjectFactory();

		ObjectPtr CreateObject(Scene & aScene, const std::string & aName);
		ObjectPtr CreateObjectFromPrefab(Scene & aScene, const std::string & aIdentifier);
		
		void LoadPrefabs(const std::string & aFilePath);
		void ReturnMemory(unsigned short aIndex);

		template <typename TEnumerator>
		void EnumerateActiveObjects(const TEnumerator & aEnumerator);

		int Count() const;

	private:
		ObjectPtr LoadGameObject(Scene & aScene, const DataNode aGameObjectProperties);
		PrefabDatabase myPrefabDataBase;

		DynamicMemoryPool<GameObject> myObjectPool;
	};

	template <typename TEnumerator>
	void GameObjectFactory::EnumerateActiveObjects(const TEnumerator & aEnumerator)
	{
		myObjectPool.ForEach(aEnumerator);
	}
}

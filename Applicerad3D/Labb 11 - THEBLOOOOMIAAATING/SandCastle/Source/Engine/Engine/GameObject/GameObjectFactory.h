#pragma once

namespace
ENGINE_NAMESPACE
{
	class Scene;

	class GameObjectFactory
	{
	public:
		GameObjectFactory();
		~GameObjectFactory();

		ObjectPtr CreateObject(Scene & aScene, const std::string & aName);
		void ReturnMemory(unsigned short aIndex);

		template <typename TEnumerator>
		void EnumerateActiveObjects(const TEnumerator & aEnumerator);

		int Count() const;

	private:
		unsigned short GetAndActivateIndex();

		GrowingArray<bool> myObjectsActiveTag;
		GameObject * myObjects;
		Stack<unsigned short> myFreeMemorySlots;
		unsigned short myNumberOfComponents;
	};

	template <typename TEnumerator>
	void GameObjectFactory::EnumerateActiveObjects(const TEnumerator & aEnumerator)
	{
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myObjectsActiveTag[iComponent] == true)
			{
				aEnumerator(myObjects[iComponent]);
			}
		}
	}
}

#pragma once
#include "../GrowingArray/GrowingArray.h"

namespace CommonUtilities
{

	template <typename Key, typename Value, typename CountType = unsigned short>
	class Map
	{
	public:
		Map()
		{
			
		}
		~Map()
		{}

		Value& operator[](const Key & aKey); // ska skapa en key om det inte finns

		bool KeyExists(const Key & aKey);

		void Delete(const Key & aKey); // assert på key

	private:
		GrowingArray<Value, CountType> mystuff;
	};

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	Value& CommonUtilities::Map<Key, Value, CountType>::operator[](const Key & aKey)
	{

	}

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	bool CommonUtilities::Map<Key, Value, CountType>::KeyExists(const Key & aKey)
	{

	}

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	void CommonUtilities::Map<Key, Value, CountType>::Delete(const Key & aKey)
	{

	}
	

}
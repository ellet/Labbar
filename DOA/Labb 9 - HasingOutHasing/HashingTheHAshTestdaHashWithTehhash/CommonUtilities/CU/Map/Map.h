#pragma once
#include "../GrowingArray/GrowingArray.h"

namespace CommonUtilities
{
	template <typename Key, typename Value, typename CountType = unsigned short>
	struct NodeData
	{
		NodeData()
		{}
		NodeData(const Key & aKey)
			: myKey(aKey)
		{
		}

		Key myKey;
		Value myValue;
	};

	template <typename Key, typename Value, typename CountType = unsigned short>
	class Map
	{
	public:
		

		Map(const CountType & aSize = 128)
		{
			using std::placeholders::_1;
			myData.Init(aSize);
			myData.Resize(aSize);
			for (CountType iData = 0; iData < myData.Size(); ++iData)
			{
				myData[iData].Init(3);
			}
		}
		~Map()
		{}

		Value& operator[](const Key & aKey); // ska skapa en key om det inte finns

		bool KeyExists(const Key & aKey);

		void Delete(const Key & aKey); // assert på key

	private:
		CountType GetIndex(const Key & aKey);
		NodeData<Key, Value, CountType>& AddToPosition(const Key & aKey);

		GrowingArray<GrowingArray<NodeData<Key, Value, CountType>, CountType>, CountType> myData;
	};

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	NodeData<Key, Value, CountType>& CommonUtilities::Map<Key, Value, CountType>::AddToPosition(const Key & aKey)
	{
		myData[GetIndex(aKey)].Add(NodeData<Key, Value, CountType>(aKey));
		return myData[GetIndex(aKey)].GetLast();
	}
	

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	CountType CommonUtilities::Map<Key, Value, CountType>::GetIndex(const Key & aKey)
	{
		return std::hash<Key>()(aKey) % myData.Size();
	}

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	inline Value& CommonUtilities::Map<Key, Value, CountType>::operator[](const Key & aKey)
	{
		if (KeyExists(aKey) == true)
		{
			for (CountType iData = 0; iData < myData[GetIndex(aKey)].Size(); ++iData)
			{
				if (myData[GetIndex(aKey)][iData].myKey == aKey)
				{
					return myData[GetIndex(aKey)][iData].myValue;
				}
			}
		}

		return AddToPosition(aKey).myValue;
	}

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	inline bool CommonUtilities::Map<Key, Value, CountType>::KeyExists(const Key & aKey)
	{
		const CountType Index = GetIndex(aKey);
		
		if (myData[Index].Size() > 0)
		{
			for (CountType iData = 0; iData < myData[Index].Size(); ++iData)
			{
				if (myData[Index][iData].myKey == aKey)
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			return false;
		}
	}

	template <typename Key, typename Value, typename CountType /*= unsigned short*/>
	inline void CommonUtilities::Map<Key, Value, CountType>::Delete(const Key & aKey)
	{
		DL_ASSERT(KeyExists(aKey) == true, "Key does not Exist");

		const CountType Index = GetIndex(aKey);

		for (CountType iData = 0; iData < myData[Index].Size(); ++iData)
		{
			if (myData[Index][iData].myKey == aKey)
			{
				myData[Index].RemoveCyclicAtIndex(iData);
			}
		}
	}
	

}
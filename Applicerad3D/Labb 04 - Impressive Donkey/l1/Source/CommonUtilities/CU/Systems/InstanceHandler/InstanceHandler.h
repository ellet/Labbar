#pragma once
#include <unordered_map>

namespace CommonUtilities
{
	template <typename DataToHold, typename Key, typename IndexType = unsigned short>
	class InstanceHandler
	{
	public:
		InstanceHandler();
		~InstanceHandler();

		DataToHold & GetObjectInstance(const Key & aIdentifier);

	private:
		bool CheckIfExists(const Key & aIdentifier);
		void AddNewInstance(const Key & aIdentifier);

		CU::GrowingArray<DataToHold, Indextype>myData;
		std::unordered_map<Key, IndexType> myIndexMap;
	};

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	DataToHold & CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::GetObjectInstance(const Key & aIdentifier)
	{
		if (CheckIfExists(aIdentifier) == false)
		{
			AddNewInstance(aIdentifier);
		}
		
		return myData[myIndexMap[aIdentifier]];
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	bool CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::CheckIfExists(const Key & aIdentifier)
	{
		return (myIndexMap.count(aIdentifier) > 0);
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	void CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::AddNewInstance(const Key & aIdentifier)
	{
		myData.Add(DataToHold());
		myIndexMap[aIdentifier] = myData.size();
	}

	template <typename DataToHold, typename Key>
	CommonUtilities::InstanceHandler<DataToHold, Key>::InstanceHandler()
	{

	}

	template <typename DataToHold, typename Key>
	CommonUtilities::InstanceHandler<DataToHold, Key>::~InstanceHandler()
	{

	}

}
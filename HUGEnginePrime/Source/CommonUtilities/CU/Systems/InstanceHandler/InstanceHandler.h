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

		bool GetObjectInstance(const Key & aIdentifier, DataToHold *&  aDataPointToSet);

	private:
		bool CheckIfExists(const Key & aIdentifier);
		void AddNewInstance(const Key & aIdentifier);

		CU::GrowingArray<DataToHold*, IndexType>myData;
		std::unordered_map<Key, IndexType> myIndexMap;
	};

	/*
		Returns true if the data contained was not yet already created.
	*/
	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	bool CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::GetObjectInstance(const Key & aIdentifier, DataToHold *&  aDataPointToSet)
	{
		if (CheckIfExists(aIdentifier) == false)
		{
			AddNewInstance(aIdentifier);
			aDataPointToSet = myData[myIndexMap[aIdentifier]];
			
			return true;
		}
		
		aDataPointToSet = myData[myIndexMap[aIdentifier]];
		return false;
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	bool CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::CheckIfExists(const Key & aIdentifier)
	{
		return (myIndexMap.count(aIdentifier) > 0);
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	void CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::AddNewInstance(const Key & aIdentifier)
	{
		myData.Add(new DataToHold());
		myIndexMap[aIdentifier] = myData.Size() - static_cast<IndexType>(1);
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::InstanceHandler()
	{
		myData.Init(4);
	}

	template <typename DataToHold, typename Key, typename IndexType /*= unsigned short*/>
	CommonUtilities::InstanceHandler<DataToHold, Key, IndexType>::~InstanceHandler()
	{

	}
}
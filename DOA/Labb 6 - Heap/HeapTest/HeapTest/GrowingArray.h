#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H
#include <assert.h>
#include <iostream>

namespace CommonUtilities
{
	template <class Type, class CountType = unsigned int>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(const CountType& aNrOfRecommendedItems, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
	
		void Init(const CountType& aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		void ReInit(const CountType& aNrOfRecomendedItems, bool aUseSafeModeFlag = true);

		inline Type& operator[](const CountType& aIndex);
		inline const Type& operator[](const CountType& aIndex) const;

		inline void Add(const Type &aObject);
		inline void Insert(const CountType& aIndex, const Type &aObject);
		inline void DeleteCyclic(const Type &aObject);
		inline void DeleteCyclicAtIndex(const CountType& aItemNumber);
		inline void RemoveCyclic(const Type &aObject);
		inline void RemoveCyclicAtIndex(const CountType& aItemNumber);
		inline CountType Find(const Type &aObject);
	
		inline Type& GetLast();
		inline const Type& GetLast() const;

		static const CountType FoundNone = static_cast<CountType>(-1);

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline CountType Count() const;
		__forceinline CountType Size() const;

	private:
		inline void Resize(const CountType& aNewSize);
		Type* myData;
		CountType mySize;
		CountType myAllocatedElements;
		bool myIsInSafeMode;
	};

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray()
	{
		myData = nullptr;
		mySize = 0;
		myAllocatedElements = 0;
		myIsInSafeMode = false;
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray(const CountType& aNrOfRecommendedItems, bool aUseSafeModeFlag = true)
	{
		myIsInSafeMode = aUseSafeModeFlag;
		myAllocatedElements = aNrOfRecommendedItems;
		myData = new Type[myAllocatedElements];
		mySize = 0;
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		myIsInSafeMode = aGrowingArray.myIsInSafeMode;
		myAllocatedElements = aGrowingArray.myAllocatedElements;
		mySize = aGrowingArray.mySize;
		myData = new Type[myAllocatedElements];
		if(myIsInSafeMode == true)
		{
			for(CountType i = 0; i < mySize;++i)
			{
				myData[i] = aGrowingArray.myData[i];
			}
		}
		else
		{
			memcpy(myData, aGrowingArray.myData, sizeof(Type) * mySize);
		}
	}

	template <class Type, class CountType>
	GrowingArray<Type, CountType>::~GrowingArray()
	{
		delete[] myData; //nullptr = safe delete
		mySize = 0;
		myAllocatedElements = 0;
		myIsInSafeMode = false;
		myData = nullptr;
	}

	template <class Type, class CountType>
	GrowingArray<Type,CountType>& GrowingArray<Type, CountType>::operator=(const GrowingArray& aGrowingArray)
	{
		mySize = aGrowingArray.mySize;
		myAllocatedElements = aGrowingArray.myAllocatedElements;
		myIsInSafeMode = aGrowingArray.myIsInSafeMode;
		delete[] myData;
		myData = new Type[myAllocatedElements];
		if(myIsInSafeMode == true)
		{
			for(CountType i = 0; i < mySize;++i)
			{
				myData[i] = aGrowingArray.myData[i];
			}
		}
		else
		{
			memcpy(myData, aGrowingArray.myData, sizeof(Type) * mySize);
		}
		return *this;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::Init(const CountType &aNrOfRecomendedItems, bool aUseSafeModeFlag = true)
	{
		myIsInSafeMode = aUseSafeModeFlag;
		myAllocatedElements = aNrOfRecomendedItems;
		myData = new Type[myAllocatedElements];
		mySize = 0;
	}

	template <class Type, class CountType>
	void GrowingArray<Type, CountType>::ReInit(const CountType &aNrOfRecomendedItems, bool aUseSafeModeFlag = true)
	{
		delete[] myData;
		myData = nullptr;
		Init(aNrOfRecomendedItems, aUseSafeModeFlag);
	}

	template <class Type, class CountType>
	inline Type& GrowingArray<Type, CountType>::operator[](const CountType& aIndex)
	{
		assert((myData != nullptr) && "Trying to use [] without first initializing it");
		assert((aIndex >= 0 && aIndex < mySize) && "Tried to access an element outside range with [] on GrowingArray.");
		return myData[aIndex];
	}

	template <class Type, class CountType>
	inline const Type& GrowingArray<Type, CountType>::operator[](const CountType& aIndex) const
	{
		assert((myData != nullptr) && "Trying to use [] without first initializing it");
		assert((aIndex >= 0 && aIndex < mySize) && "Tried to access an element outside range with [] on GrowingArray.");
		return myData[aIndex];
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::Add(const Type &aObject)
	{
		assert((myData != nullptr) && "Trying to use Add without first initializing it");
		if(myAllocatedElements == mySize)
		{
			Resize(myAllocatedElements*2);
		}
		myData[mySize] = aObject;
		++mySize;
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::Insert(const CountType &aIndex, const Type &aObject)
	{
		assert((myData != nullptr) && "Trying to use Insert without first initializing it");
		assert((aIndex >= 0 && aIndex <= mySize) && "Tried to insert an element outside range on GrowingArray.");
		if(mySize == myAllocatedElements)
		{
			Resize(myAllocatedElements*2);
		}
		for(CountType i = mySize; i > aIndex;--i)
		{
			myData[i] = myData[i - 1];
		}
		myData[aIndex] = aObject;
		++mySize;
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::DeleteCyclic(const Type &aObject)
	{
		for(CountType i = 0; i < mySize;++i)
		{
			if(myData[i] == aObject)
			{
				delete myData[i];
				myData[i] = myData[mySize-1];
				myData[mySize - 1] = nullptr;
				--mySize;
				return;
			}
		}
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::DeleteCyclicAtIndex(const CountType &aItemNumber)
	{
		if(mySize > 0)
		{
			delete myData[aItemNumber];
			myData[aItemNumber] = myData[mySize-1];
			myData[mySize - 1] = nullptr;
			--mySize;
		}
		else
		{
			DeleteAll();
		}
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::RemoveCyclic(const Type &aObject)
	{
		for(CountType i = 0; i < mySize;++i)
		{
			if(myData[i] == aObject)
			{
				myData[i] = myData[mySize-1];
				--mySize;
				return;
			}
		}
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::RemoveCyclicAtIndex(const CountType &aItemNumber)
	{
		if(mySize > 0)
		{
			myData[aItemNumber] = myData[mySize-1];
			--mySize;
		}
		else
		{
			RemoveAll();
		}
	}

	template <class Type, class CountType>
	inline CountType GrowingArray<Type, CountType>::Find(const Type &aObject)
	{
		for(CountType i = 0; i < mySize;++i)
		{
			if(myData[i] == aObject)
			{
				return i;
			}
		}
		return FoundNone;
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::RemoveAll()
	{
		mySize = 0;
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::DeleteAll()
	{
		for(CountType i = 0; i < mySize;++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
		mySize = 0;
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::Optimize()
	{
		Resize(mySize);
	}

	template <class Type, class CountType>
	__forceinline CountType GrowingArray<Type, CountType>::Size() const
	{
		return mySize;
	}

	template <class Type, class CountType>
	__forceinline CountType GrowingArray<Type, CountType>::Count() const
	{
		return mySize;
	}

	template <class Type, class CountType>
	inline Type& GrowingArray<Type, CountType>::GetLast()
	{
		return myData[mySize - 1];
	}

	template <class Type, class CountType>
	inline const Type& GrowingArray<Type, CountType>::GetLast() const
	{
		return myData[mySize - 1];
	}

	template <class Type, class CountType>
	inline void GrowingArray<Type, CountType>::Resize(const CountType &aNewSize)
	{
		Type* newData = new Type[aNewSize];
		for(CountType i = 0; i < mySize; i++)
		{
			newData[i] = myData[i];
		}
		delete[] myData;
		myData = newData;
		myAllocatedElements = aNewSize;
	}

};
namespace CU = CommonUtilities;
#endif
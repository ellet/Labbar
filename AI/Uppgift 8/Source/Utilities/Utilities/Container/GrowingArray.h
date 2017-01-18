#pragma once
#pragma message( "Compiled " __FILE__ " on " __DATE__ " at " __TIME__ ) 

#include <assert.h>
#include <cstring>


namespace SB
{
	template<typename ObjectType, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);

		~GrowingArray();

		GrowingArray&operator=(const GrowingArray& aGrowingArray);
		GrowingArray&operator=(GrowingArray&& aGrowingArray);

		void ReInit(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true);

		inline ObjectType&operator[](const SizeType& aIndex);
		inline const ObjectType&operator[](const SizeType& aIndex) const;

		inline void Add(const ObjectType& aObject);
		inline void Insert(const SizeType aIndex, const ObjectType& aObject);
		inline void DeleteCyclic(ObjectType& aObject);
		inline void DeleteCyclicAtIndex(SizeType aItemNumber);
		inline void DeleteAtIndex(SizeType aItemNumber);
		inline void RemoveCyclic(const ObjectType& aObject);
		inline void RemoveCyclicAtIndex(SizeType aItemNumber);
		inline void RemoveAtIndex(SizeType aItemNumber);
		inline void FillWith(const ObjectType & aObject, const SizeType aSizeToFillTo);
		inline void FillToCapactiy(const ObjectType & aObject);
		inline void FillFromToWith(const ObjectType & aObjectToFillWith, const SizeType aFromIndex, const SizeType aToIndex);
		inline void FillFromToCapacity(const ObjectType & aObjectToFillWith, const SizeType aFromIndex);
		
		template<typename TCompareType>
		inline SizeType Find(const TCompareType & aObject) const;

		inline const bool Empty() const;
		inline ObjectType& GetLast();
		inline const ObjectType& GetLast() const;
		__forceinline ObjectType &At(const SizeType aIndex) { return myArray[aIndex]; }
		static const SizeType FoundNone = static_cast<SizeType>(-1);

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline SizeType Size() const;
		SizeType GetCapacity();
		inline void Resize(SizeType aNewSize, const ObjectType & aFillWith = ObjectType());
		inline void Reserve(SizeType aReservedSize);
		__forceinline const ObjectType* GetArrayPointer(SizeType aPosition = 0)const { return myArray + aPosition; }

		SizeType GetLastIndex()const;

	private:
		ObjectType * myArray;

		bool mySafeModeFlag;
		SizeType myCapacity;
		SizeType myNrOfItems;
	};

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	SizeType SB::GrowingArray<ObjectType, SizeType>::GetLastIndex() const
	{
		return myNrOfItems - 1;
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	void SB::GrowingArray<ObjectType, SizeType>::FillFromToCapacity(const ObjectType & aObjectToFillWith, const SizeType aFromIndex)
	{
		FillFromToWith(aObjectToFillWith, aFromIndex, myNrOfItems - 1);
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	void SB::GrowingArray<ObjectType, SizeType>::FillFromToWith(const ObjectType & aObjectToFillWith, const SizeType aFromIndex, const SizeType aToIndex)
	{
		assert(aToIndex < myNrOfItems);

		for (SizeType i = aToIndex; i < aToIndex; ++i)
		{
			myArray[i] = aObjectToFillWith;
		}
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	void SB::GrowingArray<ObjectType, SizeType>::FillToCapactiy(const ObjectType & aObject)
	{
		FillWith(aObject, myNrOfItems);
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	void SB::GrowingArray<ObjectType, SizeType>::FillWith(const ObjectType & aObject, const SizeType aSizeToFillTo)
	{
		assert(aSizeToFillTo <= myNrOfItems);

		for (SizeType i = 0; i < aSizeToFillTo; i++)
		{
			myArray[i] = aObject;
		}
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	SizeType GrowingArray<ObjectType, SizeType>::GetCapacity()
	{
		return myCapacity;
	}


	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray()
	{
		myNrOfItems = 0;
		myCapacity = 2;
		myArray = new ObjectType[myCapacity];
		mySafeModeFlag = true;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true)
	{
		myNrOfItems = 0;
		myCapacity = aNrOfRecommendedItems;
		mySafeModeFlag = aUseSafeModeFlag;

		myArray = new ObjectType[myCapacity];
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		assert(aGrowingArray.myArray != nullptr && "CAN NOT ASSIGN WITH UNINITIALIZED ARRAY!");
		myNrOfItems = 0;
		myCapacity = 2;
		myArray = new ObjectType[myCapacity];
		mySafeModeFlag = true;
		*this = aGrowingArray;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray(GrowingArray&& aGrowingArray)
	{
		assert(aGrowingArray.myArray != nullptr && "CAN NOT ASSIGN WITH UNINITIALIZED ARRAY!");
		myCapacity = aGrowingArray.myCapacity;
		mySafeModeFlag = aGrowingArray.mySafeModeFlag;
		myNrOfItems = aGrowingArray.myNrOfItems;
		myArray = aGrowingArray.myArray;
		aGrowingArray.myArray = nullptr;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::~GrowingArray()
	{
		//assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		delete[]myArray;
		myArray = nullptr;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray& aGrowingArray)
	{
		assert(aGrowingArray.myArray != nullptr && "CAN NOT ASSIGN WITH UNINITIALIZED ARRAY!");
		if (myCapacity != aGrowingArray.myCapacity)
		{
			delete[] myArray;
			myArray = new ObjectType[aGrowingArray.myCapacity];
		}

		if (aGrowingArray.mySafeModeFlag == true)
		{
			for (SizeType i = 0; i < aGrowingArray.Size(); i++)
			{
				myArray[i] = aGrowingArray[i];
			}
		}
		else
		{
			memcpy(myArray, aGrowingArray.myArray, sizeof(ObjectType)*aGrowingArray.Size());
		}
		myCapacity = aGrowingArray.myCapacity;
		myNrOfItems = aGrowingArray.myNrOfItems;
		return *this;
	}
	template<typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(GrowingArray&& aGrowingArray)
	{
		assert(aGrowingArray.myArray != nullptr && "CAN NOT ASSIGN WITH UNINITIALIZED ARRAY!");
		myCapacity = aGrowingArray.myCapacity;
		myNrOfItems = aGrowingArray.myNrOfItems;
		myArray = aGrowingArray.myArray;
		aGrowingArray.myArray = nullptr;
		return *this;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		myCapacity = aNrOfRecomendedItems;
		mySafeModeFlag = aUseSafeModeFlag;
		myNrOfItems = 0;

		delete[] myArray;
		myArray = new ObjectType[aNrOfRecomendedItems];
	}


	template<typename ObjectType, typename SizeType = unsigned short>
	ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		assert((aIndex >= 0 && aIndex < myNrOfItems) && "INDEX OUT OF BOUNDS!");
		return myArray[aIndex];
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	const ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex) const
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		assert((aIndex >= 0 && aIndex < myNrOfItems) && "INDEX OUT OF BOUNDS!");

		return myArray[aIndex];
	}
	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Add(const ObjectType& aObject)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		if (myNrOfItems >= myCapacity)
		{
			Reserve(myCapacity * 2);
		}

		myArray[myNrOfItems++] = aObject;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Insert(const SizeType aIndex, const ObjectType& aObject)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		if (aIndex == myNrOfItems)
		{
			Add(aObject);
			return;
		}

		assert((aIndex >= 0 && aIndex < myNrOfItems) && "INDEX OUT OF BOUNDS!");
		if (++myNrOfItems >= myCapacity)
		{
			Reserve(myCapacity * 2);
		}
		for (SizeType i = myNrOfItems - 1; i > aIndex; i--)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[aIndex] = aObject;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::DeleteCyclic(ObjectType& aObject)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		DeleteCyclicAtIndex(Find(aObject));
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::DeleteCyclicAtIndex(SizeType aItemNumber)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		assert((aItemNumber >= 0 && aItemNumber < myNrOfItems) && "INDEX OUT OF BOUNDS!");
		delete(myArray[aItemNumber]);
		myArray[aItemNumber] = nullptr;

		if (aItemNumber < myNrOfItems - 1)
		{
			myArray[aItemNumber] = myArray[--myNrOfItems];
		}
		else
		{
			--myNrOfItems;
		}
		myArray[myNrOfItems] = ObjectType();
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::DeleteAtIndex(SizeType aItemNumber)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		assert((aItemNumber >= 0 && aItemNumber < myNrOfItems) && "INDEX OUT OF BOUNDS!");

		if (std::is_trivially_destructible<ObjectType>() == false)
		{
			myArray[aItemNumber] = ObjectType();
		}

		for (SizeType i = aItemNumber; i < myNrOfItems; ++i)
		{
			if (i == myNrOfItems - 1)
			{
				delete(myArray[myNrOfItems - 1]);
				myArray[myNrOfItems - 1] = nullptr;

				break;
			}
			myArray[i] = myArray[i + 1];
		}

		--myNrOfItems;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType& aObject)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		RemoveCyclicAtIndex(Find(aObject));
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType aItemNumber)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		assert((aItemNumber >= 0 && aItemNumber < myNrOfItems) && "INDEX OUT OF BOUNDS!");

		if (aItemNumber < myNrOfItems - 1)
		{
			myArray[aItemNumber] = myArray[--myNrOfItems];
		}
		else
		{
			--myNrOfItems;
		}

		if (std::is_trivially_destructible<ObjectType>() == false)
		{
			myArray[myNrOfItems] = ObjectType();
		}
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::RemoveAtIndex(SizeType aItemNumber)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		assert((aItemNumber >= 0 && aItemNumber < myNrOfItems) && "INDEX OUT OF BOUNDS!");

		for (SizeType i = aItemNumber; i < myNrOfItems - 1; ++i)
		{
			myArray[i] = myArray[i + 1];
		}

		--myNrOfItems;

		if (std::is_trivially_destructible<ObjectType>() == false)
		{
			myArray[myNrOfItems] = ObjectType();
		}
	}


	template<typename ObjectType, typename SizeType>
	template<typename TCompareType>
	SizeType GrowingArray<ObjectType, SizeType>::Find(const TCompareType & aObject) const
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		SizeType i = 0;
		while (i < myNrOfItems)
		{
			if (myArray[i] == aObject)
			{
				return i;
			}
			++i;
		}
		return FoundNone;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	inline const bool GrowingArray<ObjectType, SizeType>::Empty() const
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		if (Size() == 0)
		{
			return true;
		}

		return false;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	ObjectType& GrowingArray<ObjectType, SizeType>::GetLast()
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		return (myArray[myNrOfItems - 1]);
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	const ObjectType& GrowingArray<ObjectType, SizeType>::GetLast() const
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		return (myArray[myNrOfItems - 1]);
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::RemoveAll()
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		if (std::is_trivially_destructible<ObjectType>() == false)
		{
			for (SizeType i = 0; i < myNrOfItems; i++)
			{
				myArray[i] = ObjectType();
			}
		}
		myNrOfItems = 0;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::DeleteAll()
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		for (SizeType i = 0; i < myNrOfItems; i++)
		{
			delete myArray[i];
			myArray[i] = nullptr;
		}
		myNrOfItems = 0;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Optimize()
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		ObjectType *tempArray = new ObjectType[myNrOfItems];

		for (SizeType i = 0; i < myNrOfItems; i++)
		{
			tempArray[i] = myArray[i];
		}

		delete[]myArray;
		myArray = tempArray;
		tempArray = nullptr;
		myCapacity = myNrOfItems;
	}

	template<typename ObjectType, typename SizeType = unsigned short>
	SizeType GrowingArray<ObjectType, SizeType>::Size() const
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		return myNrOfItems;
	}

	template<typename ObjectType, typename SizeType /*= unsigned short*/>
	void GrowingArray<ObjectType, SizeType>::Reserve(SizeType aReservedSize)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");
		if (aReservedSize > myCapacity)
		{
			ObjectType *tempArray = new ObjectType[aReservedSize];

			for (SizeType i = 0; i < myNrOfItems; i++)
			{
				tempArray[i] = myArray[i];
			}

			delete[]myArray;
			myArray = tempArray;
			tempArray = nullptr;

			//Use the below to debug instances of unnecessary growth where reserving to a larger initial size would be more beneficial
//#ifdef _DEBUG
//			std::cout << "GrowingArray of type: " << typeid(ObjectType).name() << " of sizetype: " << typeid(SizeType).name() << " grew in capacity from " << myCapacity << " to " << aReservedSize << std::endl;
//#endif

			myCapacity = aReservedSize;
		}

	}

	template<typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Resize(SizeType aNewSize, const ObjectType & aFillWith)
	{
		assert(myArray != nullptr && "GROWING ARRAY NOT INITIALIZED!");

		SizeType oldSize = myNrOfItems;

		Reserve(aNewSize);
		
		if (aNewSize >= myCapacity)
		{
			myCapacity = aNewSize;
		}

		if (std::is_trivially_destructible<ObjectType>() == false)
		{
			for (SizeType i = aNewSize; i < myNrOfItems; i++)
			{
				myArray[i] = ObjectType();
			}
		}

		for (SizeType i=oldSize; i<aNewSize; i++)
		{
			myArray[i] = aFillWith;
		}

		myNrOfItems = aNewSize;
	}


}

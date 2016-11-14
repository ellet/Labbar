#pragma once

namespace
ENGINE_NAMESPACE
{
	template <typename TObjectType>
	class MemoryPool
	{
	public:
		MemoryPool(unsigned short aNumberOfObjects)
		{
			myNumberOfObjects = aNumberOfObjects;
			myObjects = reinterpret_cast<TObjectType*>(malloc(sizeof(TObjectType) * aNumberOfObjects));
			memset(&myObjects[0], UINT_MAX, sizeof(TObjectType) * aNumberOfObjects);
			myActiveFlags.Resize(myNumberOfObjects, false);

			for (unsigned short i = 1; i <= myNumberOfObjects; i++)
			{
				myFreeIndices.Push(myNumberOfObjects - i);
			}
		}

		~MemoryPool()
		{
			if (Count() > 0)
			{
				Error("Memory was not returned to memory pool!");
			}

			free(myObjects);
			myObjects = nullptr;
		}

		template <typename TCallback>
		void ForEach(const TCallback& aCallback) const
		{
			for (unsigned short i = 0; i < myNumberOfObjects; i++)
			{
				if (myActiveFlags[i] == true)
				{
					aCallback(myObjects[i]);
				}
			}
		}

		template <typename ...TArgs>
		TObjectType& Allocate(unsigned short* aIndexToSet = nullptr, TArgs && ...aArgs)
		{
			unsigned short index = GetAndActivateIndex();
			memset(&myObjects[index], UINT_MAX, sizeof(TObjectType));
			new(&myObjects[index]) TObjectType(aArgs...);

			if (aIndexToSet != nullptr)
			{
				*aIndexToSet = index;
			}

			return myObjects[index];
		}

		void Free(unsigned short aIndex)
		{
			myObjects[aIndex].~TObjectType();
			myFreeIndices.Push(aIndex);
			myActiveFlags[aIndex] = false;
			memset(&myObjects[aIndex], UINT_MAX, sizeof(TObjectType));
		}

		bool IsFull() const
		{
			return myFreeIndices.Size() == 0;
		}

		bool IsEmpty() const
		{
			return myFreeIndices.Size() == myNumberOfObjects;
		}

		unsigned short Count() const
		{
			return myNumberOfObjects - myFreeIndices.Size();
		}

	private:
		unsigned short GetAndActivateIndex()
		{
			if (myFreeIndices.Size() > 0)
			{
				unsigned short index = myFreeIndices.Pop();
				myActiveFlags[index] = true;
				return index;
			}

			Error("Out of free indices in memory pool!");
		}

		Stack<unsigned short> myFreeIndices;
		GrowingArray<bool> myActiveFlags;
		TObjectType* myObjects;
		unsigned short myNumberOfObjects;
	};

	template <typename TObjectType>
	class DynamicMemoryPool
	{
	public:
		DynamicMemoryPool(unsigned short aGrowSize)
		{
			myGrowSize = aGrowSize;
			NewMemoryPool();
		}

		~DynamicMemoryPool()
		{
			myMemoryPools.DeleteAll();
		}

		template <typename ...TArgs>
		TObjectType& Allocate(unsigned short* aIndexToSet = nullptr, TArgs && ...aArgs)
		{
			for (unsigned short i = 0; i < myMemoryPools.Size(); i++)
			{
				if (myMemoryPools[i]->IsFull() == false)
				{
					unsigned short index;
					TObjectType& object = myMemoryPools[i]->Allocate(&index, aArgs...);
					index += i * myGrowSize;

					if (aIndexToSet != nullptr)
					{
						*aIndexToSet = index;
					}

					return object;
				}
			}

			NewMemoryPool();
			return Allocate(aIndexToSet, aArgs...);
		}

		void Free(unsigned short aIndex)
		{
			unsigned short poolIndex = aIndex / myGrowSize;
			myMemoryPools[poolIndex]->Free(aIndex - poolIndex * myGrowSize);
		}

		template <typename TCallback>
		void ForEach(const TCallback& aCallback) const
		{
			for (unsigned short i = 0; i < myMemoryPools.Size(); i++)
			{
				if (myMemoryPools[i]->IsEmpty() == false)
				{
					myMemoryPools[i]->ForEach(aCallback);
				}
			}
		}

		unsigned short Count() const
		{
			unsigned short sum = 0;
			for (unsigned short i = 0; i < myMemoryPools.Size(); i++)
			{
				sum += myMemoryPools[i]->Count();
			}
			return sum;
		}

	private:
		void NewMemoryPool()
		{
			if (myMemoryPools.Size() >= UINT16_MAX / myGrowSize)
			{
				Error("Upper limit of the dynamic memory pool has been reached. Indexing must be changed to unsigned ints. RIP in peace current project --|-.");
			}

			myMemoryPools.Add(new MemoryPool<TObjectType>(myGrowSize));
		}

		GrowingArray<MemoryPool<TObjectType>*> myMemoryPools;
		unsigned short myGrowSize;
	};
}

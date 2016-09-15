#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H

#include <assert.h>

namespace CommonUtilities
{
	template<typename Type, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray()
		{
			myCurrentSize		= 0;
			myCurrentMaxSize	= 0;
			myUseSafeModeFlag	= true;
		}
		GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true)
		{
			myCurrentMaxSize	= aNrOfRecommendedItems;
			myCurrentSize		= 0;
			myArray				= new Type[myCurrentMaxSize];
			myUseSafeModeFlag	= aUseSafeModeFlag;
		}
		
		GrowingArray(const GrowingArray &aGrowingArray)
		{
			myArray = new Type[aGrowingArray.myCurrentMaxSize];

			if(myUseSafeModeFlag == true)
			{
				memcpy(myArray, aGrowingArray.myArray, sizeof(aGrowingArray.myArray)*(aGrowingArray.myCurrentSize));
			}
			else
			{
				for(SizeType n = 0; n < aGrowingArray.myCurrentSize ; n++)
				{
					myArray[n] = aGrowingArray.myArray[n];
				}
			}

			myCurrentMaxSize	= aGrowingArray.myCurrentMaxSize;
			myCurrentSize		= aGrowingArray.myCurrentSize;
			myUseSafeModeFlag	= aGrowingArray.myUseSafeModeFlag;

		}
		
		~GrowingArray()
		{
			myCurrentSize		= 0;
			myCurrentMaxSize	= 0;
		}

		void operator=(const GrowingArray &aGrowingArray)
		{
			if(myCurrentMaxSize > 0)
			{
				delete []myArray;
			}
			myArray = new Type[aGrowingArray.myCurrentMaxSize];

			if(myUseSafeModeFlag == true)
			{
				memcpy(myArray, aGrowingArray.myArray, sizeof(aGrowingArray.myArray)* aGrowingArray.myCurrentSize);
			}
			else
			{
				for(SizeType n = 0; n < aGrowingArray.myCurrentSize ; n++)
				{
					myArray[n] = aGrowingArray.myArray[n];
				}
			}

			myCurrentMaxSize	= aGrowingArray.myCurrentMaxSize;
			myCurrentSize		= aGrowingArray.myCurrentSize;
			myUseSafeModeFlag	= aGrowingArray.myUseSafeModeFlag;

		}
		
		void Init(SizeType aNumberOfRecommendedItems, bool aUseSafeModeFlag = true)
		{
			myArray = new Type[aNumberOfRecommendedItems];
			myUseSafeModeFlag = aUseSafeModeFlag;
			myCurrentMaxSize = aNumberOfRecommendedItems;
			myCurrentSize = 0;
		}
		
		void ReInit(SizeType aNumberOfRecommendedItems, bool aUseSafeModeFlag = true)
		{
			delete []myArray;
			Init(aNumberOfRecommendedItems, aUseSafeModeFlag);
		}

		inline Type& operator[](const SizeType aIndex)
		{
			assert(aIndex >= 0 && aIndex < myCurrentSize && "OutOfBounds error in GrowingArray::operator[] (nonconst)");
			return myArray[aIndex];
		}
		
		inline const Type& operator[](const SizeType aIndex) const
		{
			assert(aIndex >= 0 && aIndex < myCurrentSize && "OutOfBounds error in GrowingArray::operator[] (const)");
			return myArray[aIndex];
		}
		
		inline void Add(const Type &aObject)
		{
			if(myCurrentSize == myCurrentMaxSize)
			{
				Resize(myCurrentMaxSize*2);
			}
			myArray[myCurrentSize] = aObject;
			myCurrentSize++;
			//Derp, same as in VoS

			//It must happen in "constant time" so that every single 
			//time it is excecuted at the same time
		}

		inline void Insert(SizeType aIndex, const Type &aObject)
		{
			if(myCurrentSize == myCurrentMaxSize)
			{
				Resize(myCurrentMaxSize*2);
			}
			myCurrentSize++;
			for(int n = (myCurrentSize-1) ; n > aIndex; n--)
			{
				myArray[n] = myArray[n-1];
			}
			myArray[aIndex] = aObject;
			//If full, then Resize()
		}
		
		inline void DeleteCyclic(const Type &aObject)
		{
			SizeType index = Find(aObject);

			if(index == -1)
			{
				return;
			}

			delete myArray[index];
			myArray[index] = myArray[myCurrentSize-1];
			myCurrentSize--;

			//Deletes an object, then puts the last object in the array on the deleted spot
			//It assumes that Type is some form of pointer
		}

		inline void DeleteCyclicAtIndex(SizeType aIndex)
		{
			delete myArray[aIndex];
			RemoveCyclicAtIndex(aIndex);
			//Same as ^ but searches for an object instead regardless of position
		}

		inline void RemoveCyclic(const Type &aObject)
		{
			SizeType index = Find(aObject);
			if(index == -1)
			{
				return;
			}
			RemoveCyclicAtIndex(index);
			//Same as ^^ but doesn't delete it before the replacement
		}

		inline void RemoveCyclicAtIndex(SizeType aIndex)
		{
			assert(myCurrentSize != 0 && "Error: Out of bounds error in RemoveCyclicAtIndex");
			myArray[aIndex] = myArray[myCurrentSize-1];
			myCurrentSize--;
		}

		inline void DeleteAll()
		{
			for(SizeType n = 0; n < myCurrentSize; n++)
			{
				delete myArray[n];
			}
			myCurrentSize = 0;
		}

		inline void RemoveAll()
		{
			myCurrentSize = 0;
			//Same as ^ but no deletes
		}

		inline SizeType Find(const Type &aObject, const SizeType FoundNone = -1)
		{
			auto testSubject = aObject;
			for(SizeType n = 0; n < myCurrentSize ;n++)
			{
				if(myArray[n] == testSubject)
				{
					return n;
				}
			}
			return FoundNone;
			//Returns first occuring index of argument object. If none found the function returns FoundNone (-1)
		}
		
		void Optimize()
		{
			Resize(myCurrentSize);

			myCurrentMaxSize = myCurrentSize;
			//Resizes to current number of elements #PERFORMAAAAAAANCE
		}

		__forceinline SizeType Count() const
		{
			return myCurrentSize;

			//it "should work on const instances of this class" too
		}
		
		inline Type& GetLast()
		{
			return myArray[myCurrentSize-1];
		}

	private:
		inline void Resize(const SizeType aNewSize)
		{
			myCurrentMaxSize = aNewSize;
			Type* tempArray = new Type[myCurrentMaxSize];

			SizeType diff = myCurrentMaxSize - myCurrentSize;

			if(diff < 0)
			{
				myCurrentSize += diff;
			}

			if(myUseSafeModeFlag == true)
			{
				memcpy(tempArray, myArray, sizeof(myArray)*myCurrentSize);
			}
			else
			{
				for(int n = 0; n < myCurrentSize; n++)
				{
					tempArray[n] = myArray[n];
				}
			}
			delete []myArray;
			myArray = tempArray;

			//It doubles the current size and moves all the old data locations to the new data location
		}

		Type*		myArray;
		SizeType	myCurrentSize;
		SizeType	myCurrentMaxSize;
		bool		myUseSafeModeFlag;
	};
}

namespace CU = CommonUtilities;

#define GArray CU::GrowingArray

#endif
#pragma once

#pragma message( "Compiled " __FILE__ " on " __DATE__ " at " __TIME__ ) 

#include <assert.h>

namespace ENGINE_NAMESPACE
{
	template <typename Type, int size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class StaticList
	{
	public:
		StaticList();
		StaticList(const StaticList& aStaticList);

		~StaticList();

		StaticList & operator=(const StaticList & aStaticList);

		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);

		inline void RemoveAll();
		inline void DeleteAll();

		inline void RemoveNonCyclic(const Type aObject);

		inline void Resize(const CountType aNewSize, const Type & aFillWith = Type());

		inline CountType Size() const;

		inline Type& GetLast();
		inline const Type& GetLast() const;

	private:
		bool myUseSafeMode;
		Type * myArray;
		CountType mySize;
	};

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	StaticList<Type, size, CountType, UseSafeModeFlag>::StaticList()
	{
		myArray = new Type[size];
		myUseSafeMode = UseSafeModeFlag;
		mySize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	StaticList<Type, size, CountType, UseSafeModeFlag>::~StaticList()
	{
		myArray = new Type[size];
		mySize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	StaticList<Type, size, CountType, UseSafeModeFlag>::
		StaticList(const StaticList& aStaticList)
	{
		*this = aStaticList;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	StaticList<Type, size, CountType, UseSafeModeFlag>&
		StaticList<Type, size, CountType, UseSafeModeFlag>::
		operator=(const StaticList& aStaticList)
	{
		if (myUseSafeMode == true)
		{
			for (CountType i = 0; i < aStaticList.Size(); i++)
			{
				myArray[i] = aStaticList[i];
			}
			mySize = aStaticList.Size();
		}
		else
		{
			memcpy(this, &aStaticList, sizeof(aStaticList));
		}
		return *this;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	Type&  StaticList<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType& aIndex)
	{
		assert((aIndex >= 0 && aIndex < mySize) && "INDEX OUT OF BOUNDS!");
		return myArray[aIndex];
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	const Type&  StaticList<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType& aIndex) const
	{
		assert((aIndex >= 0 && aIndex < mySize) && "INDEX OUT OF BOUNDS!");
		return myArray[aIndex];
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(mySize < size && "ARRAY IS FULL!");
		myArray[mySize++] = aObject;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::Insert(CountType aIndex, Type& aObject)
	{
		assert((aIndex >= 0 && aIndex <= mySize && aIndex < size) && "INDEX OUT OF BOUNDS!"); 
		for (CountType i = size - 1; i > aIndex; i--)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[aIndex] = aObject;
		++mySize;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::DeleteCyclic(Type& aObject)
	{
		CountType i = 0;
		while (i <= size)
		{		
			if (myArray[i] == aObject)
			{
				break;
			}
			++i;
		}
		assert(myArray[i] == aObject && "OBJECT NOT FOUND");	
		delete(myArray[i]);
		myArray[i] = nullptr;
		if (i < mySize - 1)
		{
			myArray[i] = myArray[--mySize];
		}
		else
		{
			--mySize;
		}
	}
	
	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert((aItemNumber >= 0 && aItemNumber < mySize) && "INDEX OUT OF BOUNDS!");
		delete(myArray[aItemNumber]);
		myArray[aItemNumber] = nullptr;

		if (aItemNumber < mySize - 1)
		{
			myArray[aItemNumber] = myArray[--mySize];
		}
		else
		{
			--mySize;
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		CountType i = 0;
		while (i < mySize)
		{			
			if (myArray[i] == aObject)
			{
				break;
			}
			++i;
		}
		assert(myArray[i] == aObject && "OBJECT NOT FOUND");

		if (i < mySize)
		{
			myArray[i] = myArray[--mySize];
		}
		else
		{
			--mySize;
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		assert((aItemNumber >= 0 && aItemNumber < mySize) && "INDEX OUT OF BOUNDS!");

		if (aItemNumber < mySize - 1)
		{
			myArray[aItemNumber] = myArray[--mySize];
		}
		else
		{
			--mySize;
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (CountType i = 0; i < mySize; i++)
		{
			delete(myArray[i]);
			myArray[i] = nullptr;
		}
		mySize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::RemoveAll()
	{
		if (std::is_trivially_destructible<Type>() == false)
		{
			for (CountType i = 0; i < mySize; i++)
			{
				myArray[i] = Type();
			}
		}
		mySize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::RemoveNonCyclic(const Type aObject)
	{
		CountType i = mySize-1;
		while (i > 0)
		{
			if (myArray[i] == aObject)
			{
				break;
			}
			--i;
		}
		if (myArray[i] != aObject)
		{
			return;
		}
		if (i < mySize)
		{
			for (CountType j = i; j < mySize - 1; ++j)
			{
				myArray[j] = myArray[j + 1];
			}
		}

		--mySize;
	}

	template <typename Type, int size, typename CountType /*= unsigned short*/, bool UseSafeModeFlag /*= true*/>
	void StaticList<Type, size, CountType, UseSafeModeFlag>::Resize(const CountType aNewSize, const Type & aFillWith /*= Type()*/)
	{
		assert(aNewSize <= size && "StaticList is trying to resize to more than it's set size");

		CountType oldSize = mySize;

		if (std::is_trivially_destructible<Type>() == false)
		{
			for (CountType i = aNewSize; i < mySize; i++)
			{
				myArray[i] = Type();
			}
		}

		for (CountType i = oldSize; i < aNewSize; i++)
		{
			myArray[i] = aFillWith;
		}

		mySize = aNewSize;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	CountType StaticList<Type, size, CountType, UseSafeModeFlag>::Size() const
	{
		return mySize;
	}

	template <typename Type, int size, typename CountType /*= unsigned short*/, bool UseSafeModeFlag /*= true*/>
	Type& ENGINE_NAMESPACE::StaticList<Type, size, CountType, UseSafeModeFlag>::GetLast()
	{
		return (myArray[mySize - 1]);
	}


	template <typename Type, int size, typename CountType /*= unsigned short*/, bool UseSafeModeFlag /*= true*/>
	const Type& ENGINE_NAMESPACE::StaticList<Type, size, CountType, UseSafeModeFlag>::GetLast() const
	{
		return (myArray[mySize - 1]);
	}

}
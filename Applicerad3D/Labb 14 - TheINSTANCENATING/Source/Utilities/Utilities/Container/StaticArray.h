#pragma once

#pragma message( "Compiled " __FILE__ " on " __DATE__ " at " __TIME__ ) 


#include <assert.h>

namespace CommonUtilities
{
	template <typename Type, int size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		StaticArray& operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);


		// Utility functions
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();
	private:
		Type myArray[size];
		unsigned short myAmount;
	};
	template <typename Type, int size>
	StaticArray<Type, size>::StaticArray()
	{

	}

	template <typename Type, int size>
	StaticArray<Type, size>::~StaticArray()
	{

	}

	template <typename Type, int size>
	StaticArray<Type, size>::StaticArray(const StaticArray& aStaticArray)
	{
		*this = aStaticArray;
	}

	template <typename Type, int size>
	StaticArray<Type, size>& StaticArray<Type, size>::operator=(const StaticArray& aStaticArray)
	{
		for (size_t i = 0; i < size; i++)
		{
			myArray[i] = aStaticArray[i];
		}
		return *this;
	}

	template <typename Type, int size>
	Type&  StaticArray<Type, size>::operator[](const int& aIndex)
	{
		assert((aIndex >= 0 && aIndex < size) && "INDEX OUT OF BOUNDS!");
		return myArray[aIndex];
	}

	template <typename Type, int size>
	const Type&  StaticArray<Type, size>::operator[](const int& aIndex) const
	{
		assert((aIndex >= 0 && aIndex < size) && "INDEX OUT OF BOUNDS!");
		return myArray[aIndex];
	}



	template <typename Type, int size>
	void StaticArray<Type, size>::Insert(int aIndex, Type& aObject)
	{
		for (int i = size-1; i > aIndex; i--)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[aIndex] = aObject;
	}

	template <typename Type, int size>
	void StaticArray<Type, size>::DeleteAll()
	{
		for (size_t i = 0; i < size; i++)
		{
			delete (myArray[i]);
			myArray[i] = nullptr;
		}
	}
} namespace CU = CommonUtilities;
#include <cassert>

namespace CommonUtilities
{
	template <typename Type, int Size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		//StaticArray& operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);


		// Utility functions
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();

	private:
		Type myData[Size];
		int mySize = Size - 1;
	};
}

template <typename Type, int Size>
const Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
{
	assert(aIndex <= mySize && "Index is out of range");
	assert(aIndex > 0 && "Index can not be a negative number");

	return myData[aIndex];
}

template <typename Type, int Size>
Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
{
	assert(aIndex <= mySize && "Index is out of range");
	assert(aIndex > 0 && "Index can not be a negative number");

	return myData[aIndex];
}

template <typename Type, int Size>
void StaticArray<Type, Size>::Insert(int aIndex, Type& aObject)
{
	assert(aIndex <= mySize && "Index is out of range");
	assert(aIndex > 0 && "Index can not be a negative number");
	

	if (aIndex != mySize)
	{
		for (size_t iData = aIndex; iData < mySize; ++iData)
		{
			myData[iData + 1] = myData[iData];
		}
	}

	myData[aIndex] = aObject;
}

template <typename Type, int Size>
void StaticArray<Type, Size>::DeleteAll()
{
	for (size_t iData = 0; iData <= mySize; ++IData)
	{
		delete myData[iData];
		myData[iData] = nullptr;
	}
}

//StaticArray& operator=(const StaticArray& aStaticArray);
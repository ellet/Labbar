#ifndef CU_STATICARRAY_H
#define CU_STATICARRAY_H

#include "Assert.h"

namespace CommonUtilities
{
	template <typename DataType,unsigned int StaticSize>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aCopy);
		~StaticArray();

		const StaticArray&		operator=(const StaticArray& aStaticArray);
		inline DataType&		operator[](const unsigned int& aIndex);
		inline const DataType&	operator[](const unsigned int& aIndex) const;

	private:
		DataType				myArray[StaticSize];
	};


	template <typename DataType,unsigned int StaticSize>
	StaticArray<DataType,StaticSize>::StaticArray()
	{
	}

	template <typename DataType,unsigned int StaticSize>
	StaticArray<DataType,StaticSize>::~StaticArray()
	{
	}

	template <typename DataType, unsigned int StaticSize>
	StaticArray<DataType,StaticSize>::StaticArray(const StaticArray& aCopy)
	{
		for(unsigned int counter = 0; counter < StaticSize; counter++)
			myArray[counter] = aCopy[counter];
	}

	template <typename DataType,unsigned int StaticSize>
	const StaticArray<DataType,StaticSize>& StaticArray<DataType,StaticSize>::operator=(const StaticArray<DataType,StaticSize>& aStaticArray)
	{
		for(unsigned int counter = 0; counter < StaticSize; counter++)
			myArray[counter]=aStaticArray.myArray[counter];

		return(*this);
	}

	template <typename DataType,unsigned int StaticSize>
	DataType& StaticArray<DataType,StaticSize>::operator[](const unsigned int& aIndex)
	{
		assert((aIndex >= 0 && aIndex < StaticSize) && "ERROR, Attempted to access element out of range for StaticArray");
		return(myArray[aIndex]);
	}

	template <typename DataType,unsigned int StaticSize>
	const DataType& StaticArray<DataType,StaticSize>::operator[](const unsigned int& aIndex) const
	{
		assert((aIndex >= 0 && aIndex < StaticSize) && "ERROR, Attempted to access element out of range for StaticArray");
		return(myArray[aIndex]);
	}
};

namespace CU = CommonUtilities;

#endif

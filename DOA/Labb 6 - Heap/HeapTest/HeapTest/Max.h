#ifndef MAX_HEADER
#define MAX_HEADER

namespace CommonUtilities
{
	template<class Type>
	class Max
	{
	public:

		Max(void);
		Max(const Type& aValue);
		~Max(void);

		bool operator==(const Max& aMaxValue);
		bool operator<(const Max& aMaxValue);
		Type myValue;
	};

	template<class Type>
	Max<Type>::Max(void)
	{
	}

	template<class Type>
	Max<Type>::Max(const Type& aValue)
	{
		myValue = aValue;
	}

	template<class Type>
	Max<Type>::~Max(void)
	{
	}
	template<class Type>
	bool Max<Type>::operator==(const Max& aMaxValue)
	{
		if(aMaxValue.myValue == this->myValue)
		{
			return true;
		}
		return false;
	}

	template<class Type>
	bool Max<Type>::operator<(const Max& aMaxValue)
	{
		if(aMaxValue.myValue < this->myValue)
		{
			return false;
		}
		return true;
	}
};
#endif
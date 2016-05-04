#ifndef MIN_HEADER
#define MIN_HEADER

namespace CommonUtilities
{
	template<class Type>
	class Min
	{
	public:

		Min(void);
		Min(const Type& aValue);
		~Min(void);

		bool operator==(const Min& aMinValue);
		bool operator<(const Min& aMinValue);
		Type myValue;
	};

	template<class Type>
	Min<Type>::Min(void)
	{
	}

	template<class Type>
	Min<Type>::Min(const Type& aValue)
	{
		myValue = aValue;
	}

	template<class Type>
	Min<Type>::~Min(void)
	{
	}
	template<class Type>
	bool Min<Type>::operator==(const Min& aMinValue)
	{
		if(aMinValue.myValue == this->myValue)
		{
			return true;
		}
		return false;
	}

	template<class Type>
	bool Min<Type>::operator<(const Min& aMinValue)
	{
		if(aMinValue.myValue < this->myValue)
		{
			return true;
		}
		return false;
	}
};
#endif
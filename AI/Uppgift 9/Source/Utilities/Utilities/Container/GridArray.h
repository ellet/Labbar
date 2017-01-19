#pragma once

namespace SB
{

	template <typename T, typename CountType = unsigned short>
	class GridArray
	{
	public:
		GridArray(CountType aWidth, CountType aHeight, const bool aRunConstructors = true);
		
		void SetSizeClear(CountType aWidth, CountType aHeight, const bool aClearFlag = true);
		
		inline T & Access(const CountType& aX, const CountType& aY);
		inline const T Access(const CountType& aX, const CountType& aY) const;
		
		GrowingArray<T, CountType> & GetArray()
		{
			return myArray;
		}

		const GrowingArray<T, CountType> & GetArray() const
		{
			return myArray;
		}

		inline void Optimize();
		__forceinline CountType Width() const;
		__forceinline CountType Height() const;

	private:

		GrowingArray<T, CountType> myArray;
		CountType myWidth;
		CountType myHeight;
	};

	template <typename T, typename CountType /*= unsigned short*/>
	void GridArray<T, CountType>::Optimize()
	{
		myArray.Optimize();
	}

	template <typename T, typename CountType /*= unsigned short*/>
	GridArray<T, CountType>::GridArray(CountType aWidth, CountType aHeight, const bool aRunConstructors/* = true*/) :
		myArray(aWidth * aHeight)
	{
		SetSizeClear(aWidth, aHeight, aRunConstructors);
	}

	template <typename T, typename CountType /*= unsigned short*/>
	void GridArray<T, CountType>::SetSizeClear(CountType aWidth, CountType aHeight, const bool aClearFlag/* = false*/)
	{
		myWidth = aWidth;
		myHeight = aHeight;
		myArray.Resize(myWidth * myHeight);

		if (aClearFlag == true)
		{
			for (CountType iSlot = 0; iSlot < myArray.Size(); ++iSlot)
			{
				myArray[iSlot] = T();
			}
		}
	}

	template <typename T, typename CountType /*= unsigned short*/>
	T & GridArray<T, CountType>::Access(const CountType& aX, const CountType& aY)
	{
		if ((aX + (aY * myWidth)) >= myArray.Size())
		{
			Error("Trying to access GridArrayPosition that is out of range");
		}
		
		return myArray[aX + (aY * myWidth)];
	}

	template <typename T, typename CountType /*= unsigned short*/>
	const T GridArray<T, CountType>::Access(const CountType& aX, const CountType& aY) const
	{
		if ((aX + (aY * myWidth)) >= myArray.Size())
		{
			Error("Trying to access GridArrayPosition that is out of range");
		}

		return myArray[aX + (aY * myWidth)];
	}

	template <typename T, typename CountType /*= unsigned short*/>
	CountType GridArray<T, CountType>::Height() const
	{
		return myHeight;
	}

	template <typename T, typename CountType /*= unsigned short*/>
	CountType GridArray<T, CountType>::Width() const
	{
		return myWidth;
	}

}
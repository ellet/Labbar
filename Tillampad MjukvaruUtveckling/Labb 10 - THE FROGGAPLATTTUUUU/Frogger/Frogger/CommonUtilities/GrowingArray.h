#ifndef GROWINGARRAY_HEADER
#define GROWINGARRAY_HEADER


//////////////////////////////////////////////////////////////////////////
//																		//
//		Instructions!													//
//																		//
//		Open 'autoexp.dat' found from the filepath below as a textfile	//
//		Copy the code segment seen below and paste it CountTypeo the	//
//		file below the header '[Visualizer]'. This will allow you to	//
//		access better debug info from the typename.						//
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////

//C:\Program Files\Microsoft Visual Studio 9.0\Common7\Packages\Debugger\autoexp.dat
/*
;------------------------------------------------------------------------------
;  CommonUtilities::GrowingArray
;------------------------------------------------------------------------------
CommonUtilities::GrowingArray<*>{
	children
	(
		#(
			[Details]: [$c,!],
			#array
			(
				expr :		($e.myItemList)[$i],
				size :		$e.myLastItem-$e.myItemList
			)
		)
	)
	preview
	(
		#(
			"[", $e.myLastItem - $e.myItemList , "](",
				#array
				(
					expr :	($e.myItemList)[$i],
					size :	$e.myLastItem-$e.myItemList
				), 
			")"
		)
	)
}
*/
#include "LoopMacros.h"
#include "CommonMacros.h"
#include "assert.h"
#include <iostream>

namespace CommonUtilities
{
	template <typename DataType,typename CountType = unsigned int>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(CountType aMaximumCapacity, CountType aGrowthFactor, bool aUseSafeModeFlag=true);
		GrowingArray(const GrowingArray& aGrowingArray);
		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);


		void 				ReInit(CountType aMaximumCapacity, CountType aGrowthFactor,bool aUseSafeModeFlag=true);

		inline DataType&	GetLast() const;

		inline void			Add(const DataType& aObject);
		inline void 		InsertAtIndex(CountType aIndex,const DataType& aObject);
		
		inline void 		DeleteCyclic(DataType& aObject);
		inline void 		DeleteCyclicAtIndex(CountType aIndex);
		
		inline void			DeleteKeepPriorityAtIndex(CountType aIndex);		
		inline void			DeleteKeepPriority(DataType& aObject);				
		
		inline void 		RemoveCyclic(const DataType& aObject);            
		inline void 		RemoveCyclicAtIndex(CountType aIndex);		
		
		inline void			RemoveKeepPriorityAtIndex(CountType aIndex);		
		inline void			RemoveKeepPriority(DataType& aObject);				

		inline void 		RemoveAll();
		inline void 		DeleteAll();

		void				Optimize();
		inline CountType	Count() const;
		inline CountType	Capacity();
		inline bool			Contains(const DataType& aObject);

		inline DataType& 	operator[](const CountType& aIndex) const;
		inline DataType& 	operator[](const CountType& aIndex);
        inline DataType&    At(const CountType& aIndex);
        inline DataType&    At(const CountType& aIndex) const;
	protected:
		void 				Init(CountType aMaximumCapacity,CountType aGrowthFactor,bool aUseSafeModeFlag=true);
		inline void			ReSize(CountType aNewSize);

		DataType* 			myItemList;
		DataType* 			myLastItem;
		CountType 			myCurNrOfItems;
		CountType 			myMaxNrOfItems;
		CountType 			myGrowthFactor;
		bool				myUseSafeModeFlag;

	};

	template <typename DataType,typename CountType>
	GrowingArray<DataType,CountType>::GrowingArray()
	{
		myItemList			= NULL;
		myLastItem			= myItemList;
		myCurNrOfItems		= 0;
		myMaxNrOfItems		= 64;
		myGrowthFactor		= 64;
		myUseSafeModeFlag	= true;
		Init(myMaxNrOfItems, myGrowthFactor, myUseSafeModeFlag);

	}

	template <typename DataType,typename CountType>
	GrowingArray<DataType,CountType>::GrowingArray(CountType aMaximumCapacity, CountType aGrowthFactor, bool aUseSafeModeFlag/* =true */)
	{
		myItemList			= NULL;
		myLastItem			= myItemList;
		myCurNrOfItems		= 0;
		myUseSafeModeFlag	= aUseSafeModeFlag;
		Init(aMaximumCapacity, aGrowthFactor);
	}

	template <typename DataType,typename CountType>
	GrowingArray<DataType,CountType>::GrowingArray(const GrowingArray<DataType,CountType>& aGrowingArray)
	{
		myItemList=NULL;
		*this=aGrowingArray;
	}

	template <typename DataType,typename CountType>

	GrowingArray<DataType,CountType>& GrowingArray<DataType,CountType>::operator=(const GrowingArray<DataType,CountType>& aGrowingArray)
	{
		if(myItemList==NULL)
		{
			Init(aGrowingArray.myMaxNrOfItems,aGrowingArray.myGrowthFactor,aGrowingArray.myUseSafeModeFlag);
		}
		else
		{
			ReInit(aGrowingArray.myMaxNrOfItems,aGrowingArray.myGrowthFactor,aGrowingArray.myUseSafeModeFlag);
		}

		if(myUseSafeModeFlag==true)
		{
			for(CountType i=0;i<aGrowingArray.Count();i++)
			{
				myItemList[i]=aGrowingArray[i];
			}
		}
		else
		{
			memcpy(myItemList,&aGrowingArray[0],aGrowingArray.Count()*sizeof(DataType));
		}
		myCurNrOfItems = static_cast<CountType>(aGrowingArray.Count());
		myLastItem = &myItemList[myCurNrOfItems];
		return(*this);
	}



	template <typename DataType,typename CountType>
	GrowingArray<DataType,CountType>::~GrowingArray()
	{
		RemoveAll();
		myLastItem=NULL;
		if(myItemList!=NULL)
		{
			delete [] myItemList;
		}
		myItemList=NULL;

	}


	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::Init(CountType aMaximumCapacity,CountType aGrowthFactor,bool aUseSafeModeFlag/* =true */)
	{
		assert(myItemList==NULL && "CALLED INIT ON AN ALREADY INITED GROWINGARRAY PLEASE USE REINIT");

		myMaxNrOfItems=aMaximumCapacity;
		myGrowthFactor=aGrowthFactor;
		myUseSafeModeFlag=aUseSafeModeFlag;
		myCurNrOfItems=0;

		myItemList = new DataType[myMaxNrOfItems]();
		myLastItem = myItemList;
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::ReInit(CountType aMaximumCapacity, CountType aGrowthFactor,bool aUseSafeModeFlag/* =true */)
	{
		assert(myItemList!=NULL && "CALLED REINIT ON AN UNINITED GROWINGARRAY PLEASE USE INIT");

		delete [] (myItemList);

		myMaxNrOfItems=static_cast<CountType>(aMaximumCapacity);
		myGrowthFactor=static_cast<CountType>(aGrowthFactor);
		myUseSafeModeFlag=aUseSafeModeFlag;
		myCurNrOfItems=0;

		myItemList = new DataType [myMaxNrOfItems] ();
		myLastItem = myItemList;
	}

    template <typename DataType,typename CountType>
    DataType& GrowingArray<DataType,CountType>::At(const CountType& aIndex)
    {
		return(myItemList[aIndex]);
    }
    
    template <typename DataType,typename CountType>
    DataType& GrowingArray<DataType,CountType>::At(const CountType& aIndex) const
    {
		return(myItemList[aIndex]);
    }

	template <typename DataType,typename CountType>
	DataType& GrowingArray<DataType,CountType>::operator[](const CountType& aIndex) const 
	{
		assert((aIndex>=0) && (aIndex<static_cast<CountType>(myCurNrOfItems)) && "GROWING ARRAY: OUT OF BOUNDS ERROR");
		return(myItemList[aIndex]);
	}

	template <typename DataType,typename CountType>
	DataType& GrowingArray<DataType,CountType>::operator[](const CountType& aIndex)
	{
		assert((aIndex>=0) && (aIndex<static_cast<CountType>(myCurNrOfItems)) && "GROWING ARRAY: OUT OF BOUNDS ERROR");
		return(myItemList[aIndex]);
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::Add(const DataType& aItem)
	{
		if(myCurNrOfItems==myMaxNrOfItems) ReSize(myMaxNrOfItems+myGrowthFactor);
		myItemList[myCurNrOfItems]=aItem;
		myCurNrOfItems++;
		myLastItem = &myItemList[myCurNrOfItems];
	}


	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::DeleteCyclic(DataType& aItem)
	{
		For_Count_i(myCurNrOfItems)
		{
			if(myItemList[i]==aItem)
			{
				delete(myItemList[i]);
				myItemList[i]=myItemList[myCurNrOfItems-1];
				myCurNrOfItems--;
				myLastItem = &myItemList[myCurNrOfItems];
				return;
			}
		}

	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		SAFE_DELETE(myItemList[aItemNumber]);
		myItemList[aItemNumber] = NULL; 
		myItemList[aItemNumber]=myItemList[myCurNrOfItems-1];
		myCurNrOfItems--;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::DeleteKeepPriorityAtIndex(CountType aIndex)
	{
		delete(myItemList[aIndex]);
		for(CountType i = aIndex; i < myCurNrOfItems; i++)
		{
			myItemList[i] = myItemList[i+1];
		}
		myCurNrOfItems--;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	
	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::DeleteKeepPriority(DataType& aObject)
	{
		for(CountType i = 0; i < myCurNrOfItems; i++)
		{
			if(aObject == myItemList[i])
			{
				delete(myItemList[i]);
				for(CountType j = i; j < myCurNrOfItems; j++)
				{
					myItemList[j] = myItemList[j+1];
				}
				myCurNrOfItems--;
				myLastItem = &myItemList[myCurNrOfItems];
				break;
			}
		}
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::RemoveCyclic(const DataType& aItem) 
	{
		for(CountType i = 0; i < myCurNrOfItems; i++)
		{
			if(myItemList[i]==aItem)
			{
				myItemList[i]=myItemList[myCurNrOfItems-1];
				myCurNrOfItems--;
				myLastItem = &myItemList[myCurNrOfItems];
				return;
			}
		}
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		//if (aItemNumber != myCurNrOfItems - 1)
		//{
			myItemList[aItemNumber] = myItemList[myCurNrOfItems - 1];
		//}

		myCurNrOfItems--;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::RemoveKeepPriorityAtIndex(CountType aIndex)
	{
		for(CountType i = aIndex; i < myCurNrOfItems; i++)
		{
			myItemList[i] = myItemList[i+1];
		}
		myCurNrOfItems--;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::RemoveKeepPriority(DataType& aObject)
	{
		for(CountType i = 0; i < myCurNrOfItems; i++)
		{
			if(aObject == myItemList[i])
			{
				for(CountType j = i; j < myCurNrOfItems; j++)
				{
					myItemList[j] = myItemList[j+1];
				}
				myCurNrOfItems--;
				myLastItem = &myItemList[myCurNrOfItems];
				break;
			}
		}
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::InsertAtIndex(CountType aIndex,const DataType& aObject)
	{
		if(myCurNrOfItems==myMaxNrOfItems) ReSize(myMaxNrOfItems+myGrowthFactor);
		for(CountType i=myCurNrOfItems;i>aIndex;i--)
		{
			myItemList[i]=myItemList[i-1];
		}
		myItemList[aIndex]=aObject;
		myCurNrOfItems++;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::RemoveAll()
	{
		myCurNrOfItems=0;
		myLastItem = myItemList;
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::DeleteAll()
	{
		for(CountType i = 0; i < myCurNrOfItems; i++)
		{
			delete myItemList[i];
			myItemList[i]=NULL;
		}
		myCurNrOfItems=0;
		myLastItem = myItemList;

	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::Optimize()
	{
		ReSize(myCurNrOfItems);
	}

	template <typename DataType,typename CountType>
	CountType GrowingArray<DataType,CountType>::Count() const
	{
 		return(myCurNrOfItems);
	}

	template <typename DataType, typename CountType>
	CountType GrowingArray<DataType,CountType>::Capacity()
	{
		return(myMaxNrOfItems);
	}

	template <typename DataType, typename CountType>
	bool GrowingArray<DataType,CountType>::Contains(const DataType& aObject)
	{
		for(CountType i = 0; i < myCurNrOfItems; i++)
		{
			if(myItemList[i] == aObject)
			{
				return(true);
			}
		}

		return(false);
	}

	template <typename DataType,typename CountType>
	void GrowingArray<DataType,CountType>::ReSize(CountType aNewSize)
	{
		assert(aNewSize != 0 && "GROWING ARRAY: NEW SIZE IS ZERO");

		DataType* tempList=new DataType[aNewSize] ();
		if(myUseSafeModeFlag==true)
		{
			for(CountType i=0;i<static_cast<CountType>(myCurNrOfItems);i++)
			{
				tempList[i]=myItemList[i];
			}
		}
		else
		{
			memcpy(tempList,myItemList,myCurNrOfItems*sizeof(DataType*));
		}
		delete [] (myItemList);
		myMaxNrOfItems=static_cast<CountType>(aNewSize);
		myItemList=tempList;
		myLastItem = &myItemList[myCurNrOfItems];
	}

	template <typename DataType,typename CountType>
	DataType& GrowingArray<DataType,CountType>::GetLast() const
	{
		return myItemList[myCurNrOfItems-1];
	}
}

#endif
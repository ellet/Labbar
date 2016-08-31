#pragma once

#include "CU/ObjectCreationDatabase/BaseObjectData.h"

class ObjectCreationDatabase
{
public:
	ObjectCreationDatabase();
	~ObjectCreationDatabase();

	void AddData(const std::string & aDataKey,const BaseObjectData & aDataObject);
	
	template<typename StructType>
	const StructType & GetData(const std::string & aDataKey) const;

private:
	std::unordered_map<std::string, const BaseObjectData*> myData;
};

template<typename StructType>
const StructType & ObjectCreationDatabase::GetData(const std::string & aDataKey) const
{
	return *dynamic_cast<StructType*>(myData[aDataKey]);
}
#include "stdafx.h"
#include "ObjectCreationDatabase.h"


ObjectCreationDatabase::ObjectCreationDatabase()
{
}


ObjectCreationDatabase::~ObjectCreationDatabase()
{
}

void ObjectCreationDatabase::AddData(const std::string & aDataKey, const BaseObjectData & aDataObject)
{
	myData[aDataKey] = &aDataObject;
}
#include "stdafx.h"
#include "PrefabDatabase.h"
#include "GameObject.h"

namespace ENGINE_NAMESPACE
{

	//std::unordered_map<std::string, DataNodeCopy> PrefabDatabase::ourPrefabs;
	DataDocument PrefabDatabase::ourPrefabs;
	std::unordered_map<std::string, unsigned short> PrefabDatabase::ourPrefabsIndices;

	PrefabDatabase::PrefabDatabase()
	{}

	PrefabDatabase::~PrefabDatabase()
	{}

	void PrefabDatabase::AddGlobalPrefabs(const std::string & aFilePath)
	{
		Data::Open(aFilePath, ourPrefabs);

		unsigned short objectCount = static_cast<unsigned short>(ourPrefabs["hierarchy"].Capacity());

		for (unsigned short i = 0; i < objectCount; ++i)
		{
			ourPrefabsIndices[ourPrefabs["hierarchy"][i]["name"].GetString()] = i;
		}
	}

	/*void PrefabDatabase::AddGlobalPrefab(const DataNode aPrefab)
	{
		
	}*/

	const DataNode & PrefabDatabase::GetGlobalPrefab(const std::string & aPrefabID) const
	{
		if (ourPrefabsIndices.find(aPrefabID) == ourPrefabsIndices.end())
		{
			Error("Vafan! " + aPrefabID + " prefaben fanns ju inte");
		}

		return ourPrefabs["hierarchy"][ourPrefabsIndices[aPrefabID]];
	} 

	

}

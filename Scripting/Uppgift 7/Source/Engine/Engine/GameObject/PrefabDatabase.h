#pragma once
//#include "Engine\DataParser\DataParser.h"

namespace SB
{
	class GameObject;

	class PrefabDatabase
	{
	public:
		PrefabDatabase();
		~PrefabDatabase();

		void AddGlobalPrefabs(const std::string & aFilePath = "Assets/Data/Prefabs/Prefabs.json");
		//void AddGlobalPrefab(const DataNode aPrefab);
		const DataNode & GetGlobalPrefab(const std::string & aPrefabID) const;


	private:
		static DataDocument ourPrefabs;
		static std::unordered_map<std::string, unsigned short> ourPrefabsIndices;
		//static std::unordered_map<std::string, DataNodeCopy> ourPrefabs;
	};
}

#include "stdafx.h"
#include "PrefabScene.h"
#include "..\Component\ComponentRegistry.h"
#include "..\DataParser\DataParser.h"
#include "..\GameObject\GameObjectFactory.h"


namespace SB
{
	PrefabScene::PrefabScene(PostMasterState & aPostMasterState)
		: Scene(aPostMasterState, "Prefab Scene")
	{
	}


	PrefabScene::~PrefabScene()
	{
	}

	void PrefabScene::LoadPrefabs(const std::string & aFileForPrefabList /*= "Assets/Data/Prefabs/Prefabs.json"*/)
	{
		myGameObjectFactory->LoadPrefabs(aFileForPrefabList);
		
	}
}

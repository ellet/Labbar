#pragma once
#include "Scene.h"



namespace ENGINE_NAMESPACE
{
	class PrefabScene
		: public Scene
	{
	public:
		PrefabScene(PostMasterState & aPostMasterState);
		~PrefabScene();

		void LoadPrefabs(const std::string & aFileForPrefabList = "Assets/Data/Prefabs/Prefabs.json" );
	};
}
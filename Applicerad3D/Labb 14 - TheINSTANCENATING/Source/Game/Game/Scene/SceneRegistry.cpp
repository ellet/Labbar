#include "stdafx.h"
#include "SceneRegistry.h"
#include "MainMenuScene.h"
#include "CreditScene.h"
#include "OptionsScene.h"
#include "ModelViewerScene\ModelViewerScene.h"
#include "TestScenes\TestCollision\CollisionTestScene.h"
#include "ParticleEditorScene\ParticleEditorScene.h"
#include <Engine/Scene/SceneManager.h>
#include "TestScenes\SpriteInstancingScene.h"

namespace Debug
{

	void RegisterGameScenes()
	{
		SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<SB::ModelViewerScene>());
		SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<CollisionTestScene>());
		SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<SpriteInstancingScene>());
		//SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<ParticleEditorScene>());
	}

}

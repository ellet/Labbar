#include "stdafx.h"
#include "SceneRegistry.h"
#include "CreditsScene.h"
#include "ModelViewerScene\ModelViewerScene.h"
#include "ParticleEditorScene\ParticleEditorScene.h"
#include <Engine/Scene/SceneManager.h>

namespace Debug
{

	void RegisterGameScenes()
	{
		SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<SB::ModelViewerScene>());
		SB::Engine::GetDebugger().AddSceneForSceneSelection(SB::NewSceneBindBeforeDeletion<ParticleEditorScene>());
	}

}

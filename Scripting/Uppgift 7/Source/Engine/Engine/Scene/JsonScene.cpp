#include "stdafx.h"
#include "JsonScene.h"
#include "Engine\GUI\GUILoader.h"
#include "Engine/GenericEngineMessages.h"
#include "..\Engine\Engine\GUI/RootGUIElement.h"
#include "Engine/Texture/RenderTexture.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Texture/WorldRenderTexture.h"
#include "..\Camera\Controllers\FreeSpaceCameraController.h"

namespace SB
{

	JsonScene::JsonScene(PostMasterState & aPostMasterState, const char* aFilePath, const char* aSkyBoxFilePath) : Scene(aPostMasterState, aFilePath, aSkyBoxFilePath)
	{	
		SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
		myCamera->GetRenderTexture()->GetModelRenderer().SetDirectionalLight(0, SB::Vector3f::UnitZ, SB::Vector4f(1.f, 1.f, 1.f, 1.f));
		SetCameraOrientation(SB::Vector3f::Zero);
		myCamera->GetRenderTexture()->GetModelRenderer().SetDirectionalLight(0, Vector3f(1.f, -1.f, 0.f), SB::Vector4f::One);

		myGUI = Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/InGame.json");
	}


	JsonScene::~JsonScene()
	{
	}

	void JsonScene::Update(const Time & aDeltaTime)
	{
		Scene::Update(aDeltaTime);
	}
	
	void JsonScene::RenderGui()
	{
		Scene::RenderGui();
	}

	void JsonScene::OnEnter()
	{
		myGUI = Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/InGame.json");
		
		PostMaster::Post(ShowCursorMessage(false));
		PostMaster::Post(EnterSceneMessage(GetName().c_str()));
		PostMaster::Post(ConfineMouseMessage(true));
	}

	//PRIVATE FUNCTIONS:

}

#include "stdafx.h"
#include "JsonScene.h"
#include "..\Game\Game\Player\PlayerControllerComponent.h"
#include "..\SoundManager\SoundManager.h"

#include "Engine\GUI\GUILoader.h"
#include "Engine/Rendering/SpriteRenderer.h"
#include "Engine/Sprite/SpriteEffect.h"
#include "Engine/GenericEngineMessages.h"


class DrawWarpDriveEvent
{};
class DrawCockpitEvent
{};

namespace ENGINE_NAMESPACE
{

	JsonScene::JsonScene(PostMasterState & aPostMasterState, const char* aFilePath) : Scene(aPostMasterState, aFilePath)
	{	
		Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");

		Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, SB::Vector3f::UnitZ, SB::Vector4f(1.f, 1.f, 1.f, 1.f));

		myGUI = Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/testGUI.json");
	}


	JsonScene::~JsonScene()
	{
	}

	void JsonScene::Update(const Time & aDeltaTime)
	{
		Scene::Update(aDeltaTime);
	}
	
	void JsonScene::Render()
	{
		Scene::Render();

		PostMaster::Post(DrawWarpDriveEvent());
		PostMaster::Post(DrawCockpitEvent());
	}

	void JsonScene::RenderGui()
	{
		PostMaster::Post(DrawCrosshairEvent());
		Engine::GetRenderer().GetModelRenderer().RenderBuffer();

		Scene::RenderGui();
		
	}

	void JsonScene::OnEnter()
	{

		Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/testGUI.json");
		//Ensure there is a player - Robin - Andreas
		auto player = FindObject("Player");
		if (player == nullptr)
		{
			Error("Scene has no 'Player' object. Please reconsider your life choices.");
		}

		player->GetComponent<PlayerControllerComponent>()->ActivateFirstPersonCamera();
		SB::PostMaster::Post(SaveLevelMessage());


		PostMaster::Post(ShowCursorMessage(false));
		PostMaster::Post(ConfineMouseMessage(true));
	}

	//PRIVATE FUNCTIONS:

}

#include "stdafx.h"
#include "YlfTestScene.h"
#include <Engine/Camera/Controllers/FreeSpaceCameraController.h>
#include <Engine\GUI\GUILoader.h>
#include <Engine/Feedback/VisualEffect/VisualEffectComponent.h>
#include <Engine/Texture/WorldRenderTexture.h>


YlfTestScene::YlfTestScene(SB::PostMasterState & aPostMasterState) : Scene(aPostMasterState, "Ylf Test Scene")
{
	SB::PostMasterStateBinding bind = SB::PostMaster::Push(*this);

	myCamera->GetRenderTexture()->GetModelRenderer().SetDirectionalLight(0, SB::Vector3f::UnitZ, SB::Vector4f(1.f, 1.f, 1.f, 1.f));
	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(1000.f, 1.5f));

	SB::ObjectPtr visualEffectTest = Scene::CreateGameObject("visualEffectTest"); //"Assets/Models/Objects/SandcastleEasterEgg/easterEgg.fbx"
	visualEffectTest->CreateComponent<SB::VisualEffectComponent>();

	Scene::CreateAndAddModel("sandcastle egg","Assets/Models/Objects/SandcastleEasterEgg/easterEgg.fbx", SB::Vector3f(0.f, 0.f, 500.f));
}

YlfTestScene::~YlfTestScene()
{
}

void YlfTestScene::Render()
{
	SB::Scene::Render();
}

void YlfTestScene::OnEnter()
{
	SB::Engine::GetGUILoader().DisableGUI();
	SB::PostMaster::Post<SB::ShowCursorMessage>(SB::ShowCursorMessage(true));
	SB::PostMaster::Post<SB::ChangeCursorMessage>(SB::ChangeCursorMessage(SB::eCursorState::eNormal));
}

#include "stdafx.h"
#include "StreakTestScene.h"

#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Rendering\ModelRenderer.h>
#include <imgui.h>
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\GameObject\GameObject.h>
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "Engine\Model\CubeModel.h"
#include "Engine\SoundManager\SoundManger.h"
#include "Engine\Streaks\StreakEmitterInstance.h"
#include "..\Utilities\Utilities\Math\MathMacros.h"

StreakTestScene::StreakTestScene() : Scene("PbrTestScene", "grass.dds")
{
	CreateAndAddModel("models/stefan_sphere/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 0.f));

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
	SetCameraOrientation(SB::Vector3f(0.f, 0.f, -20.f), SB::Vector3f(0.f, 0.f, 1.f));

	SB::Engine::GetRenderer().GetModelRenderer().SetAmbient(.05f);
	SB::Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, SB::Vector3f(1.f, -1.f, 1.f), SB::Vector4f(1.0f, 1.0f, 1.0f, 1.f));

	myStreakEmitter = std::make_unique<SB::StreakEmitterInstance>(SB::Vector3f(5.0f, 0.0f, 0.f));
}


StreakTestScene::~StreakTestScene()
{
}

void StreakTestScene::Update(const SB::Time & aDeltaTime)
{
	if (ImGui::Begin("PBR Test Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("Move camera with WASD, QE, Ctrl, Space and Arrow Keys.");
	}
	ImGui::End();

	//myHead->SetMatrix(Matrix44f::CreateRotateAroundY(myTime.InSeconds()) * Matrix44f::CreateTranslation(0.f, 0.f, -5.f));

	SB::Scene::Update(aDeltaTime);

	const float Angle = DEGRESS_TO_RADIANSF(45.f);
	SB::Matrix44f rotationMatrix = SB::Matrix44f::CreateRotateAroundZ(Angle * aDeltaTime.InSeconds());
	SB::Vector4f newPosition = myStreakEmitter->GetPosition();
	newPosition.w = 1.f;
	myStreakEmitter->SetPosition(newPosition * rotationMatrix);

	myStreakEmitter->Update(aDeltaTime);
}

void StreakTestScene::Render()
{
	SB::Scene::Render();

	myStreakEmitter->Render();
}

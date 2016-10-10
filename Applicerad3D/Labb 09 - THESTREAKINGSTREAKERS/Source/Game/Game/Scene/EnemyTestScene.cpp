#include "stdafx.h"
#include "EnemyTestScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>
#include <Engine/Scripting/ScriptFile.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>

#include "Game\Component\Shooting\ShootingComponent.h"
#include "Game\Component\Controller\AIControllerComponent.h"

EnemyTestScene::EnemyTestScene() : Scene("sickest scene. what", "grass.dds")
{
	CreateEnemy();

	myScript = SB::Engine::GetResourceManager().Get<SB::ScriptFile>("Assets/Scripts/Components/TestComponent.lua")->Execute();

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(10.f, 3.f));

	SetCameraOrientation(SB::Vector3f(-40.f, 0.f, -65.f));

}

EnemyTestScene::~EnemyTestScene()
{
}

void EnemyTestScene::Update(const SB::Time & aDeltaTime)
{
	SB::Scene::Update(aDeltaTime);
}

void EnemyTestScene::Render()
{
	SB::Scene::Render();
}

void EnemyTestScene::CreateEnemy()
{
	myPlayer = CreateAndAddModel("Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx", SB::Vector3f(-100.f, 0.f, 5.f), SB::Vector3f::One / 100.f);

	myEnemy = CreateAndAddModel("Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx", SB::Vector3f(0.f, 0.f, 5.f), SB::Vector3f::One / 100.f);
	myEnemy->AddComponent(GetComponentFactory<ShootingComponent>()->CreateComponent());
	myEnemy->AddComponent(GetComponentFactory<AIControllerComponent>()->CreateComponent());

	myEnemy->GetComponent<AIControllerComponent>()->SetPlayer(myPlayer);
	
}

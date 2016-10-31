#include "stdafx.h"
#include "JsonScene.h"
#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\DataParser\DataParser.h>
#include <Engine\Camera\Controllers\FreeSpaceCameraController.h>
#include <Engine\Component\BouncingComponent.h>
#include "..\SoundManager\SoundManger.h"
#include "..\..\..\Game\Game\Component\Shooting\ShotComponent.h"
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "Utilities\Intersection\IntersectionTests.h"
#include <imgui.h>
#include "..\Component\Collider\ColliderComponent.h"
#include "..\Game\MovementCollisionTestComponent.h"
#include "..\Component\Collider\RenderColliderComponent.h"
#include "..\Game\Game\Scene\TestCollision\TestHandleCollisionComponent.h"
#include "..\Game\Game\Component\Health\HealthComponent.h"
#include "Engine\ParticleSystem\ParticleComponent.h"
#include "Engine\Streak\StreakComponent.h"
#include "Engine/Component/CircleMovementComponent.h"
#include "Engine\ParticleSystem\ParticleComponent.h"
#include "Engine\Streak\StreakComponent.h"
#include "Engine/Component/CircleMovementComponent.h"
#include "../../../Game/DrawCrosshairEvent.h"
#include "..\Game\Game\Component\Shooting\WeaponComponent.h"
#include "..\Game\Game\Component\Controller\AI\AIInterceptorComponent.h"
#include "..\Physics\PhysicsComponent.h"

namespace ENGINE_NAMESPACE
{

	JsonScene::JsonScene(const char* aFilePath) : Scene(aFilePath, "grass.dds")
	{
		Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");

		Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f::UnitZ, Vector4f(1.f, 1.f, 1.f, 1.f));


		ObjectPtr temp = CreateAndAddModel("Test Spheres", "models/stefan_sphere/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 15.f));
		temp->Initialize();
		
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
		PostMaster::Post(DrawCrosshairEvent());
	}
	void JsonScene::CreateAIEnemy()
	{
		ObjectPtr testEnemy = CreateAndAddModel("InterceptorAI", "Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx", Vector3f(0.0f, 100.0f, 50.0f));

		ComponentPtr<ColliderComponent> collider = testEnemy->CreateComponent<ColliderComponent>();
		collider->SetOffsetAndRadius(Vector3f(0.0f, 0.0f, 5.0f), testEnemy->GetComponent<ModelComponent>()->GetBoundingBox().GetMaximumRadius() / 2.f);
		testEnemy->CreateComponent<PhysicsComponent>();
		/*WeaponData*/
		WeaponData wData = WeaponData("Interceptor Gun", "", "", "", "", Vector3f(0.1f, 0.1f, 5.f), Vector3f::Zero, 0.0f, 3.0f, 120.f);
		ComponentPtr<WeaponComponent> weapon = testEnemy->CreateComponent<WeaponComponent>();
		ComponentPtr<AIInterceptorComponent> ai = testEnemy->CreateComponent<AIInterceptorComponent>();
		ai->SetPlayer(FindObject("Player"));

		testEnemy->Initialize();
	}

	//PRIVATE FUNCTIONS:

}

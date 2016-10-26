#include "stdafx.h"
#include "TestEnemyCollisionScene.h"

#include "imgui.h"

#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>
#include "Engine\Resources\ResourceManager.h"
#include "Engine\SplashScreen\SplashScreenEffect.h"
#include <Engine\SplashScreen\SplashScreenScene.h>
#include "Utilities\Intersection\Colliders\SphereCollider.h"
#include "Utilities\Intersection\IntersectionTests.h"
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "Engine\Component\Collider\ColliderComponent.h"
#include "TestHandleCollisionComponent.h"
#include "Engine\Component\Collider\CollisionEvent.h"
#include <Engine\Component\Collider\RenderColliderComponent.h>
#include <Engine\Component\BouncingComponent.h>
#include "MovementCollisionTestComponent.h"


const unsigned short EnemyAmount = 1;
const SB::Vector3f LevelConstraints = SB::Vector3f(10.f, 10.f, 10.f);

TestEnemyCollisionScene::TestEnemyCollisionScene()
{
	myEnemyObjects.Resize(EnemyAmount);

	for (unsigned short iEnemy = 0; iEnemy < myEnemyObjects.Size(); ++iEnemy)
	{
		CreateEnemyObject(myEnemyObjects[iEnemy]);
	}
}


TestEnemyCollisionScene::~TestEnemyCollisionScene()
{
}

void TestEnemyCollisionScene::Update(const SB::Time & aDeltaTime)
{
	SB::Scene::Update(aDeltaTime);
}

void TestEnemyCollisionScene::Render()
{
	SB::Scene::Render();
}

void TestEnemyCollisionScene::CreateEnemyObject(SB::ObjectPtr & aGameObject)
{
	aGameObject = CreateGameObject("Enemy");

	SB::ComponentPtr<SB::ModelComponent>prettyModel = aGameObject->CreateComponent<SB::ModelComponent>();
	std::shared_ptr<SB::AssimpModel> model = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("Assets/Models/Ships/Enemies/InterceptorX101/interceptorX101.fbx");
	prettyModel->SetModel(model);

	const float tempsize = model->GetBoundingBox().GetMaximumRadius();

	aGameObject->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));

	SB::BoundingBoxf boundingBox = model->GetBoundingBox();
	boundingBox.min = SB::Vector4f(boundingBox.min, 1.f) * aGameObject->GetTransformation();
	boundingBox.max = SB::Vector4f(boundingBox.max, 1.f) * aGameObject->GetTransformation();

	SB::ComponentPtr<SB::ColliderComponent> testCollider = aGameObject->CreateComponent<SB::ColliderComponent>();
	SB::ComponentPtr<MovementCollisionTestComponent> testMovement = aGameObject->CreateComponent<MovementCollisionTestComponent>();
	aGameObject->CreateComponent<SB::RenderColliderComponent>();
	aGameObject->CreateComponent<TestHandleCollisionComponent>();
	aGameObject->CreateComponent<SB::BouncingComponent>();

	SB::Vector3f tempPosition;

	tempPosition.x = myRandomizer.GetRandomValue(-LevelConstraints.x + 1.f, LevelConstraints.x - 1.f);
	tempPosition.y = myRandomizer.GetRandomValue(-LevelConstraints.y + 1.f, LevelConstraints.y - 1.f);
	tempPosition.z = myRandomizer.GetRandomValue(-LevelConstraints.z + 1.f, LevelConstraints.z - 1.f);

	aGameObject->SetPosition(tempPosition);

	SB::Vector3f tempVelocity;

	tempVelocity.x = myRandomizer.GetRandomValue(-3.f, 3.f);
	tempVelocity.y = myRandomizer.GetRandomValue(-3.f, 3.f);
	tempVelocity.z = myRandomizer.GetRandomValue(-3.f, 3.f);

	testMovement->SetVelocity(tempVelocity);

	testCollider->SetOffsetAndRadius(aGameObject->GetPosition(), boundingBox.GetSize().x / 2.f);

	aGameObject->Initialize();
}


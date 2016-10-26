#include "stdafx.h"
#include "CollisionTestScene.h"
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
#include "..\Engine\Engine\Component\Collider\CollisionEvent.h"
#include "..\Engine\Engine\Component\Collider\RenderColliderComponent.h"
#include "MovementCollisionTestComponent.h"


const SB::Vector3f LevelConstraints(10.f, 10.f, 10.f);
const unsigned short AmountOfBalls = 1000;

CollisionTestScene::CollisionTestScene() : SB::Scene("PbrTestScene", "grass.dds")
{
	
	//myTestObject2 = CreateGameObject();

	CreateFactories();

	myCollisionObjects.Resize(AmountOfBalls);

	for (unsigned short iObject = 0; iObject < myCollisionObjects.Size(); ++iObject)
	{
		CreateGameObjectWithCollider(myCollisionObjects[iObject]);
	}

	SetCameraOrientation(SB::Vector3f(0.f, 0.f, -3.f));
	MovementCollisionTestComponent::ourConstraints = LevelConstraints;
}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(const SB::Time & aDeltaTime)
{
	//ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	//ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	//ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);


	//if (ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	//{
	//	if (ImGui::CollapsingHeader("Object 1") == true)
	//	{
	//		SB::Vector3f tempVector1 = myTestObject1->GetPosition();
	//		float tempScale1 = myTestObject1->GetScale().x * 100.f;

	//		ImGui::SliderFloat("X1", &tempVector1.x, -3.f, 3.f);
	//		ImGui::SliderFloat("Y1", &tempVector1.y, -3.f, 3.f);
	//		ImGui::SliderFloat("Z1", &tempVector1.z, -3.f, 3.f);
	//		
	//		ImGui::SliderFloat("Scale1", &tempScale1, -0.1f, 3.f);


	//		
	//		myTestObject1->GetComponent<SB::ColliderComponent>()->SetRadius(tempScale1 / 2.f);

	//		tempScale1 /= 100.f;
	//		myTestObject1->SetScale(SB::Vector3f(tempScale1, tempScale1, tempScale1));
	//		myTestObject1->SetPosition(tempVector1);
	//		myTestObject1->GetComponent<SB::ColliderComponent>()->UpdatePosition(tempVector1);
	//		
	//		

	//	}

	//	
	//	if (ImGui::CollapsingHeader("Object 2") == true)
	//	{

	//		SB::Vector3f tempVector2 = myTestObject2->GetPosition();
	//		float tempScale2 = myTestObject2->GetScale().x * 100.f;

	//		ImGui::SliderFloat("X2", &tempVector2.x, -3.f, 3.f);
	//		ImGui::SliderFloat("Y2", &tempVector2.y, -3.f, 3.f);
	//		ImGui::SliderFloat("Z2", &tempVector2.z, -3.f, 3.f);

	//		ImGui::SliderFloat("Scale2", &tempScale2, -0.1f, 3.f);

	//		myTestObject2->GetComponent<SB::ColliderComponent>()->SetRadius(tempScale2 / 2.f);

	//		tempScale2 /= 100.f;
	//		myTestObject2->SetScale(SB::Vector3f(tempScale2, tempScale2, tempScale2));
	//		myTestObject2->SetPosition(tempVector2);
	//		myTestObject2->GetComponent<SB::ColliderComponent>()->UpdatePosition(tempVector2);

	//		
	//	}

	//	if (SB::Intersection::SphereVsSphere(myTestObject1->GetComponent<SB::ColliderComponent>()->GetCollider(), myTestObject2->GetComponent<SB::ColliderComponent>()->GetCollider()) == true)
	//	{
	//		//myTestObject1->TriggerEvent(SB::CollisionEvent());
	//		//myTestObject2->TriggerEvent(SB::CollisionEvent());
	//	}
	//
	//	bool tempCollisionObj1 = myTestObject1->GetComponent<TestHandleCollisionComponent>()->HasCollided();
	//	bool tempCollisionObj2 = myTestObject2->GetComponent<TestHandleCollisionComponent>()->HasCollided();

	//	if (tempCollisionObj1 == true && tempCollisionObj2 == true)
	//	{
	//		ImGui::Text("Collision!");
	//	}
	//	else
	//	{
	//		ImGui::Text("void!!!");
	//	}


		
	/*}
	ImGui::End();*/

	Scene::Update(aDeltaTime);
}

void CollisionTestScene::Render()
{

	SB::Engine::GetDebugger().RenderCube(LevelConstraints / 2.f, LevelConstraints, SB::Vector4f(0.f, 0.f, 1.f, 1.f));

	Scene::Render();
}

void CollisionTestScene::CreateGameObjectWithCollider(SB::ObjectPtr & aGameObject)
{
	aGameObject = CreateGameObject("Collider test");

	SB::ComponentPtr<SB::ModelComponent>prettyModel = aGameObject->CreateComponent<SB::ModelComponent>();
	std::shared_ptr<SB::AssimpModel> model = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel->SetModel(model);
	
	const float tempsize = model->GetBoundingBox().GetMaximumRadius();
	
	aGameObject->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));

	SB::BoundingBoxf boundingBox = model->GetBoundingBox();
	boundingBox.min = SB::Vector4f(boundingBox.min, 1.f) * myTestObject1->GetTransformation();
	boundingBox.max = SB::Vector4f(boundingBox.max, 1.f) * myTestObject1->GetTransformation();

	SB::ComponentPtr<SB::ColliderComponent> testCollider = aGameObject->CreateComponent<SB::ColliderComponent>();
	SB::ComponentPtr<MovementCollisionTestComponent> testMovement = aGameObject->CreateComponent<MovementCollisionTestComponent>();
	aGameObject->CreateComponent<SB::RenderColliderComponent>();
	aGameObject->CreateComponent<TestHandleCollisionComponent>();

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

	testCollider->SetOffsetAndRadius(myTestObject1->GetPosition(), boundingBox.GetSize().x / 2.f);

	aGameObject->Initialize();
}

void CollisionTestScene::CreateFactories()
{
	

	unsigned short Presize = AmountOfBalls + 4;
	SetDefaultFactoryComponentAmount(Presize);

	PreCreateComponentFactory<SB::ModelComponent>();
	PreCreateComponentFactory<SB::LightComponent>();
	PreCreateComponentFactory<SB::ColliderComponent>();
	PreCreateComponentFactory<TestHandleCollisionComponent>();
	PreCreateComponentFactory<SB::RenderColliderComponent>();
	PreCreateComponentFactory<MovementCollisionTestComponent>();


	CreateGameObjectWithCollider(myTestObject1);
	

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
}

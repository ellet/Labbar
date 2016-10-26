#include "stdafx.h"
#include "TestObjectEventSystemScene.h"

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
#include "..\Engine\Engine\Component\TestEventSystem\TestEventSystemComponent.h"
#include "Engine\Component\TestEventSystem\TestEvent.h"

TestObjectEventSystemScene::TestObjectEventSystemScene()
{
	myTestObject1 = CreateGameObject("Test");
	myTestObject2 = CreateGameObject("Test");
	myTestObject3 = CreateGameObject("Test");
	myTestObject4 = CreateGameObject("Test");
	myTestObject5 = CreateGameObject("Test");

	CreateFactories();

	SetCameraOrientation(SB::Vector3f(0.f, 0.f, -3.f));


	mySpace = 0;
}


TestObjectEventSystemScene::~TestObjectEventSystemScene()
{
}

void TestObjectEventSystemScene::Update(const SB::Time & aDeltaTime)
{
	if (mySpace == true)
	{
		mySpace = false;
		myTestObject1->TriggerEvent(SB::TestEvent(SB::Vector3f(1.f, 0.f, 0.f)));
		myTestObject2->TriggerEvent(SB::TestEvent(SB::Vector3f(1.f, 0.f, 0.f)));
		myTestObject3->TriggerEvent(SB::TestEvent(SB::Vector3f(1.f, 0.f, 0.f)));
		myTestObject4->TriggerEvent(SB::TestEvent(SB::Vector3f(1.f, 0.f, 0.f)));
		myTestObject5->TriggerEvent(SB::TestEvent(SB::Vector3f(1.f, 0.f, 0.f)));
	}

	SB::Scene::Update(aDeltaTime);
}

void TestObjectEventSystemScene::Render()
{
	if (ImGui::Begin("PBR Test Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
	{
		std::string tempText = "Pos :";

		tempText += std::to_string(myTestObject1->GetPosition().x);
		tempText += ", ";
		tempText += std::to_string(myTestObject1->GetPosition().y);
		tempText += ", ";
		tempText += std::to_string(myTestObject1->GetPosition().z);

		ImGui::Text(tempText.c_str());
	}
	ImGui::End();

	SB::Scene::Render();
}



void TestObjectEventSystemScene::CreateFactories()
{
	PreCreateComponentFactory<SB::ModelComponent>();
	PreCreateComponentFactory<SB::LightComponent>();
	PreCreateComponentFactory<SB::TestEventSystemComponent>();


	/*SB::ComponentPtr<SB::ModelComponent> prettyModel1(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model1 = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel1->SetModel(model1);

	SB::ComponentPtr<SB::ModelComponent> prettyModel2(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model2 = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel2->SetModel(model2);

	SB::ComponentPtr<SB::ModelComponent> prettyModel3(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model3 = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel3->SetModel(model3);

	SB::ComponentPtr<SB::ModelComponent> prettyModel4(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model4 = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel4->SetModel(model4);
	
	SB::ComponentPtr<SB::ModelComponent> prettyModel5(GetComponentFactory<SB::ModelComponent>()->CreateComponent());
	std::shared_ptr<SB::AssimpModel> model5 = SB::Engine::GetResourceManager().Get<SB::AssimpModel>("models/unitsphere/sphere.fbx");
	prettyModel5->SetModel(model5);


	const float tempsize = model5->GetBoundingBox().GetMaximumRadius();

	myTestObject1->AddComponent<SB::ModelComponent>(prettyModel1);
	myTestObject2->AddComponent<SB::ModelComponent>(prettyModel2);
	myTestObject3->AddComponent<SB::ModelComponent>(prettyModel3);
	myTestObject4->AddComponent<SB::ModelComponent>(prettyModel4);
	myTestObject5->AddComponent<SB::ModelComponent>(prettyModel5);
	

	
	SB::ComponentPtr<SB::TestEventSystemComponent> testEventComp1(GetComponentFactory<SB::TestEventSystemComponent>()->CreateComponent());
	myTestObject1->AddComponent<SB::TestEventSystemComponent>(testEventComp1);
	myTestObject1->Initialize();
	

	SB::ComponentPtr<SB::TestEventSystemComponent> testEventComp2(GetComponentFactory<SB::TestEventSystemComponent>()->CreateComponent());
	myTestObject2->AddComponent<SB::TestEventSystemComponent>(testEventComp2);
	myTestObject2->Initialize();

	SB::ComponentPtr<SB::TestEventSystemComponent> testEventComp3(GetComponentFactory<SB::TestEventSystemComponent>()->CreateComponent());
	myTestObject3->AddComponent<SB::TestEventSystemComponent>(testEventComp3);
	myTestObject3->Initialize();

	SB::ComponentPtr<SB::TestEventSystemComponent> testEventComp4(GetComponentFactory<SB::TestEventSystemComponent>()->CreateComponent());
	myTestObject4->AddComponent<SB::TestEventSystemComponent>(testEventComp4);
	myTestObject4->Initialize();

	SB::ComponentPtr<SB::TestEventSystemComponent> testEventComp5(GetComponentFactory<SB::TestEventSystemComponent>()->CreateComponent());
	myTestObject5->AddComponent<SB::TestEventSystemComponent>(testEventComp5);
	myTestObject5->Initialize();


	myTestObject1->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));
	myTestObject2->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));
	myTestObject3->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));
	myTestObject4->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));
	myTestObject5->SetScale(SB::Vector3f(0.01f, 0.01f, 0.01f));
	
	myTestObject1->SetPosition(SB::Vector3f(0.f, 0.f, 0.f));
	myTestObject2->SetPosition(SB::Vector3f(0.f, 1.f, 0.f));
	myTestObject3->SetPosition(SB::Vector3f(0.f, 2.f, 0.f));
	myTestObject4->SetPosition(SB::Vector3f(0.f, 3.f, 0.f));
	myTestObject5->SetPosition(SB::Vector3f(0.f, 4.f, 0.f));
	 

	SB::BoundingBoxf boundingBox = model1->GetBoundingBox();
	boundingBox.min = SB::Vector4f(boundingBox.min, 1.f) * myTestObject1->GetTransformation();
	boundingBox.max = SB::Vector4f(boundingBox.max, 1.f) * myTestObject1->GetTransformation();
	*/

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
	//SetCameraOrientation(model1->GetBoundingBox().GetCenter() + SB::Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));


}

SB::ReceiveResult TestObjectEventSystemScene::Receive(const SB::AnyKeyDownMessage & aMessage)
{
	switch (aMessage.key)
	{
	case SB::KeyboardKey::eB:
		mySpace = true;
		break;
	
	}
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult TestObjectEventSystemScene::Receive(const SB::AnyKeyUpMessage & aMessage)
{
	switch (aMessage.key)
	{
	case SB::KeyboardKey::eB:
		mySpace = false;
		break;

	}
	return SB::ReceiveResult::eContinue;
}

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
#include "..\Engine\Engine\Debugging\DebugGUI\BaseDebugGUI.h"


const SB::Vector4f NoCollisionColor(0.f, 1.f, 0.f, 1.f);
const SB::Vector4f CollisionColor(1.f, 0.f, 0.f, 1.f);


const SB::Vector3f LevelConstraints(10.f, 10.f, 10.f);
const unsigned short AmountOfBalls = 1000;

CollisionTestScene::CollisionTestScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "Collision test")
{
	
	
	//CreateAndAddModel("ModelObject", "Assets/Models/PBL_Spheres/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 25.f))->Initialize();

	myCapsule2 = SB::CapsuleCollider(SB::Vector3f(-4.f, 0.f, 25.f), SB::Vector3f::UnitY * 4.f, 2.f);
	myCapsule = SB::CapsuleCollider(SB::Vector3f(0.f, 0.f, 25.f), SB::Vector3f::UnitY * 4.f, 2.f);
	mySphere = SB::SphereCollider(SB::Vector3f(4.f, 0.f, 25.f), 2.f);

	myRay = SB::RayCollider(SB::Vector3f(4.f, 0.f, 25.f), SB::Vector3f::UnitZ);

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(15.f, 2.5f));
}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Update(const SB::Time & aDeltaTime)
{
	/*ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);*/

	myRenderColor = NoCollisionColor;
	const SB::Vector2f Range(-10.f, 10.f);
	const SB::Vector2f PositivRange(0.f, Range.y);

	if (ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_NoCollapse))
	{
		

		//if (ImGui::CollapsingHeader("Object 1") == true)
		//{
			SB::Vector3f capsulePosition1 = myCapsule.GetPosition();
			

			SB::DebugGUI::SetElementsWidth(100.f);
			SB::DebugGUI::PrintText("Position1");
			//const SB::Vector2f Range(-5.f, 5.f);
			capsulePosition1.z -= 25.f;
			SB::DebugGUI::VectorSlider(capsulePosition1, Range);
			capsulePosition1.z += 25.f;
			
			myCapsule.SetPosition(capsulePosition1);

			
			SB::Vector3f capsuleLengthAndDirection1 = myCapsule.GetLengthAndDirection();
			//const SB::Vector2f Range(-5.f, 5.f);
			SB::DebugGUI::PrintText("Position2");
			SB::DebugGUI::VectorSlider(capsuleLengthAndDirection1, Range);

			myCapsule.SetLengthAndDirection(capsuleLengthAndDirection1);



			//-------------------

			SB::Vector3f capsulePosition2 = myCapsule2.GetPosition();


			SB::DebugGUI::SetElementsWidth(100.f);

			//const SB::Vector2f Range(-5.f, 5.f);
			capsulePosition2.z -= 25.f;
			SB::DebugGUI::PrintText("Position1");
			SB::DebugGUI::VectorSlider(capsulePosition2, Range);
			capsulePosition2.z += 25.f;

			myCapsule2.SetPosition(capsulePosition2);


			SB::Vector3f capsuleLengthAndDirection2 = myCapsule2.GetLengthAndDirection();
			//const SB::Vector2f Range(-5.f, 5.f);
			SB::DebugGUI::PrintText("Position2");
			SB::DebugGUI::VectorSlider(capsuleLengthAndDirection2, Range);

			myCapsule2.SetLengthAndDirection(capsuleLengthAndDirection2);


			//-----------------------------------

			SB::Vector3f RayPosition = myRay.GetPosition();


			SB::DebugGUI::SetElementsWidth(100.f);

			//const SB::Vector2f Range(-5.f, 5.f);
			RayPosition.z -= 25.f;
			SB::DebugGUI::PrintText("Ray Position");
			SB::DebugGUI::VectorSlider(RayPosition, Range);
			RayPosition.z += 25.f;

			myRay.SetPosition(RayPosition);

			SB::Vector3f RayDirection = myRay.GetDirection();

			//const SB::Vector2f Range(-5.f, 5.f);
			//RayPosition.z -= 25.f;
			SB::DebugGUI::PrintText("Ray Direction");
			SB::DebugGUI::VectorSlider(RayDirection, SB::Vector2f(-1.f ,1.f));
			//RayPosition.z += 25.f;

			myRay.SetDirection(RayDirection);

		//}
		
		//if (ImGui::CollapsingHeader("Object 2") == true)
		//{
			SB::Vector3f tempVector3 = mySphere.GetPosition();


			SB::DebugGUI::SetElementsWidth(100.f);

			
			tempVector3.z -= 25.f;
			SB::DebugGUI::VectorSlider(tempVector3, Range);
			tempVector3.z += 25.f;

			mySphere.UpdatePosition(tempVector3);



			float tempFloat = mySphere.GetRadius();
			//const SB::Vector2f Range(-5.f, 5.f);
			//SB::DebugGUI::VectorSlider(tempVector2, Range);
			SB::DebugGUI::FloatSlider(tempFloat, PositivRange);

			mySphere.SetRadius(tempFloat);
		//}

		if (SB::Intersection::CapsuleVsCapsule(myCapsule2, myCapsule) == true)
		{
			myRenderColor = CollisionColor;
		}
		
		//if (ImGui::CollapsingHeader("Object 2") == true)
		//{

		//	SB::Vector3f tempVector2 = myTestObject2->GetPosition();
		//	float tempScale2 = myTestObject2->GetScale().x * 100.f;

		//	ImGui::SliderFloat("X2", &tempVector2.x, -3.f, 3.f);
		//	ImGui::SliderFloat("Y2", &tempVector2.y, -3.f, 3.f);
		//	ImGui::SliderFloat("Z2", &tempVector2.z, -3.f, 3.f);

		//	ImGui::SliderFloat("Scale2", &tempScale2, -0.1f, 3.f);

		//	myTestObject2->GetComponent<SB::ColliderComponent>()->SetRadius(tempScale2 / 2.f);

		//	tempScale2 /= 100.f;
		//	myTestObject2->SetScale(SB::Vector3f(tempScale2, tempScale2, tempScale2));
		//	myTestObject2->SetPosition(tempVector2);
		//	myTestObject2->GetComponent<SB::ColliderComponent>()->UpdatePosition(tempVector2);

		//	
		//}

		//if (SB::Intersection::SphereVsSphere(myTestObject1->GetComponent<SB::ColliderComponent>()->GetCollider(), myTestObject2->GetComponent<SB::ColliderComponent>()->GetCollider()) == true)
		//{
		//	//myTestObject1->TriggerEvent(SB::CollisionEvent());
		//	//myTestObject2->TriggerEvent(SB::CollisionEvent());
		//}
	
		//bool tempCollisionObj1 = myTestObject1->GetComponent<TestHandleCollisionComponent>()->HasCollided();
		//bool tempCollisionObj2 = myTestObject2->GetComponent<TestHandleCollisionComponent>()->HasCollided();

		//if (tempCollisionObj1 == true && tempCollisionObj2 == true)
		//{
		//	ImGui::Text("Collision!");
		//}
		//else
		//{
		//	ImGui::Text("void!!!");
		//}


		ImGui::End();
	}
	

	Scene::Update(aDeltaTime);
}

void CollisionTestScene::Render()
{


	//SB::Engine::GetDebugDrawer().RenderCube(LevelConstraints / 2.f, LevelConstraints, SB::Vector4f(0.f, 0.f, 1.f, 1.f));

	Scene::Render();


	SB::Engine::GetDebugDrawer().RenderShape(myCapsule.GetCapsuleAsCapsuleShape(), myRenderColor);
	SB::Engine::GetDebugDrawer().RenderShape(myCapsule2.GetCapsuleAsCapsuleShape(), myRenderColor);
	SB::Engine::GetDebugDrawer().RenderShape(mySphere.GetBasicSphere(), myRenderColor);

	SB::Engine::GetDebugDrawer().RenderShape(myRay.GetRayAsLineSegment(50.f), myRenderColor);
	
}

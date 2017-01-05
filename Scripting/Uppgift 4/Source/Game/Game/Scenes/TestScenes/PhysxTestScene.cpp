#include "stdafx.h"
#include "PhysxTestScene.h"
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"


#include <iostream>
#include "Physics\System\PhysicsManager\PhysicsManager.h"

static const SB::BoxShape TemplateBox = SB::BoxShape(SB::Vector3f::Zero, SB::Vector3f(2.f, 4.f, 2.f));
static const SB::SphereShape TemplateSphere = SB::SphereShape(SB::Vector3f::Zero, 1.f);

PhysxTestScene::PhysxTestScene(SB::PostMasterState & aPostMasterState) : Scene(aPostMasterState, "PhysxTestScene", "Assets/Skyboxes/skybox4_16f.dds")
{
	GetPhysicsManager().AddActor(myPlane);

	SB::Quaternion planeRotation;
	planeRotation.RotateAroundLocalX(DEGREES_TO_RADIANSF(90.f));

	myObject = CreateAndAddModel("PhysicsObjectModel", "Assets/Models/PBL_Spheres/testSpheres.fbx", SB::Vector3f(0.f, 10.f, 25.f));
	myPlaneObject = CreateAndAddModel("PhysicsObjectModel", "Assets/Models/PBL_Spheres/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 25.f), SB::Vector3f::One, planeRotation);

	myInputListener = std::make_unique<SB::InputListener>();

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(15.f, 2.5f));

	SP::CreationManager::ConnectToVisualDebugger();
}

void PhysxTestScene::shootSphere()
{
	myShots.Add(std::make_shared<SP::DynamicActor>(GetCamera().GetPosition()));
	myShots.GetLast()->AddShape(TemplateSphere);

	SB::Vector3f velocityFromCamera = SB::Vector3f(0.f, 0.f, 200.f) * GetCamera().GetOrientation();
	
	myShots.GetLast()->SetVelocity(velocityFromCamera);
	
	
	GetPhysicsManager().AddActor(*myShots.GetLast());
}


void PhysxTestScene::AddBox(const SB::Vector3f & aPosition)
{
	myBoxes.Add(std::make_shared<SP::DynamicActor>(aPosition));
	myBoxes.GetLast()->AddShape(TemplateBox);

	GetPhysicsManager().AddActor(*myBoxes.GetLast());
}

PhysxTestScene::~PhysxTestScene()
{
}

void PhysxTestScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eControl) == true)
	{
		AddBox(SB::Vector3f(0.f, 35.f, 25.f));
	}

	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eSpace) == true)
	{
		shootSphere();
	}

	Scene::Update(aDeltaTime);
}

void PhysxTestScene::Render()
{
	Scene::Render();

	for (unsigned short iBody = 0; iBody < myBoxes.Size(); ++iBody)
	{
		SB::Engine::GetDebugDrawer().RenderCube(GetCamera(), myBoxes[iBody]->GetPosition(), TemplateBox.myExtents * 2.f, myBoxes[iBody]->GetRotation());
	}

	for (unsigned short iShot = 0; iShot < myShots.Size(); ++iShot)
	{
		SB::Engine::GetDebugDrawer().RenderSphere(GetCamera(), myShots[iShot]->GetPosition(), TemplateSphere.myRadius);
	}
}



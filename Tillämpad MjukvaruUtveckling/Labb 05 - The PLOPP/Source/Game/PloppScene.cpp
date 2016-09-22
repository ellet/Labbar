#include "stdafx.h"
#include "PloppScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include <ConstantBuffer.h>
#include <DirectionalLight.h>

PloppScene::PloppScene()
{
	std::shared_ptr<AssimpModel> modelCube = std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx");
	std::shared_ptr<ModelInstance> instanceCube = std::make_shared<ModelInstance>(modelCube);
	myCube = instanceCube;
	myObjects.push_back(instanceCube);

	std::shared_ptr<AssimpModel> modelHead = std::make_shared<AssimpModel>(myEffect, "models/JacobHead/K11_1415.fbx");
	std::shared_ptr<ModelInstance> instanceHead = std::make_shared<ModelInstance>(modelHead);
	myHead = instanceHead;
	myHead->SetPosition(Vector3f(0.f, 0.f, 10.f));
	myObjects.push_back(instanceHead);

	std::shared_ptr<AssimpModel> modelSkeleton = std::make_shared<AssimpModel>(myEffect, "models/enemy_character/enemy_robot.fbx");
	std::shared_ptr<ModelInstance> instanceSkeleton = std::make_shared<ModelInstance>(modelSkeleton);
	mySkellyton = instanceSkeleton;
	mySkellyton->SetPosition(Vector3f(0.f, -2.f, 20.f));
	myObjects.push_back(instanceSkeleton);

	GetCamera().SetPosition(Vector3f(-1.f, 0.5f, -3.f) * 1.5f);
	GetCamera().LookAt(Vector3f::Zero);

	myConstantBuffer = std::make_unique<ConstantBuffer<LightBuffer>>();

	myLight = std::make_unique<DirectionalLight>();
	myLight->SetDirection(Vector3f(0.f, 0.f, 1.f));
	myLight->SetColor(Vector3f(1.f, 1.f, 1.f));
	myCameraSpeed = 2.f;
	myDetectionDistance = 1.f;
}


PloppScene::~PloppScene()
{
}

void PloppScene::Update(const Time & aDeltaTime)
{
	if (GetCamera().GetPosition().z > 20.f || GetCamera().GetPosition().z < -7.f)
	{
		myCameraSpeed *= -1.f;
	}
	if (GetCamera().GetPosition().z + myDetectionDistance > myCube->GetPosition().z && /*cube not loaded*/)
	{

	}


	GetCamera().AddPosition(Vector3f(0.f, 0.f, myCameraSpeed * aDeltaTime.InSeconds()));
}

void PloppScene::Render()
{
	LightBuffer tempData;
	tempData.myDirection = myLight->GetDirection();
	tempData.myColor = myLight->GetColor();

	myConstantBuffer->UpdateData(tempData);

	myConstantBuffer->BindToPS(1);
	Scene::Render();
}

#include "stdafx.h"
#include "PloppScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include <ConstantBuffer.h>
#include <DirectionalLight.h>
#include "..\Engine\CubeModel.h"
#include "..\Engine\ThreadPool\Work.h"

PloppScene::PloppScene()
{
	//std::shared_ptr<AssimpModel> modelCube = std::make_shared<AssimpModel>(myEffect, "models/tga_companioncube/companion.fbx");
	std::shared_ptr<ModelInstance> instanceCube = std::make_shared<ModelInstance>();
	myCube = instanceCube;
	myCube->SetPosition(Vector3f(0.f, 0.f, 5.f));
	myObjects.push_back(instanceCube);

	//std::shared_ptr<AssimpModel> modelHead = std::make_shared<AssimpModel>(myEffect, "models/JacobHead/K11_1415.fbx");
	std::shared_ptr<ModelInstance> instanceHead = std::make_shared<ModelInstance>();
	myHead = instanceHead;
	myHead->SetPosition(Vector3f(0.f, 0.f, 15.f));
	myObjects.push_back(instanceHead);

	//std::shared_ptr<AssimpModel> modelSkeleton = std::make_shared<AssimpModel>(myEffect, "models/enemy_character/enemy_robot.fbx");
	std::shared_ptr<ModelInstance> instanceSkeleton = std::make_shared<ModelInstance>();
	mySkellyton = instanceSkeleton;
	mySkellyton->SetPosition(Vector3f(0.f, -2.f, 25.f));
	myObjects.push_back(instanceSkeleton);

	GetCamera().SetPosition(Vector3f(-1.f, 0.5f, -3.f) * 1.5f);
	GetCamera().LookAt(Vector3f::Zero);

	myConstantBuffer = std::make_unique<ConstantBuffer<LightBuffer>>();

	myLight = std::make_unique<DirectionalLight>();
	myLight->SetDirection(Vector3f(0.f, 0.f, 1.f));
	myLight->SetColor(Vector3f(1.f, 1.f, 1.f));
	myCameraSpeed = 2.f;
	myDetectionDistance = 3.f;

	myHasLoadedCube = false;
	myHasLoadedHead = false;
	myHasLoadedSkelly = false;

	MakeSomeCubes();
}

PloppScene::~PloppScene()
{
	myThreadPool.Stop();
}

void PloppScene::Update(const Time & aDeltaTime)
{
	if (GetCamera().GetPosition().z >= 25.f) //haha comment :P
	{
		GetCamera().SetPosition(Vector3f(GetCamera().GetPosition().x, GetCamera().GetPosition().y, 25.f));
		myCameraSpeed *= -1.f;
	}
	else if (GetCamera().GetPosition().z < -7.f)
	{
		GetCamera().SetPosition(Vector3f(GetCamera().GetPosition().x, GetCamera().GetPosition().y, -7.f));
		myCameraSpeed *= -1.f;
	}
	if (GetCamera().GetPosition().z + myDetectionDistance > myCube->GetPosition().z && myHasLoadedCube == false)
	{
		myHasLoadedCube = true;
		WorkFunction loadFunction;
		loadFunction = std::bind(&ModelInstance::Load, std::ref(myCube), myEffect, "models/tga_companioncube/companion.fbx");
		Work * someWork = new Work(loadFunction);
		myThreadPool.AddWork(*someWork);
	}
	if (GetCamera().GetPosition().z + myDetectionDistance > myHead->GetPosition().z && myHasLoadedHead == false)
	{
		myHasLoadedHead = true;
		WorkFunction loadFunction;
		loadFunction = std::bind(&ModelInstance::Load, std::ref(myHead), myEffect, "models/JacobHead/K11_1415.fbx");
		Work * someWork = new Work(loadFunction);
		myThreadPool.AddWork(*someWork);
	}
	if (GetCamera().GetPosition().z + myDetectionDistance > mySkellyton->GetPosition().z && myHasLoadedSkelly == false)
	{
		myHasLoadedSkelly = true;
		WorkFunction loadFunction;
		loadFunction = std::bind(&ModelInstance::Load, std::ref(mySkellyton), myEffect, "models/enemy_character/enemy_robot.fbx");
		Work * someWork = new Work(loadFunction);
		myThreadPool.AddWork(*someWork);
	}

	GetCamera().AddPosition(Vector3f(0.f, 0.f, myCameraSpeed * aDeltaTime.InSeconds()));
	//GetCamera().AddYaw(aDeltaTime.InSeconds());
	Scene::Update(aDeltaTime);
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

void PloppScene::MakeSomeCubes()
{
	auto cube = std::make_shared<CubeModel>(myEffect, std::make_shared<Texture>("models/tga_companioncube/companion_heart.dds"));
	float size = 10.f;
	float offset = 3.25f;

	for (float iCube = -5.f; iCube < 15.f; ++iCube)
	{
		auto instance = std::make_shared<ModelInstance>(cube);
		instance->SetMatrix(Matrix44f::CreateTranslation(4.f, 0.f, iCube * offset));
		myObjects.push_back(instance);
	}
}

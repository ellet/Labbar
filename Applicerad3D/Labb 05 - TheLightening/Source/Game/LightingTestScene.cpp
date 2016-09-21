#include "stdafx.h"
#include "LightingTestScene.h"
#include <AssimpModel.h>
#include <ModelInstance.h>
#include <StandardEffect.h>
#include <Camera.h>
#include <ConstantBuffer.h>
#include <DirectionalLight.h>

LightingTestScene::LightingTestScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/JacobHead/K11_1415.fbx");
	std::shared_ptr<ModelInstance> instance = std::make_shared<ModelInstance>(model);

	myHead = instance;

	myObjects.push_back(instance);

	GetCamera().SetPosition(Vector3f(-1.f, 0.5f, -1.f) * 1.5f);
	GetCamera().LookAt(Vector3f::Zero);

	myConstantBuffer = std::make_unique<ConstantBuffer<LightBuffer>>();

	myLight = std::make_unique<DirectionalLight>();
	myLight->SetDirection(Vector3f(0.f, 0.f, 1.f));
	myLight->SetColor(Vector3f(1.f, 1.f, 1.f));
}

LightingTestScene::~LightingTestScene()
{
}

void LightingTestScene::Render()
{
	LightBuffer tempData;
	tempData.myDirection = myLight->GetDirection();
	tempData.myColor = myLight->GetColor();

	myConstantBuffer->UpdateData(tempData);

	myConstantBuffer->BindToPS(1);
	Scene::Render();
}

void LightingTestScene::Update(const Time & aDeltaTime)
{
	Vector3f tempVector = myLight->GetDirection();
	Vector4f tempNewDirection(Vector4f(tempVector.x, tempVector.y, tempVector.z, 1.0f) * Matrix44f::CreateRotateAroundY(aDeltaTime.InSeconds()));

	myLight->SetDirection(Vector3f(tempNewDirection.x, tempNewDirection.y, tempNewDirection.z));
	myHead->SetMatrix(myHead->GetMatrix() * Matrix44f::CreateRotateAroundY(aDeltaTime.InSeconds() / 10.f));
}

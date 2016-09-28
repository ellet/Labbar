#include "stdafx.h"
#include "PointLightScene.h"
#include "Engine\Model\AssimpModel.h"
#include <Engine\Camera\Camera.h>
#include "Engine\Model\ModelInstance.h"
#include <Engine\Effect\StandardEffect.h>

PointLightScene::PointLightScene()
{
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Modelviewer_Exempelmodell/K11_1415.fbx");
	
	myObjects.push_back(std::make_shared<ModelInstance>(model));

	GetCamera().SetPosition(Vector3f(0.f, 0.f, -2.3f));

	Vector4f tempPosition = Vector4f(4.f ,0.f, 0.f, 1.f);

	for (int iSpot = 0; iSpot < 8; ++iSpot)
	{
		Vector4f derpPosition = tempPosition * Matrix44f::CreateRotateAroundY(0.785398163f * iSpot);
		myLightPositions.push_back(derpPosition);
		Engine::GetRenderer().GetModelRenderer().SetPointLight(iSpot, derpPosition, Vector3f(0.f, 0.f, 0.f), 0.f, 0.f);
	}
	
	//Engine::GetRenderer().GetModelRenderer().SetPointLight(0, Vector3f(-4.f, 0.f, 2.f), Vector3f(1.f, 0.f, 0.f), 1.f, 1.f);
	//Engine::GetRenderer().GetModelRenderer().SetPointLight(1, Vector3f(-2.f, 0.f, 4.f), Vector3f(1.f, 0.f, 1.f), 1.f, 1.f);
	//Engine::GetRenderer().GetModelRenderer().SetPointLight(2, Vector3f(2.f, 0.f, 4.f), Vector3f(1.f, 1.f, 1.f), 1.f, 1.f);
	Engine::GetRenderer().GetModelRenderer().SetPointLight(3, Vector3f(4.f, 0.f, 2.f), Vector3f(1.f, 1.f, 0.f), 1.f, 1.f);

	Engine::GetRenderer().GetModelRenderer().SetPointLight(4, Vector3f(-4.f, 0.f, -2.f), Vector3f(0.f, 1.f, 0.f), 1.f, 1.f);
	Engine::GetRenderer().GetModelRenderer().SetPointLight(5, Vector3f(-2.f, 0.f, -4.f), Vector3f(0.f, 0.f, 1.f), 1.f, 1.f);
	Engine::GetRenderer().GetModelRenderer().SetPointLight(6, Vector3f(2.f, 0.f, -4.f), Vector3f(0.f, 1.f, 1.f), 1.f, 1.f);
	Engine::GetRenderer().GetModelRenderer().SetPointLight(7, Vector3f(4.f, 0.f, -2.f), Vector3f(0.f, 0.f, 1.f), 1.f, 1.f);


	Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, Vector3f(0.f, 0.f, 0.f), Vector4f(0.7f, 0.7f, 0.7f, 1.f));
}


PointLightScene::~PointLightScene()
{
}

void PointLightScene::Update(const Time & aDeltaTime)
{
	for (int iSpot = 0; iSpot < 8; ++iSpot)
	{
		Vector4f tempVector = (Vector4f(Engine::GetRenderer().GetModelRenderer().GetPointLightPosition(iSpot), 1.0f) * Matrix44f::CreateRotateAroundY(0.785398163f * aDeltaTime.InSeconds()));
		Engine::GetRenderer().GetModelRenderer().SetPointLightPosition(iSpot,tempVector);
	}
	
	Scene::Update(aDeltaTime);
}

void PointLightScene::Render()
{
	Scene::Render();
}

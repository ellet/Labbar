#include "stdafx.h"
#include "PBLScene.h"

#include <Engine\Component\Factory\ComponentFactory.h>
#include <Engine/Model/ModelInstance.h>
#include <Engine\Component\ModelComponent.h>
#include <Engine\Component\LightComponent.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\Model\AssimpModel.h>
#include <Engine/Effect/StandardEffect.h>
#include <Engine\Camera/Camera.h>

PBLScene::PBLScene()
{
	CreateFactories();

	GetCamera().SetPosition(Vector3f(0.f, 0.f, -8.f));
}


PBLScene::~PBLScene()
{
}

void PBLScene::Update(const Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void PBLScene::Render()
{
	Scene::Render();
}

void PBLScene::CreateFactories()
{
	AddComponentFactory<ModelComponent>();
	AddComponentFactory<LightComponent>();

	std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();

	//GetComponentFactory<ModelComponent>()->CreateComponent();

	SharedPtrComponent<ModelComponent> prettyModel(GetComponentFactory<ModelComponent>()->CreateComponent());
	std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(myEffect, "models/Stefan/testSpheres.fbx");
	prettyModel->SetModel(std::make_shared<ModelInstance>(model));

	//GetCamera().SetPosition(model->GetBoundingBox().GetCenter() + Vector3f(0.f, 0.f, -model->GetBoundingBox().GetSize().z * 1.5f));

	enemy->AddComponent<ModelComponent>(prettyModel);
}
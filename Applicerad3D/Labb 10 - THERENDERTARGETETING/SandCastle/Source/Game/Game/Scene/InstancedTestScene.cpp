#include "stdafx.h"
#include "InstancedTestScene.h"
#include <Engine\Model\AssimpModel.h>
#include <Engine\Model\ModelInstance.h>
#include <Engine\Effect\StandardEffect.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Model\CubeModel.h>
#include <Engine\Texture\Texture.h>

class TestComponent : public SB::BaseComponent
{
public:
	TestComponent()
	{
		myTime = 1.0f;
	}
	void Update(const SB::Time& aDeltaTime) override
	{
		myTime -= aDeltaTime;
		if (myTime <= 0.f)
		{
			myObject->Remove();
		}
	}

private:
	SB::Time myTime;
};

InstancedTestScene::InstancedTestScene()
	: SB::Scene("skybox.dds")
{
	SB::ObjectPtr ptr = CreateGameObject("test");
	ptr->CreateComponent<TestComponent>();
	ptr->Initialize();
}


InstancedTestScene::~InstancedTestScene()
{
}

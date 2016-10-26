#pragma once
#include <Engine\Scene\Scene.h>
#include "Engine\PostMaster.h"
#include "Engine\Input\KeyMessages.h"


class TestObjectEventSystemScene :
	public SB::Scene, public SB::Subscriber<SB::AnyKeyDownMessage>, public SB::Subscriber<SB::AnyKeyUpMessage>
{
public:
	TestObjectEventSystemScene();
	~TestObjectEventSystemScene();

	void Update(const SB::Time & aDeltaTime);
	void Render();

	SB::ReceiveResult TestObjectEventSystemScene::Receive(const SB::AnyKeyDownMessage & aMessage) override;
	SB::ReceiveResult TestObjectEventSystemScene::Receive(const SB::AnyKeyUpMessage & aMessage) override;

private:
	SB::ObjectPtr myTestObject1;
	SB::ObjectPtr myTestObject2;
	SB::ObjectPtr myTestObject3;
	SB::ObjectPtr myTestObject4;
	SB::ObjectPtr myTestObject5;
	

	bool mySpace;

	void CreateFactories();
};


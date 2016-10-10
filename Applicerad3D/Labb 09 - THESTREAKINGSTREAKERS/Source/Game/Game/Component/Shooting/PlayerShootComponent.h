#pragma once
#include <Engine\Component\BaseComponent.h>

namespace SB
{
	class Model;
	class Scene;
}

class PlayerShootComponent : public SB::BaseComponent, public SB::Subscriber<SB::KeyDownMessage<SB::KeyboardKey::eZ>>
{
public:
	virtual void Initialize() override;
	~PlayerShootComponent();

	SB::ReceiveResult Receive(const SB::LeftMouseButtonDownMessage & aMessage);
	SB::ReceiveResult Receive(const SB::LeftMouseButtonUpMessage & aMessage);
	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eZ>& aMessage) override;

	virtual void Update(const SB::Time & aDeltaTime) override;

private:
	std::shared_ptr<SB::Model> myModel;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonDownMessage>> myKeySubscription;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonUpMessage>> myKeyUpSubscription;
	int myShotCounter;
	bool myShooting;
	SB::Time myShootTimer;
};


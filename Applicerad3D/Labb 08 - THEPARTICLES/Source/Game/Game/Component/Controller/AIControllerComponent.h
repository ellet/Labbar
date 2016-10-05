#pragma once
#include "Game\Component\Controller\ControllerComponent.h"
namespace SB
{
	class GameObject;
}

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent();
	virtual ~AIControllerComponent() override;

	virtual void Update(const SB::Time & aDeltaTime) override;
	void SetPlayer(std::shared_ptr<SB::GameObject> aPlayer);
private:
	std::shared_ptr <SB::GameObject> myPlayer;
	float myShootTimer;
};
	

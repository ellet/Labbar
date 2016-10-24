#pragma once
#include "..\Game\Game\Component\Controller\ControllerComponent.h"
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
	void SetPlayer(const SB::ObjectPtr & aPlayer);
protected:
	SB::ObjectPtr myPlayer;
	float myShootTimer;
};
	

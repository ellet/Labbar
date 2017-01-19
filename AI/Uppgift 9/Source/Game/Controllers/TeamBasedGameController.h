#pragma once

#include "Controllers/Behaviours/SeekBehaviour.h"
#include "BaseController.h"

class TeamBasedGameController : public BaseController
{
public:
	TeamBasedGameController(const Actor & aActor);
	~TeamBasedGameController();


	virtual SB::Vector2f Update(const float aDeltaTime) override;

	void SetTargetPosition(const SB::Vector2f & aTargetPosition);


private:
	SeekBehaviour mySeekBehaviour;
};


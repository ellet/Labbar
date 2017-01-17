#pragma once
#include "Controller.h"
#include "CircleShape.h"
#include "AIArriveController.h"
#include "AIFleeController.h"
#include "..\Behaviours\SeekBehaviour.h"

class Controller;

class AIEventHandler
{
public:
	static void Create();
	static void Destroy();

	static void SetNewTargetForSeek(const SetSeekTargetEvent & aNewArrivalTarget);

	static void CheckEvadeOnBlendControllers();
	static void CheckEvadeOnFormationControllers();


private:
	static AIEventHandler * ourInstance;

	static AIEventHandler & GetInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("AIEventHandlerNotCreated");
		}

		return *ourInstance;
	}

	AIEventHandler();
	~AIEventHandler();


	static bool CollisionCheck(const SB::Vector2f & aPosition, const SB::CircleShape & aCircle);
	static bool CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle);
};

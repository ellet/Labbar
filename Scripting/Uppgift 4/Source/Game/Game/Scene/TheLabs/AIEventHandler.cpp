#include "stdafx.h"
#include "AIEventHandler.h"
#include "Unit.h"
#include "PollingStation.h"
#include "BlendBehaviourController.h"
#include "FormationGroup.h"


AIEventHandler * AIEventHandler::ourInstance = nullptr;


AIEventHandler::AIEventHandler()
{
}


AIEventHandler::~AIEventHandler()
{
}

bool AIEventHandler::CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle)
{
	const float combinedRadius = aFirstCircle.myRadius + aSecondCircle.myRadius;
	const float distance = (aFirstCircle.myPosition - aSecondCircle.myPosition).Length();

	if (combinedRadius >= distance)
	{
		return true;
	}

	return false;
}

bool AIEventHandler::CollisionCheck(const SB::Vector2f & aPosition, const SB::CircleShape & aCircle)
{
	const float Distance = (aPosition - aCircle.myPosition).Length();

	if (Distance <= aCircle.myRadius)
	{
		return true;
	}

	return false;
}

void AIEventHandler::Create()
{
	if (ourInstance != nullptr)
	{
		Error("our instance already created");
	}

	ourInstance = new AIEventHandler();
}

void AIEventHandler::Destroy()
{
	if (ourInstance == nullptr)
	{
		Error("instance is already nullptr");
	}

	delete ourInstance;
}


void AIEventHandler::SetNewTargetForSeek(const SetSeekTargetEvent & aNewArrivalTarget)
{
	const SB::GrowingArray<BlendBehaviourController*> & blendControllers = PollingStation::GetBlendControllers();

	for (unsigned short iController = 0; iController < blendControllers.Size(); ++iController)
	{
		blendControllers[iController]->RecieveEvent(aNewArrivalTarget);
	}

	FormationGroup & currentFormationGroup = PollingStation::GetFormationGroup();

	currentFormationGroup.RecieveEvent(aNewArrivalTarget);
}

void AIEventHandler::CheckEvadeOnBlendControllers()
{
	const SB::GrowingArray<BlendBehaviourController*> & blendControllers = PollingStation::GetBlendControllers();

	for (unsigned short iController = 0; iController < blendControllers.Size(); ++iController)
	{
		SB::CircleShape currentShape = blendControllers[iController]->GetEvadeArea();

		for (unsigned short iOther = 0; iOther < blendControllers.Size(); ++iOther)
		{
			if (iController == iOther)
			{
				continue;
			}

			if (CollisionCheck(blendControllers[iOther]->GetPosition(), currentShape) == true)
			{
				//SB::Vector2f futurePosition = blendControllers[iOther]->GetFuturePosition(1.f);
				SB::Vector2f futurePosition = blendControllers[iOther]->GetFuturePosition(0.f);

				blendControllers[iController]->RecieveEvent(PointToEvadeEvent(futurePosition));
			}
		}
	}
}

void AIEventHandler::CheckEvadeOnFormationControllers()
{
	const SB::GrowingArray<FormationController*> & FormationControllers = PollingStation::GetFormationControllers();
	const SB::GrowingArray<Unit*> & UnitsToCheck = PollingStation::GetActors();

	for (unsigned short iController = 0; iController < FormationControllers.Size(); ++iController)
	{
		SB::CircleShape currentShape = FormationControllers[iController]->GetEvadeArea();

		for (unsigned short iOther = 0; iOther < UnitsToCheck.Size(); ++iOther)
		{
			if (FormationControllers[iController]->GetUnit() == UnitsToCheck[iOther])
			{
				continue;
			}

			if (CollisionCheck(UnitsToCheck[iOther]->GetPosition(), currentShape) == true)
			{
				SB::Vector2f futurePosition = UnitsToCheck[iOther]->GetFuturePosition(0.f);

				FormationControllers[iController]->RecieveEvent(PointToEvadeEvent(futurePosition));
			}
		}
	}
}


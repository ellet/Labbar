#pragma once
#include "CircleShape.h"


class Unit;
class AIArriveController;
class AIFleeController;
class BlendBehaviourController;
class FormationGroup;
class FormationController;

class PollingStation
{
public:
	static void Create();
	static void Destroy();

	static void RegisterUnit(Unit & aUnit);
	static void UnRegisterUnit(Unit & aUnit);

	static void RegisterFormationController(FormationController & aFormationController);
	static void UnRegisterFormationController(FormationController & aFormationController);

	static void RegisterBlenderController(BlendBehaviourController & aBlenderController);
	static void UnRegisterBlenderController(BlendBehaviourController & aBlenderController);

	static void RegisterFormationGroup(FormationGroup & aGroup);
	static void UnRegisterFormationGroup(FormationGroup & aGroup);

	static const SB::GrowingArray<Unit*> & GetActors();
	static const SB::GrowingArray<BlendBehaviourController*> & GetBlendControllers();
	static const SB::GrowingArray<FormationController*> & GetFormationControllers();
	static FormationGroup & GetFormationGroup();

private:
	static PollingStation * ourInstance;

	SB::GrowingArray<Unit*> myUnits;
	SB::GrowingArray<BlendBehaviourController *> myBlendControllers;
	SB::GrowingArray<FormationController *> myFormationControllers;

	FormationGroup * myFormationGroup;

	static PollingStation & GetInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("ourinstance was nullpr");
		}

		return *ourInstance;
	}

	PollingStation();
	~PollingStation();
};


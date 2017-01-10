#include "stdafx.h"
#include "PollingStation.h"
#include "Unit.h"

PollingStation * PollingStation::ourInstance = nullptr;

void PollingStation::Create()
{
	if (ourInstance != nullptr)
	{
		Error("pollingstation is not nulltpr");
	}

	ourInstance = new PollingStation();
}

void PollingStation::Destroy()
{
	if (ourInstance == nullptr)
	{
		Error("pollingstation is nulltpr");
	}

	delete ourInstance;
}



void PollingStation::RegisterUnit(Unit & aUnit)
{
	GetInstance().myUnits.Add(&aUnit);
}

void PollingStation::UnRegisterUnit(Unit & aUnit)
{
	GetInstance().myUnits.RemoveCyclic(&aUnit);
}

void PollingStation::RegisterFormationController(FormationController & aFormationController)
{
	GetInstance().myFormationControllers.Add(&aFormationController);
}

void PollingStation::UnRegisterFormationController(FormationController & aFormationController)
{
	GetInstance().myFormationControllers.RemoveCyclic(&aFormationController);
}

void PollingStation::RegisterBlenderController(BlendBehaviourController & aBlenderController)
{
	GetInstance().myBlendControllers.Add(&aBlenderController);
}

void PollingStation::UnRegisterBlenderController(BlendBehaviourController & aBlenderController)
{
	GetInstance().myBlendControllers.RemoveCyclic(&aBlenderController);
}

void PollingStation::RegisterFormationGroup(FormationGroup & aGroup)
{
	GetInstance().myFormationGroup = &aGroup;
}

void PollingStation::UnRegisterFormationGroup(FormationGroup & /*aGroup*/)
{
	GetInstance().myFormationGroup = nullptr;
}

const SB::GrowingArray<Unit*> & PollingStation::GetActors()
{
	return GetInstance().myUnits;
}


const SB::GrowingArray<BlendBehaviourController*> & PollingStation::GetBlendControllers()
{
	return GetInstance().myBlendControllers;
}

const SB::GrowingArray<FormationController*> & PollingStation::GetFormationControllers()
{
	return GetInstance().myFormationControllers;
}

FormationGroup & PollingStation::GetFormationGroup()
{
	return *GetInstance().myFormationGroup;
}

PollingStation::PollingStation()
{
}

PollingStation::~PollingStation()
{
}

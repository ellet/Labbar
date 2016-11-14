#include "stdafx.h"
#include "Objective.h"
#include "..\Dialog\DialogChain.h"


Objective::Objective()
{
	myIsActive = false;
}

Objective::Objective(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction)
{
	myIdentity = aData["identity"].GetString();
	myDescription = aData["description"].GetString();
	myCounter = aData["counter"].GetUnsignedShort();
	myCounterTarget = aData["target"].GetUnsignedShort();

	if (aData.HasMember("dialogChain") == true)
		myDialogChain = std::make_unique<DialogChain>(aData["dialogChain"], aOnCompleteFunction);
	else
		myDialogChain = nullptr;

	myIsActive = false;
}

Objective::~Objective()
{
}


void Objective::Update(const SB::Time & aDeltaTime)
{
	if (myIsActive == false)
	{
		return;
	}

	if (myDialogChain != nullptr)
	{
		myDialogChain->Update(aDeltaTime);
	}
}

void Objective::Render() const
{
	if (myIsActive == false)
	{
		return;
	}

	if (myDialogChain != nullptr)
	{
		myDialogChain->Render();
	}
}

const std::string & Objective::GetIdentity() const
{
	return myIdentity;
}

const std::string & Objective::GetDescription() const
{
	return myDescription;
}


unsigned short Objective::GetCounter() const
{
	return myCounter;
}

void Objective::SetCounter(unsigned short aValue)
{
	if (myIsActive == true)
		myCounter = aValue;
}

bool Objective::TargetReached() const
{
	return myCounter == myCounterTarget;
}

bool Objective::GetIsDialogDone() const
{
	if (myDialogChain == nullptr)
	{
		return true;
	}

	return myDialogChain->GetIsDone();
}

void Objective::Deactivate()
{
	myIsActive = false;
}

void Objective::Activate()
{
	myIsActive = true;
}

void Objective::IncrementCounter(unsigned short aIncrementValue)
{
	if (myIsActive == true)
		myCounter++;
}

void Objective::DecrementCounter(unsigned short aDecrementValue)
{
	if (myIsActive == true)
		myCounter--;
}

unsigned short Objective::GetTarget() const
{
	return myCounterTarget;
}

std::string Objective::ToString() const
{
	Error("Could not convert {[empty]} to a valid ObjectiveComponent value.");
}

std::string Objective::ToString(const std::string &aFormat) const
{
	if (aFormat == "counter")
	{
		return std::to_string(myCounter);
	}
	else if (aFormat == "target")
	{
		return std::to_string(myCounterTarget);
	}
	Error("Could not convert {" + aFormat + "} to a valid ObjectiveComponent value.");
}
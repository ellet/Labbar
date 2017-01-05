#include "stdafx.h"
#include "Objective.h"

namespace SB
{


	Objective::Objective()
	{
		myIsActive = false;
		myIsCompleted = false;
	}

	Objective::Objective(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction)
	{
		myIdentity = aData["identity"].GetString();
		myDescription = aData["description"].GetString();
		myCounter = aData["counter"].GetUnsignedShort();
		myCounterTarget = aData["target"].GetUnsignedShort();

		myOnCompleteFunction = aOnCompleteFunction;

		myIsActive = false;
		myIsCompleted = false;
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

		if (myIsCompleted == true)
		{
			myOnCompleteFunction();
			myIsActive = false;
		}
	}

	void Objective::Render(const Camera & aCamera) const
	{
		if (myIsActive == false)
		{
			return;
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
		if (myIsActive == true && myIsCompleted == false)
		{
			myCounter = aValue;

			if (TargetReached() == true)
			{
				OnTargetReached();
			}

#ifdef _DEBUG
			std::string debugText = "Objective '" + myIdentity + "' counter set to " + std::to_string(aValue);
			std::cout << debugText << std::endl;
#endif
		}
	}

	void Objective::OnTargetReached()
	{
		myIsCompleted = true;

#ifdef _DEBUG
		std::string debugText = "Objective '" + myIdentity + "' flagged as completed";
		std::cout << debugText << std::endl;
#endif
	}

	void Objective::Deactivate()
	{
		myIsActive = false;

#ifdef _DEBUG
		std::string debugText = "Objective '" + myIdentity + "' deactivated";
		std::cout << debugText << std::endl;
#endif
	}

	void Objective::Activate()
	{
		myIsActive = true;

#ifdef _DEBUG
		std::string debugText = "Objective '" + myIdentity + "' activated";
		std::cout << debugText << std::endl;
#endif
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
};
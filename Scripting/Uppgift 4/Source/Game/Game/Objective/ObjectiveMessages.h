#pragma once

namespace SB
{
	class Objective;

	enum class eObjectiveState
	{
		eStarted,
		eEnded
	};

	struct ObjectiveStateChangedMessage
	{
		eObjectiveState myState;
		std::shared_ptr<Objective> myObjective;
	};

};
#pragma once


namespace ENGINE_NAMESPACE
{
	enum class ePopType
	{
		eCurrent,
		eMajor,
		eToFirst,
		eAll //This will quite game unless you add a new major scene before next update
	};

	struct PopSceneMessage
	{
		PopSceneMessage(ePopType aType)
		{
			myPop = aType;
		}

		ePopType myPop;
	};
};
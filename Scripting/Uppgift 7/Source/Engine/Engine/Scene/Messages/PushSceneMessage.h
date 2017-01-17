#pragma once
#include "CreateSceneMessage.h"

namespace SB
{
	struct PushSceneMessage
	{
		PushSceneMessage(const std::shared_ptr<Scene> aSceneToPush, const eSceneType aSceneType) : mySceneToPush(aSceneToPush), mySceneType(aSceneType)
		{}


		eSceneType mySceneType;
		std::shared_ptr<Scene> mySceneToPush;
	};
}
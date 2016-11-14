#pragma once
#include "CreateSceneMessage.h"

namespace ENGINE_NAMESPACE
{
	struct PushSceneMessage
	{
		PushSceneMessage(const std::shared_ptr<Scene> aSceneToPush, const eSceneType aSceneType) : mySceneToPush(aSceneToPush), mySceneType(aSceneType)
		{}


		eSceneType mySceneType;
		std::shared_ptr<Scene> mySceneToPush;
	};
}
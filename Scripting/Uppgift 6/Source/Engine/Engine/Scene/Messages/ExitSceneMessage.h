#pragma once

struct ExitSceneMessage
{
	ExitSceneMessage(const char* aSceneName) : mySceneName(aSceneName)
	{

	}
	const char *mySceneName;
};
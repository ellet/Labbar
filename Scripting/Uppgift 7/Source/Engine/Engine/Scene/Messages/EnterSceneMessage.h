#pragma once

struct EnterSceneMessage
{
	EnterSceneMessage(const char* aSceneName) : mySceneName(aSceneName)
	{

	}
	const char *mySceneName;
};
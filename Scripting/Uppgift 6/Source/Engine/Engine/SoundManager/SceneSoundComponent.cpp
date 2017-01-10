#include "stdafx.h"
#include "SceneSoundComponent.h"


namespace SB
{
	SceneSoundComponent::SceneSoundComponent()
	{
	}


	SceneSoundComponent::~SceneSoundComponent()
	{
	}

	void SceneSoundComponent::PlayAll()
	{
		std::string playEvent;
		for (unsigned short i = 0; i < mySounds.Size(); ++i)
		{
			playEvent = "Play_" + mySounds[i];
			Engine::GetSoundManager().PostEvent(playEvent.c_str());
		}
	}

	void SceneSoundComponent::StopAll()
	{
		std::string stopEvent;
		for (unsigned short i = 0; i < mySounds.Size(); ++i)
		{
			stopEvent = "Stop_" + mySounds[i]; 
			Engine::GetSoundManager().PostEvent(stopEvent.c_str());
		}
	}

	void SceneSoundComponent::ToJson(JsonSerializer &aSerializer) const
	{
		JsonSerializer &serializer = aSerializer;
		serializer.WriteObject("properties");
		serializer.WriteArray("sounds");

		for (unsigned short i = 0; i < mySounds.Size(); i++)
		{
			serializer.WriteArrayValue(mySounds[i]);
		}

		serializer.StepOut();
		serializer.StepOut();
		serializer.WriteNode("type", "SceneSoundComponent");
	}

	void SceneSoundComponent::LoadData(DataNode aProperties)
	{
		for (unsigned short i = 0; i < static_cast<unsigned short> (aProperties["sounds"].Size()) ; ++i)
		{
			mySounds.Add(aProperties["sounds"][i].GetString());
		}
	}

	ReceiveResult SceneSoundComponent::Receive(const EnterSceneMessage & aMessage)
	{
		PlayAll();
		return ReceiveResult::eContinue;
	}

	ReceiveResult SceneSoundComponent::Receive(const ExitSceneMessage & aMessage)
	{
		StopAll();
		return ReceiveResult::eContinue;
	}

}
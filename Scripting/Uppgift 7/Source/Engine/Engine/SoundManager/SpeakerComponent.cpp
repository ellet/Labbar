#include "stdafx.h"
#include "SpeakerComponent.h"

namespace SB
{
	SpeakerComponent::SpeakerComponent()
	{
	}

	SpeakerComponent::~SpeakerComponent()
	{
		SB::Engine::GetSoundManager().UnRegisterObjectID(mySoundID);
	}

	void SpeakerComponent::Initialize()
	{
		mySoundID = Engine::GetSoundManager().RegisterObjectAtFreeID();
	}

	void SpeakerComponent::RegisterRTPC(const std::string & aRTPCIdentifier)
	{
		myRTPCValues.Add(RTPCUpdate(aRTPCIdentifier));
		myRTPCIdentifiers[aRTPCIdentifier] = myRTPCValues.Size() - 1;
	}

	void SpeakerComponent::SetRTPC(const std::string & aRTPCIdentifier, int aRTPCValue)
	{
		myRTPCValues[myRTPCIdentifiers[aRTPCIdentifier]].myRTPCValue = aRTPCValue;
	}

	void SpeakerComponent::PostSoundEvent(const std::string & aSoundEvent)
	{
		SB::Engine::GetSoundManager().PostEvent(aSoundEvent.c_str(), mySoundID);
	}

	void SpeakerComponent::Update(const Time & aDeltaTime)
	{
		UpdateRTPC();
		SB::Engine::GetSoundManager().SetPosition((myObject->GetParent() == nullptr) ? myObject->GetPosition() : myObject->GetWorldPosition(), mySoundID);
	}

	void SpeakerComponent::ToJson(JsonSerializer &aSerializer) const 
{
		JsonSerializer &serializer = aSerializer;
		serializer.WriteObject("properties");
		serializer.StepOut();
		serializer.WriteNode("type", "SpeakerComponent");
	}

	void SpeakerComponent::UpdateRTPC()
	{
		for (unsigned short i = 0; i < myRTPCValues.Size(); ++i)
		{
			if (myRTPCValues[i].myRTPC != "")
			{
				SB::Engine::GetSoundManager().SetRTPC(myRTPCValues[i].myRTPC.c_str(), myRTPCValues[i].myRTPCValue, mySoundID);
			}
		}
	}

}
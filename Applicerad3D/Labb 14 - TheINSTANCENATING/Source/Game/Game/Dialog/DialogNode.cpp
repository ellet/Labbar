#include "stdafx.h"
#include "DialogNode.h"
#include "Engine/SoundManager/SoundManager.h"


DialogNode::DialogNode()
{
	myTrailDelay = 0.f;
	myVoiceClip = "";
	mySubtitles = SB::Text(SB::Vector2f::Zero, SB::Vector2f::One, "");

	DetermineDuration();
}

DialogNode::DialogNode(SB::DataNode aData)
{
	LoadData(aData);
}

DialogNode::~DialogNode()
{
}

void DialogNode::Update(const SB::Time& aDeltaTime)
{
	if (GetIsDonePlaying() == true)
	{
		return;
	}

	myCurrentDuration -= aDeltaTime;
	if (myCurrentDuration <= 0.f)
	{
		myCurrentDuration = 0.f;
	}
}

void DialogNode::Render() const
{
	if (GetIsDonePlaying() == true)
	{
		return;
	}

	mySubtitles.Render();	
}

void DialogNode::Start()
{
	SB::Engine::GetSoundManager().PostEvent(myVoiceClip.c_str());
}

void DialogNode::Reset()
{
	myCurrentDuration = myTotalDuration;
}

void DialogNode::LoadData(SB::DataNode aData)
{
	//TODO: Alter this to a position that looks good regardless of text size, wrapping, etc
	const SB::Vector2f TextPosition = SB::Vector2f(0.f, 0.f);

	myVoiceClip = aData["voiceClip"].GetString();
	mySubtitles = SB::Text(TextPosition, SB::Vector2f::One, aData["subtitles"].GetString());
	myTrailDelay = aData["trailDelay"].GetFloat();

	DetermineDuration();
}

//Automatically determine duration based on subtitle length and sound event length (use highest of the two)
void DialogNode::DetermineDuration()
{
	const float DurationPerCharacter = 0.15f;
	const float TrailDuration = 1.f + myTrailDelay.InSeconds();
	float duration = static_cast<float>(mySubtitles.GetText().length()) * DurationPerCharacter;

	//TODO: Check if voice clip's duration is longer, and if so set duration to that instead

	if (duration > 0.f)
	{
		duration += TrailDuration;
	}

	myTotalDuration = duration;
	myCurrentDuration = duration;
}

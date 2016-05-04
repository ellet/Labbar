#include "stdafx.h"
#include "PlaySoundEvent.h"
#include "../../SoundManager/SoundManager.h"


PlaySoundEvent::PlaySoundEvent(const std::string &aSoundName, const bool aRepeat)
{
	mySoundName = aSoundName;
	myRepeat = aRepeat;
}


PlaySoundEvent::~PlaySoundEvent()
{
}

void PlaySoundEvent::OneShotEvent()
{
	SoundManager::PlayLoadedSound(mySoundName,myRepeat);
}

#include "stdafx.h"
#include "SoundManager.h"
#include <Macros/Macros.h>
#include <DLDebug/DL_Debug.h>
#include "../JsonParser/JsonParser.h"

SoundManager *SoundManager::ourInstance;
//irrklang::ISoundEngine *SoundManager::mySoundEngine;


//
//// PUBLIC:
//
void SoundManager::Create(void)
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SoundManager();
		GetInstance().mySoundEngine = irrklang::createIrrKlangDevice(); // Starting the sound engine w. default parameters
	}
}
void SoundManager::Destroy(void)
{
	GetInstance().mySoundEngine->drop();
	SAFE_DELETE(ourInstance)
}

void SoundManager::LoadSound()
{
	JsonParser::InitSounds(GetInstance().mySoundMap);
}
void SoundManager::PlayLoadedSound(const std::string &aSoundID, const bool aSoundIsLooped)
{
	std::map<std::string, std::string>::iterator it = GetInstance().mySoundMap.find(aSoundID);
	if ( it != GetInstance().mySoundMap.end() )
	{ 
		GetInstance().mySoundEngine->play2D(it->second.c_str(), aSoundIsLooped);
		return;
	}

	GetInstance().mySoundEngine->play2D(aSoundID.c_str(), aSoundIsLooped);
}
void SoundManager::PlaySoundFromPath(const std::string &aFilePath, const bool aSoundIsLooped)
{
	GetInstance().mySoundEngine->play2D(aFilePath.c_str(), aSoundIsLooped);
}

void SoundManager::StopAllSounds(void)
{
	GetInstance().mySoundEngine->stopAllSounds();
}
void SoundManager::PauseAllSounds(const bool aSoundIsPaused)
{
	GetInstance().mySoundEngine->setAllSoundsPaused(aSoundIsPaused);
}


//
//// PRIVATE:
//
SoundManager::SoundManager(void)
{
}
SoundManager::~SoundManager(void)
{
}



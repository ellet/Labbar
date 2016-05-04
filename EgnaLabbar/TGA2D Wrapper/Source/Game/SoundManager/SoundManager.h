#pragma once
#include <iostream>
#include <string>
#include <map>
#include <Macros/Macros.h>
#include <irrKlang.h>

//#pragma comment(lib, "irrKlang.lib") // Linking w. irrKlang.lib to enable use of irrKlang.dll

class SoundManager
{
public:
	static void Create(void);
	static void Destroy(void);

	static void LoadSound();
	static void PlayLoadedSound(const std::string &aSoundID, const bool aSoundIsLooped);
	static void PlaySoundFromPath(const std::string &aFilePath, const bool aSoundIsLooped);

	static void StopAllSounds(void);
	static void PauseAllSounds(const bool aSoundIsPaused);


private:
	SoundManager(void);
	~SoundManager(void);

	static SoundManager *ourInstance;
	irrklang::ISoundEngine *mySoundEngine;
	std::map<std::string, std::string> mySoundMap;
	inline static SoundManager& GetInstance(void);
};

inline SoundManager& SoundManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "SoundManager.ourInstance is nullptr");
	return (*ourInstance);
}



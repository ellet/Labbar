#include "stdafx.h"
#include "SoundManager.h"
#include "Audio/WwiseManager.h"
#include "Engine/SoundManager/PlaySoundEvent.h"
#include "Audio/SoundObjectIDManager.h"

namespace SB
{

	SoundManager::SoundManager()
	{
		myWwiseManager = std::make_unique<CWwiseManager>();
		myIDManager = std::make_unique<SoundObjectIDManager>();

		myBGMVolume = 100;
		mySFXVolume = 100;
		myDialogVolume = 100;

		Init("Audio/SoundBanks/Init.bnk");
	}

	SoundManager::~SoundManager()
	{
		myIDManager->UnregisterAllObjects(&*myWwiseManager);
	}

	bool SoundManager::Init(const char* aInitBank)
	{
		bool success = myWwiseManager->Init(aInitBank);
		myWwiseManager->SetErrorCallBack(&SoundManager::ErrorCallback);
		return success;
	}

	
	void SoundManager::Update()
	{
		myWwiseManager->Update();
	}

	void SoundManager::SetRTPC(const char* aRTPC, int aValue, int anObjectID)
	{
		if (myWwiseManager)
		{
			myWwiseManager->SetRTPC(aRTPC, aValue, anObjectID);
		}
	}

	void SoundManager::SetPosition(const Vector3f & aPosition, int aObjectID, const Vector3f & aDirection)
	{
		if (myWwiseManager)
		{
			myWwiseManager->SetPosition(aPosition.x, aPosition.y, aPosition.z, aObjectID);
		}
	}

	void SoundManager::SetListenerPosition(const Vector3f & aPosition, const Vector3f & aDirection)
	{
		if (myWwiseManager)
		{
			myWwiseManager->SetListenerPosition(aPosition.x, aPosition.y, aPosition.z, aDirection.x, aDirection.y, aDirection.z);
		}
	}

	
	int SoundManager::RegisterObjectAtFreeID()
	{
		int ID = myIDManager->GetNewID();
		if (myWwiseManager)
		{
			myWwiseManager->RegisterObject(ID);
		}
		if (ID >= DEFAULT_OBJECT)
		{
			Error("Too many Wwise ID's. Consider your life choices!");
		}
		return ID;
	}

	void SoundManager::UnRegisterObjectID(int anObjectID)
	{
		myIDManager->RemoveID(anObjectID);
	}
	const int GlobalObject = -1;

	void SoundManager::SetAmbientVolume(unsigned short aVolume)
	{
		myAmbientVolume = aVolume;
		myWwiseManager->SetRTPC("AmbientVolume", aVolume, GlobalObject);
	}


	void SoundManager::SetSFXVolume(unsigned short aVolume)
	{
		mySFXVolume = aVolume;
		myWwiseManager->SetRTPC("SFXVolume", aVolume, GlobalObject);
	}

	void SoundManager::SetBGMVolume(unsigned short aVolume)
	{
		myBGMVolume = aVolume;
		myWwiseManager->SetRTPC("BGMVolume", aVolume, GlobalObject);
	}

	void SoundManager::SetDialogVolume(unsigned short aVolume)
	{
		myDialogVolume = aVolume;
		myWwiseManager->SetRTPC("DialogVolume", aVolume, GlobalObject);
	}

	bool SoundManager::LoadBank(const char* aBankPath)
	{
		return myWwiseManager->LoadBank(aBankPath);
	}

	void SoundManager::UnLoadBank(const char* aBankPath)
	{
		return myWwiseManager->UnLoadBank(aBankPath);
	}

	void SoundManager::PostEvent(const char* aEvent)
	{
//#ifndef Publish
//		if (std::strcmp(aEvent, "") != 0)
//		{
//			std::cout << "Sound executed: " << aEvent << std::endl;
//		}
//#endif
		return myWwiseManager->PostEvent(aEvent);
	}

	void SoundManager::PostEvent(const char* aEvent, int aObjectID)
	{
//#ifndef Publish
//		if (std::strcmp(aEvent, "") != 0)
//		{
//			std::cout << "Sound executed: " << aEvent << " on object ID: " << aObjectID << std::endl;
//		}
//#endif
		return myWwiseManager->PostEvent(aEvent, aObjectID);
	}

	void SoundManager::PostEvent(const std::string& aEvent)
	{
		PostEvent(aEvent.c_str());
	}

	void SoundManager::PostEvent(const std::string& aEvent, int aObjectID)
	{
		PostEvent(aEvent.c_str(), aObjectID);
	}

	void SoundManager::ErrorCallback(const char* aError)
	{
		std::string temp = aError;
		std::wstring errorMsg(temp.begin(), temp.end());
		OutputDebugString(errorMsg.c_str());
	}

	

	ReceiveResult SoundManager::Receive(const PlaySoundEvent & aMessage)
	{
		PostEvent(aMessage.mySoundEventName);

		return ReceiveResult::eContinue;
	}

	unsigned short SoundManager::GetBGMVolume() const
	{
		return myBGMVolume;
	}

	unsigned short SoundManager::GetSFXVolume() const
	{
		return mySFXVolume;
	}

	unsigned short SoundManager::GetDialogVolume() const
	{
		return myDialogVolume;
	}


	unsigned short SoundManager::GetAmbientVolume() const
	{
		return myAmbientVolume;
	}

}

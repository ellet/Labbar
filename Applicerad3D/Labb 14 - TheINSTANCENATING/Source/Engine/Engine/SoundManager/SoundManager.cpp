#include "stdafx.h"
#include "SoundManager.h"
#include "Audio/WwiseManager.h"
#include "Engine/SoundManager/PlaySoundEvent.h"
#include "Audio/SoundObjectIDManager.h"

namespace ENGINE_NAMESPACE
{

	SoundManager::SoundManager()
	{
		myWwiseManager = std::make_unique<CWwiseManager>();
		myIDManager = std::make_unique<SoundObjectIDManager>();
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
		if (ID >= GAME_OBJECT_POSTEST)
		{
			Error("Too many Wwise ID's. Consider your life choices!");
		}
		return ID;
	}

	void SoundManager::UnRegisterObjectID(int anObjectID)
	{
		myIDManager->RemoveID(anObjectID);
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
		return myWwiseManager->PostEvent(aEvent);
	}

	void SoundManager::PostEvent(const char* aEvent, int aObjectID)
	{
		return myWwiseManager->PostEvent(aEvent, aObjectID);
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
}

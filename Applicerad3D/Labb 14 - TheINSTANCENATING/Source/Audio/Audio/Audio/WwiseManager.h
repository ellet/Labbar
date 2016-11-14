#pragma once

#define GAME_OBJECT_POSTEST 10000


struct AkMemSettings;
struct AkStreamMgrSettings;
struct AkDeviceSettings;
struct AkInitSettings;
struct AkPlatformInitSettings;
struct AkMusicSettings;
typedef wchar_t			AkOSChar;				///< Generic character string


class CWwiseManager
{
public:
	CWwiseManager();
	~CWwiseManager();
	bool Init(const char* aInitBank);
	void Update();
	bool LoadBank(const char* aBankPath);
	void UnLoadBank(const char* aBankPath);
	void PostEvent(const char* aEvent);
	void PostEvent(const char* aEvent, int aObjectID);

	typedef void(*callback_function)(const char*);
	void SetErrorCallBack(callback_function aErrorCallback);


	void SetRTPC(const char* aRTPC, int aValue, int aObjectID);
	void SetPosition(float aX, float aY, float aZ, int aObjectID, float aDirectionX = 0, float aDirectionY = 0, float aDirectionZ = 1.f);
	void SetListenerPosition(float aX, float aY, float aZ, float aDirectionX = 0, float aDirectionY = 0, float aDirectionZ = 1.f);

	void RegisterObject(int anObjectID);
	void UnRegisterObject(int anObjectID);
private:
	bool myIsInitialized;
	void TermWwise();
	bool InitWwise(AkMemSettings &in_memSettings, AkStreamMgrSettings &in_stmSettings, AkDeviceSettings &in_deviceSettings, AkInitSettings &in_initSettings, AkPlatformInitSettings &in_platformInitSettings, AkMusicSettings &in_musicInit, AkOSChar* in_szErrorBuffer, unsigned int in_unErrorBufferCharCount);
	void CallError(const char* aError);
	callback_function myErrorCallbck;
};


#pragma once
#include <Engine\PostMaster.h>

class CWwiseManager;
class SoundObjectIDManager;
namespace ENGINE_NAMESPACE
{

	struct PlaySoundEvent;

	class SoundManager : public Subscriber<PlaySoundEvent>
	{
	public:
		SoundManager();
		~SoundManager();

		bool Init(const char* aInitBank);
		bool LoadBank(const char* aBankPath);
		void UnLoadBank(const char* aBankPath);
		void PostEvent(const char* aEvent);
		void PostEvent(const char* aEvent, int aObjectID);
		void Update();


		void SetRTPC(const char* aRTPC, int aValue, int anObjectID);
		void SetPosition(const Vector3f & aPosition, int aObjectID, const Vector3f & aDirection = Vector3f(0.0f, 0.0f, 1.0f));
		void SetListenerPosition(const Vector3f & aPosition, const Vector3f & aDirection = Vector3f(0.0f, 0.0f, 1.0f));

		int RegisterObjectAtFreeID();
		void UnRegisterObjectID(int anObjectID);


		/*typedef void(*callback_function)(const char*);
		void SetErrorCallBack(callback_function aErrorCallback);*/

		virtual ReceiveResult Receive(const PlaySoundEvent & aMessage);

	private:
		std::unique_ptr<CWwiseManager> myWwiseManager;
		std::unique_ptr<SoundObjectIDManager> myIDManager;

		static void ErrorCallback(const char* aError);
	};

}

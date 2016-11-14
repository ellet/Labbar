#pragma once
#include "Engine\Component\BaseComponent.h"
namespace ENGINE_NAMESPACE
{
	struct RTPCUpdate
	{
		RTPCUpdate()
		{
			myRTPC = "";
			myRTPCValue = 0;
		}
		RTPCUpdate(const std::string & aRTPC, int aInitialValue = 0)
		{
			myRTPC = aRTPC;
			myRTPCValue = aInitialValue;
		}
		std::string myRTPC;
		int myRTPCValue;
	};
	class SpeakerComponent :
		public BaseComponent
	{
	public:
		SpeakerComponent();
		~SpeakerComponent();

		virtual void Initialize() override;
		void PostSoundEvent(const std::string & aSoundEvent);
		void RegisterRTPC(const std::string & aRTPCIdentifier);

		void SetRTPC(const std::string & aRTPCIdentifier, int aRTPCValue);

		virtual void Update(const Time & aDeltaTime) override;


		virtual void ToJson() const override;

	private:
		void UpdateRTPC();

		std::unordered_map<std::string, unsigned short> myRTPCIdentifiers;
		GrowingArray<RTPCUpdate> myRTPCValues;
		int mySoundID;
	};
}


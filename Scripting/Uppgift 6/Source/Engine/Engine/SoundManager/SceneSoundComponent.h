#pragma once
#include "Engine\Scene\Messages\EnterSceneMessage.h"
#include "Engine\Scene\Messages\ExitSceneMessage.h"


namespace SB
{
	class SceneSoundComponent :
		public BaseComponent, public Subscriber<EnterSceneMessage>, public Subscriber<ExitSceneMessage>
	{
	public:
		SceneSoundComponent();
		~SceneSoundComponent();
		
		void PlayAll();

		void StopAll();
		
		virtual void ToJson(JsonSerializer &aSerializer) const override;


		virtual void LoadData(DataNode aProperties) override;


		virtual ReceiveResult Receive(const EnterSceneMessage & aMessage) override;


		virtual ReceiveResult Receive(const ExitSceneMessage & aMessage) override;

	private:

		GrowingArray<std::string> mySounds;
		int mySoundID;
	};
}


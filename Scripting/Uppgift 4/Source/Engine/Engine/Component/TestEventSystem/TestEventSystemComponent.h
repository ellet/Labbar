#pragma once
#include "Engine\Component\BaseComponent.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"

namespace SB
{
	struct TestEvent;

	class TestEventSystemComponent :
		public BaseComponent, public EventSubscriber<TestEvent>
	{
	public:
		TestEventSystemComponent();
		~TestEventSystemComponent();

		virtual void Initialize() override;

		virtual void RecieveEvent(const TestEvent & aEvent) override;

	};

}

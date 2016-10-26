#pragma once
#include "Engine\Component\BaseComponent.h"


namespace ENGINE_NAMESPACE
{
	struct SphereShape;
	struct CollisionEvent;
	struct TriggerCollisionEvent;

	class RenderColliderComponent :
		public BaseComponent, public EventSubscriber<CollisionEvent>, public EventSubscriber<TriggerCollisionEvent>
	{
	public:
		RenderColliderComponent();
		~RenderColliderComponent();

		
		void Initialize() override;

		void Render() const override;


		void Update(const Time & aDeltaTime) override;


		void RecieveEvent(const CollisionEvent & aEvent) override;
		void RecieveEvent(const TriggerCollisionEvent& aEvent) override;

	private:

		Stopwatch myStopWatch;
		bool myHasCollided;
		bool myHasTriggered;
		
		GrowingArray<SphereShape> myRenderSpheres;

		Vector4f myRenderColor;
	};

}
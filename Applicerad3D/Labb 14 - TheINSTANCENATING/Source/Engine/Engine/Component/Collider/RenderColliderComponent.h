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

		virtual void DebugRender() const override;

		void Update(const Time & aDeltaTime) override;

		void RecieveEvent(const CollisionEvent & aEvent) override;
		void RecieveEvent(const TriggerCollisionEvent& aEvent) override;

		static void SwitchRenderColliders();


		virtual void ToJson() const override;

	private:
		static bool ourShouldRenderCollidersFlag;

		GrowingArray<Vector4f> myColors;
		GrowingArray<Stopwatch> myStopWatches;
		GrowingArray<bool> myHasCollidedFlags;
		GrowingArray<bool> myHasTriggeredFlags;
		GrowingArray<SphereShape> myRenderSpheres;
	};

}

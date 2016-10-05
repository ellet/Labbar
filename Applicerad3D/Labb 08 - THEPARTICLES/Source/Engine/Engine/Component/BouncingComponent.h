#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>

namespace ENGINE_NAMESPACE
{
	class BouncingComponent : public BaseComponent
	{
	public:
		BouncingComponent();
		~BouncingComponent();


		virtual void Update(const Time & aDeltaTime) override;

		virtual void Render() const override;

		virtual void Initialize() override;

	private:
		void MoveObject(const Time & aDeltaTime);
		void RotateObject(const Time & aDeltaTime, const Vector3f & aTargetDirection, const Vector3f & aCurrentDirection);

		float GetAngle(const float aFirstSide, const float aSecondSide, const float aThirdSide) const;

		//Temp debugging
		Vector3f myRotAxis;

		Randomizer myRandomizer;
		Vector3f myMovingTowardsPoint;
		Vector3f myVelocity;
		Vector3f myThrowingAwayVelocity;
		float myPointGravity;
	};
}

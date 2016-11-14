#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>

namespace ENGINE_NAMESPACE
{
	class BouncingComponent : public BaseComponent, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>
	{
	public:
		BouncingComponent();
		~BouncingComponent();


		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() const override;
		virtual void Initialize() override;

		ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;
		ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;

	private:
		void MoveObject(const Time & aDeltaTime);
		void RotateTowardsPoint(const Time & aDeltaTime, const Vector3f & aTargetPosition, const float aMaxRotationInDegrees);

		float GetAngleWithCross(const Vector3f & aProductFromNormalizedVectors) const;

		//void RotateWithLerp(const Time & aDeltaTime, const Vector3f & aTargetDirection);
		//void RotateTestLookAtCamera();

		//void MoveObjectPosition(const Time & aDeltaTime);
		//void MoveObjectWorldPosition(const Time & aDeltaTime);

		void DebugDraw();

		//Temp debugging
		Vector3f myRotAxis;

		Randomizer myRandomizer;
		GrowingArray<Vector3f> myPointPaths;
		Quaternion myTargetRot;
		Quaternion myObjectLastRot;
		std::string myDebugRotationText;
		unsigned short myActivatePoint;

		float myRotProgress;

		bool myHasRot;
		bool myHasFirst;

		bool myAngleIsPositive;

		bool myShouldProgress;
	};
}

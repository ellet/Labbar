#pragma once
#include "Engine\Component\BaseComponent.h"

namespace ENGINE_NAMESPACE
{

	class CircleMovementComponent : public BaseComponent
	{
	public:
		CircleMovementComponent();
		~CircleMovementComponent();

		void Update(const Time& aDeltaTime) override;
		void Initialize() override;

	private:
		Time myProgress;
		Vector3f myOrigin;
	};

};
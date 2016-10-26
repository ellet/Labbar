#pragma once
#include "Engine\Component\BaseComponent.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"


class MovementCollisionTestComponent :
	public SB::BaseComponent
{
public:
	MovementCollisionTestComponent();
	~MovementCollisionTestComponent();

	void SetVelocity(const SB::Vector3f & aVelocity);

	void Update(const SB::Time & aDeltaTime) override;

	void Render() const override;

	static SB::Vector3f ourConstraints;


private:
	SB::Vector3f GetMovement(const SB::Time & aDeltaTime);

	bool CheckIfInside(const SB::Vector3f & aPosition);


	SB::Vector3f myVelocity;
};


#pragma once

namespace ENGINE_NAMESPACE
{
	struct ParticleLogic
	{
		Vector3f myVelocity;
		Time myStartLifeTime;
		Time myLifeTimeLeft;
		float myStartSize;
	};
}

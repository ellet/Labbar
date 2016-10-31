#pragma once


namespace ENGINE_NAMESPACE
{
	struct ParticleSettings
	{
		Vector4f myStartColor;
		Vector4f myEndColor;

		Vector2f myMinMaxVelocityX;
		Vector2f myMinMaxVelocityY;
		Vector2f myMinMaxVelocityZ;
		Vector2f myMinMaxLifeTime;
		Vector2f myMinMaxSize;
		float myEndSizeInPercent;
		float myEmitCoolDown;

		//int myAmountOfParticles;
		unsigned short myAmountOfParticles;
	};
}

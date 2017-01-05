#pragma once

namespace SB
{
	struct VisualEffectVertex
	{
		Vector3f position;
		float size = 100;
		Vector4f color = Vector4f::One;
	};

	struct ShaderResourceCBufferData
	{
		float deltaTime;
		float runTime;
		Vector2f trash;
	};
}
#pragma once

namespace SB
{
	struct SpriteVertex
	{
		Vector4f position;
		Vector2f uv;

		Vector3f GetPosition() const
		{
			return position;
		}
	};
}

#pragma once

namespace SB
{
	struct Vertex
	{
		Vector4f position;
		Vector4f normal;
		Vector4f tangent;
		Vector4f bitangent;
		Vector4ui bones;
		Vector4f weights;
		Vector2f uv;
		Vector2f padding;

		Vector3f GetPosition() const
		{
			return position;
		}
	};
}

#pragma once

namespace SB
{
	struct LineVertex
	{
		Vector4f position;
		Color color;

		Vector3f GetPosition() const
		{
			return position;
		}
	};
}

#pragma once

struct SimpleVertex
{
	Vector4f position;
	Vector4f color;

	Vector3f GetPosition() const
	{
		return position;
	}
};

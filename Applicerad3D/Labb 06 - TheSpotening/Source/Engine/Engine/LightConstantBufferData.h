#pragma once

struct LightConstantBufferData
{
	struct DirectionLight
	{
		Vector4f direction;
		Vector4f color;
	} directionLight[1];

	struct PointLight
	{
		Vector3f myPosition = Vector3f(0.f, 0.f, 0.f);
		float myRange = 0.f;
		Vector3f myColor = Vector3f(0.f, 0.f, 0.f);
		float myIntensity = 0.f;
	} myPointLights[8];
};

#pragma once

namespace Tga2D
{
	class CLight
	{
	public:
		CLight();
		~CLight();
		void Render();
		Vector2f myPosition;
		Vector4f myColor;
		float myIntensity;
		float myFallOff;
	};
}
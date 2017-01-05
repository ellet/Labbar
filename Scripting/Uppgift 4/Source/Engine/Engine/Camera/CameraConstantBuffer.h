#pragma once

namespace SB
{
	struct CameraConstantBuffer
	{
		Matrix44f view;
		Matrix44f projection;

		Matrix44f previousView;
		Matrix44f previousProjection;

		Vector4f cameraPosition;
	};
}

#pragma once
#include "Engine\Buffer\VertexBuffer.h"


namespace ENGINE_NAMESPACE
{
	class FullScreenEffect;

	struct FullScreenVertex
	{
		Vector4f myPosition;
		Vector2f myUV;
	};

	class FullscreenHelper
	{
	public:
		FullscreenHelper();
		~FullscreenHelper();

		void CopyTextureToTarget(const std::shared_ptr<Texture> & aTextureToCopyFrom);

	private:
		std::unique_ptr<FullScreenEffect> myCopyEffect;
		std::unique_ptr<VertexBuffer<FullScreenVertex>> myVertexBuffer;
		GrowingArray<FullScreenVertex> myVertices;
	};
}
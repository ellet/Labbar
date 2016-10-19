#include "stdafx.h"
#include "FullscreenHelper.h"
#include "Engine\Effect\FullScreenEffect.h"

namespace ENGINE_NAMESPACE
{

	FullscreenHelper::FullscreenHelper()
	{
		myVertices.Resize(6);

		myVertices[0].myPosition = Vector4f(-1.f, -1.f, 0.5f, 1.f);
		myVertices[1].myPosition = Vector4f(-1.f, 1.f, 0.5f, 1.f);
		myVertices[2].myPosition = Vector4f(1.f, -1.f, 0.5f, 1.f);

		myVertices[3].myPosition = Vector4f(1.f, 1.f, 0.5f, 1.f);
		myVertices[4].myPosition = Vector4f(1.f, -1.f, 0.5f, 1.f);
		myVertices[5].myPosition = Vector4f(-1.f, 1.f, 0.5f, 1.f);

		myVertices[0].myUV = Vector2f(0.f, 1.f);
		myVertices[1].myUV = Vector2f(0.f, 0.f);
		myVertices[2].myUV = Vector2f(1.f, 1.f);

		myVertices[3].myUV = Vector2f(1.f, 0.f);
		myVertices[4].myUV = Vector2f(1.f, 1.f);
		myVertices[5].myUV = Vector2f(0.f ,0.f);

		myVertexBuffer = std::make_unique<VertexBuffer<FullScreenVertex>>(&myVertices[0], myVertices.Size(), true);
		myCopyEffect = std::make_unique<FullScreenEffect>();
	}


	FullscreenHelper::~FullscreenHelper()
	{
	}

	void FullscreenHelper::CopyTextureToTarget(const std::shared_ptr<Texture> & aTextureToCopyFrom)
	{
		aTextureToCopyFrom->BindToPS(0);

		myVertexBuffer->Bind(0);

		myCopyEffect->Bind();

		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Engine::GetInstance().GetRenderer().GetContext()->Draw(myVertices.Size(), 0);
	}

}
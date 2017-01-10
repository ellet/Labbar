#include "stdafx.h"
#include "Engine\Model\Mesh.h"
#include <d3dcommon.h>
#include <d3d11.h>
#include "Engine\Vertex\SimpleVertex.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\IndexBuffer.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\ModelRenderer.h"

namespace SB
{
	std::atomic<size_t> GenericMesh::ourIdentifierCounter = 1;

	GenericMesh::GenericMesh(const Surface & aSurface)
	{
		myTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		myVertexCount = 0;
		myIndexCount = 0;
		mySurface = aSurface;
		myIdentifier = ourIdentifierCounter.fetch_add(1);
		myMinimumRenderDistance = -1.0f;
		myMaximumRenderDistance = -1.0f;
	}

	size_t GenericMesh::GetIdentifier() const
	{
		return myIdentifier;
	}

	void GenericMesh::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY & aTopology)
	{
		myTopology = aTopology;
	}

	GenericMesh::~GenericMesh()
	{
	}

	void GenericMesh::SetSurface(const Surface & aSurface)
	{
		mySurface = aSurface;
	}

	void GenericMesh::Render(const std::shared_ptr<Effect>& aEffect) const
	{
		mySurface.BindToPS();

		aEffect->Bind();

		myVertexBuffer->Bind(0);
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(myTopology);

		myIndexBuffer->Bind();
		Engine::GetInstance().GetRenderer().GetContext()->DrawIndexed(myIndexCount, 0, 0);
	}

	void GenericMesh::RenderInstanced(const std::shared_ptr<Effect>& aEffect, int aInstanceCount) const
	{
		mySurface.BindToPS();
		
		if (aEffect->Prepare(true) == false)
		{
			return;
		}
		
		aEffect->Bind();

		myVertexBuffer->Bind(0);
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(myTopology);

		myIndexBuffer->Bind();
		Engine::GetInstance().GetRenderer().GetContext()->DrawIndexedInstanced(myIndexCount, aInstanceCount, 0, 0, 0);
	}

	const BoundingBoxf & GenericMesh::GetBoundingBox()
	{
		return myBoundingBox;
	}

	bool GenericMesh::Prepare(bool aLoadAsynchronously)
	{
		return mySurface.Prepare(aLoadAsynchronously);
	}

	ResourceStatus GenericMesh::GetLoadStatus() const
	{
		return mySurface.GetLoadStatus();
	}

	void GenericMesh::CreateMesh(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount)
	{
		if (myVertexBuffer != nullptr)
		{
			Error("Mesh already created!");
			return;
		}

		myVertexBuffer = std::make_unique<GenericVertexBuffer>(aVertexData, aVertexCount * aVertexSizeInBytes, aVertexSizeInBytes);
		myIndexBuffer = std::make_unique<IndexBuffer>(aIndexData, aIndexCount);

		myVertexCount = aVertexCount;
		myIndexCount = aIndexCount;
	}

	void GenericMesh::SetMinMaxRenderDistance(float aMinDistance, float aMaxDistance)
	{
		myMinimumRenderDistance = aMinDistance;
		myMaximumRenderDistance = aMaxDistance;
	}
}

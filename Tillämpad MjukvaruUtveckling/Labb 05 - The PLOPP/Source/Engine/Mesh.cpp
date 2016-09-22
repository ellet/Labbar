#include "stdafx.h"
#include "Mesh.h"
#include <d3dcommon.h>
#include <d3d11.h>
#include "SimpleVertex.h"
#include "VertexBuffer.h"
#include "DXRenderer.h"
#include "IndexBuffer.h"
#include "Effect.h"
#include "Texture.h"
#include "ModelRenderer.h"

GenericMesh::GenericMesh(const std::shared_ptr<Texture> & aTexture)
{
	myVertexCount = 0;
	myIndexCount = 0;
	myTextures[0] = aTexture;
	myIdentifier = 0;
}

size_t GenericMesh::GetIdentifier() const
{
	return myIdentifier;
}

void GenericMesh::AssignIdentifier(size_t aIdentifier)
{
	if (myIdentifier != 0)
	{
		Engine::GetInstance().GetRenderer().GetModelRenderer().ReturnBatchIdentifier(myIdentifier);
	}
	myIdentifier = aIdentifier;
}

GenericMesh::~GenericMesh()
{
	if (myIdentifier != 0)
	{
		Engine::GetInstance().GetRenderer().GetModelRenderer().ReturnBatchIdentifier(myIdentifier);
		myIdentifier = 0;
	}
}

void GenericMesh::SetTexture(const std::shared_ptr<Texture> & aTexture, const unsigned int aTextureIndex)
{
	myTextures[aTextureIndex] = aTexture;
}

void GenericMesh::Render() const
{
	if (myTextures[0] != nullptr)
	{
		myTextures[0]->BindToPS(0);
	}
	if (myTextures[1] != nullptr)
	{
		myTextures[1]->BindToPS(1);
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexed(myIndexCount, 0, 0);
}

void GenericMesh::RenderInstanced(int aInstanceCount) const
{
	if (myTextures[0] != nullptr)
	{
		myTextures[0]->BindToPS(0);
	}
	if (myTextures[1] != nullptr)
	{
		myTextures[1]->BindToPS(1);
	}

	if (myEffect != nullptr)
	{
		myEffect->Bind();
	}

	myVertexBuffer->Bind(0);
	Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	myIndexBuffer->Bind();
	Engine::GetInstance().GetRenderer().GetContext()->DrawIndexedInstanced(myIndexCount, aInstanceCount, 0, 0, 0);
}

std::shared_ptr<Texture> GenericMesh::GetTexture(const unsigned int aTextureIndex)
{
	return myTextures[aTextureIndex];
}

const BoundingBoxf & GenericMesh::GetBoundingBox()
{
	return myBoundingBox;
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

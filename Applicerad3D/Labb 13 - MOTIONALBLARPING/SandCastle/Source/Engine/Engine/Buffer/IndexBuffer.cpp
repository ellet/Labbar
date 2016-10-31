#include "stdafx.h"
#include "Engine\Buffer\IndexBuffer.h"
#include <d3d11.h>
#include "Engine\Rendering\DXRenderer.h"

namespace ENGINE_NAMESPACE
{
	IndexBuffer::IndexBuffer(const unsigned int * aFirstIndex, unsigned int aIndexCount, bool aIsImmutable)
		: Buffer(D3D11_BIND_INDEX_BUFFER, aIsImmutable ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC, aIsImmutable ? 0 : D3D11_CPU_ACCESS_WRITE, 0, aFirstIndex, aIndexCount * sizeof(unsigned int))
	{
	}

	IndexBuffer::IndexBuffer(const std::vector<unsigned int> & aIndices, bool aIsImmutable)
		: IndexBuffer(&aIndices[0], static_cast<unsigned int>(aIndices.size()), aIsImmutable)
	{
	}

	void IndexBuffer::Bind()
	{
		Engine::GetInstance().GetRenderer().GetContext()->IASetIndexBuffer(GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
	}

	int IndexBuffer::GetCount() const
	{
		return GetSizeInBytes() / sizeof(unsigned int);
	}

	void IndexBuffer::UpdateData(const unsigned* aInitialData, int aIndexCount, bool aAllowResize, int aBufferBeginsAt)
	{
		Buffer::UpdateData(aInitialData, sizeof(unsigned int) * aIndexCount, aAllowResize, aBufferBeginsAt * sizeof(unsigned int));
	}

	IndexBuffer::~IndexBuffer()
	{
	}
}

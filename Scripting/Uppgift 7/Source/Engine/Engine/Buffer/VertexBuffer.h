#pragma once
#include "Engine\Buffer\Buffer.h"

namespace SB
{
	class GenericVertexBuffer : public Buffer
	{
	public:
		GenericVertexBuffer(const void * aData, int aSizeInBytes, int aVertexSize, bool aIsImmutable = true);
		~GenericVertexBuffer();

		int GetVertexSize() const;
		int GetCount() const;

		void Bind(int aSlot) const;

	private:
		int myVertexSize;
	};

	template<typename TVertex>
	class VertexBuffer : public GenericVertexBuffer
	{
	public:
		VertexBuffer(const TVertex *aInitialData, int aVertexCount, bool aIsImmutable = true);
		~VertexBuffer();

		void UpdateData(const TVertex *aInitialData, int aVertexCount, bool aAllowResize = false, int aBufferBeginsAt = 0);
	};

	template<typename TVertex>
	VertexBuffer<TVertex>::VertexBuffer(const TVertex *aInitialData, int aVertexCount, bool aIsImmutable)
		: GenericVertexBuffer(aInitialData, sizeof(TVertex) * aVertexCount, sizeof(TVertex), aIsImmutable)
	{
	}

	template<typename TVertex>
	void VertexBuffer<TVertex>::UpdateData(const TVertex *aInitialData, int aVertexCount, bool aAllowResize, int aBufferBeginsAt)
	{
		GenericVertexBuffer::UpdateData(aInitialData, sizeof(TVertex) * aVertexCount, aAllowResize, aBufferBeginsAt * sizeof(TVertex));
	}

	template<typename TVertex>
	VertexBuffer<TVertex>::~VertexBuffer()
	{
	}
}

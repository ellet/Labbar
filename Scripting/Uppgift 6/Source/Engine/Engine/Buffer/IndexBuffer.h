#pragma once
#include "Engine\Buffer\Buffer.h"

namespace SB
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const unsigned int * aFirstIndex, unsigned int aIndexCount, bool aIsImmutable = true);
		IndexBuffer(const std::vector<unsigned int> & aIndices, bool aIsImmutable = true);
		void Bind();
		~IndexBuffer();

		int GetCount() const;

		void UpdateData(const unsigned int *aInitialData, int aIndexCount, bool aAllowResize = false, int aBufferBeginsAt = 0);
	};
}

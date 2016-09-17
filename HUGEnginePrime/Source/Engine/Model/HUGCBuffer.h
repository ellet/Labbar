#pragma once
#include <d3d11.h>
class CHUGCBuffer
{
public:
	CHUGCBuffer();
	~CHUGCBuffer();

	void Init(const int aSizeOfBuffer);

	void Activate();

	template <typename DataType>
	void SetData(const DataType& aDataToSet);

private:
	ID3D11Buffer * myMatrixBuffer;
	char * myDataPtr;

	int myDataSize;
	int myCurrentIndex;
};

template <typename DataType>
void CHUGCBuffer::SetData(const DataType & aDataToSet)
{
	&myDataPtr[myCurrentIndex] = &aDataToSet;
	myCurrentIndex += sizeof(DataType);
}

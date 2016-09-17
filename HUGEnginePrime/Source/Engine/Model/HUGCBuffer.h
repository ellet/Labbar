#pragma once
#include <d3d11.h>
class CHUGCBuffer
{
public:
	CHUGCBuffer();
	~CHUGCBuffer();

	void Init(const int aSizeOfBuffer, const int aRegisterIndex);

	void Activate();

	template <typename DataType>
	void SetData(const DataType& aDataToSet);

private:
	ID3D11Buffer * myBuffer;
	char * myDataPtr;

	int myRegisterIndex;

	int myDataSize;
	int myCurrentIndex;
	
};

template <typename DataType>
void CHUGCBuffer::SetData(const DataType & aDataToSet)
{
	memcpy(&myDataPtr[myCurrentIndex], &aDataToSet, sizeof(DataType));
	myCurrentIndex += sizeof(DataType);
}

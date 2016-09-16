#pragma once
class CHUGCBuffer
{
public:
	CHUGCBuffer();
	~CHUGCBuffer();

	void Init();

	//void Activate();

	//void SetDAta()

private:
	ID3D11Buffer * myMatrixBuffer;
};
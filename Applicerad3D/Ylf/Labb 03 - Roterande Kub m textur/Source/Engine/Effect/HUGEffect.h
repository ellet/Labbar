#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

class CHUGEffect
{
public:
	struct MatrixBufferType
	{
		CU::Matrix44f myToWorld;
		CU::Matrix44f myToCamera;
		CU::Matrix44f myToProjection;
	};

	CHUGEffect();
	~CHUGEffect();

	void Init();
	void Active();
	void Inactivate();

	void SetShaderResources(const CU::Matrix44f aWorldMatrix, const CU::Matrix44f aCameraMatrix,
		const CU::Matrix44f aProjectionMatrix, ID3D11ShaderResourceView* aTexture);

private:

	ID3D11VertexShader * myVertexShader;
	ID3D11PixelShader * myPixelShader;
	ID3D11InputLayout * myLayout;
	ID3D11Buffer * myMatrixBuffer;
	ID3D11SamplerState * mySampleState;
};
#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

struct MatrixBuffer
{
	CU::Matrix44f myWorld;
	CU::Matrix44f myCamera;
	CU::Matrix44f myProjection;
};

//class ShaderResourceView;

class CHUGEffect
{
public:


	CHUGEffect();
	~CHUGEffect();

	void Init(const std::wstring & aTextureFilePath);
	void ActivateEffect(const MatrixBuffer & aMatrixBuffer);

private:
	void SetMatrixes(const MatrixBuffer & aMatrixBuffer);

	ID3D11VertexShader * myVertexShader;
	ID3D11PixelShader * myPixelShader;
	ID3D11InputLayout * myLayout;
	
	ID3D11ShaderResourceView * myTexture;

	/*Cbuffer mymatrixbuffer*/

	ID3D11SamplerState * mySampleState;
};
#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

class CHUGEffect
{
public:


	CHUGEffect();
	~CHUGEffect();

	void Init();
	void Active();

private:

	ID3D11VertexShader * myVertexShader;
	ID3D11PixelShader * myPixelShader;
	ID3D11InputLayout * myLayout;
};
#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;

struct ID3D11Texture2D;

class CHUGTexture
{
public:
	CHUGTexture();
	~CHUGTexture();

	void Init(ID3D11Device* aDevice, ID3D11DeviceContext* aDeviceContext, const std::string & aFileName);

	void Release();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11Texture2D* myTexture;
	ID3D11ShaderResourceView* myTextureView;
};


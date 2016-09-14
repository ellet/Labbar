#include "stdafx.h"
#include "Model/Texture/HUGTexture.h"
#include "Model/TextureLoader/dds.h"
#include "Model/TextureLoader/DDSTextureLoader.h"
#include "Model/TextureLoader/DirectXHelpers.h"
#include "Model/TextureLoader/PlatformHelpers.h"


CHUGTexture::CHUGTexture()
{
	myTexture = nullptr;
	myTextureView = nullptr;
}

CHUGTexture::~CHUGTexture()
{
}

void CHUGTexture::Init(ID3D11Device* aDevice, ID3D11DeviceContext* aDeviceContext, const std::wstring & aFileName)
{
	HRESULT tempResult = S_OK;


	tempResult = DirectX::CreateDDSTextureFromFile(aDevice, aFileName.c_str(), nullptr, &myTextureView);
	DL_ASSERT(tempResult == S_OK, "failed to load sprite!");
}

void CHUGTexture::Release()
{
	myTexture->Release();
	myTextureView->Release();

	myTexture = nullptr;
	myTextureView = nullptr;
}

ID3D11ShaderResourceView* CHUGTexture::GetTexture()
{
	return myTextureView;
}

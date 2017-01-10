#include "stdafx.h"
#include "Engine\Texture\WorldRenderTexture.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Buffer\DepthBuffer.h"
#include "RenderTexture.h"

namespace SB
{
	WorldRenderTexture::WorldRenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer)
		: RenderTexture(aWidth, aHeight, aGenerateDepthBuffer, nullptr)
	{
		AddRenderTexture(DXGI_FORMAT_R16G16B16A16_FLOAT);
		AddRenderTexture(DXGI_FORMAT_R16G16_FLOAT);

		myModelRenderer = std::make_unique<ModelRenderer>();
	}

	WorldRenderTexture::~WorldRenderTexture()
	{
	}

	ID3D11RenderTargetView * WorldRenderTexture::GetView(WorldRenderTarget aTarget) const
	{
		return RenderTexture::GetView(static_cast<unsigned short>(aTarget));
	}

	const std::shared_ptr<Texture> & WorldRenderTexture::GetTexture(WorldRenderTarget aTarget) const
	{
		return RenderTexture::GetTexture(static_cast<unsigned short>(aTarget));
	}

	ModelRenderer& WorldRenderTexture::GetModelRenderer()
	{
		return *myModelRenderer;
	}

	void WorldRenderTexture::RenderBuffer()
	{
		Bind(0);
		GetModelRenderer().RenderBuffer();
	}
}

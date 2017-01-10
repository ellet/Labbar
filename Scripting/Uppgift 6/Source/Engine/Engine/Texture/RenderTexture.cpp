#include "stdafx.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Buffer\DepthBuffer.h"

namespace SB
{
	RenderTexture::RenderTexture(unsigned aWidth, unsigned aHeight, bool aGenerateDepthBuffer, nullptr_t)
	{
		if (aGenerateDepthBuffer)
		{
			myDepthBuffer = std::make_unique<DepthBuffer>(aWidth, aHeight);
		}
	
		myWidth = aWidth;
		myHeight = aHeight;
	}

	RenderTexture::RenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer, DXGI_FORMAT aFormat)
		: RenderTexture(aWidth, aHeight, aGenerateDepthBuffer, nullptr)
	{
		AddRenderTexture(aFormat);
	}

	RenderTexture::RenderTexture(ID3D11Texture2D * aTexture, ID3D11RenderTargetView * aRenderTarget, ID3D11ShaderResourceView * aShaderResourceView, unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer)
	{
		myTextures.Resize(1);

		myTextures[0].texture = std::make_shared<Texture>(aTexture, aShaderResourceView, aWidth, aHeight);
		myTextures[0].renderTargetView = aRenderTarget;
		myTextures[0].renderTargetView->AddRef();

		if (aGenerateDepthBuffer)
		{
			myDepthBuffer = std::make_unique<DepthBuffer>(aWidth, aHeight);
		}

		myWidth = aWidth;
		myHeight = aHeight;
	}

	RenderTexture::~RenderTexture()
	{
		for (unsigned short i = 0; i < myTextures.Size(); i++)
		{
			SAFE_RELEASE(myTextures[i].renderTargetView);
		}
	}

	void RenderTexture::Bind(int aSlot, bool aUpdateViewport)
	{
		Engine::GetRenderer().StoreRenderTargetResolution(Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));

		ID3D11RenderTargetView * renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { };
		ID3D11DepthStencilView * depthStencilView = nullptr;
		
		for (unsigned short i = 0; i < myTextures.Size(); i++)
		{
			renderTargets[aSlot + i] = myTextures[i].renderTargetView;
		}

		if (myDepthBuffer != nullptr)
		{
			depthStencilView = myDepthBuffer->GetView();
		}

		Engine::GetInstance().GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, depthStencilView);

		if (aUpdateViewport)
		{
			Engine::GetInstance().GetRenderer().SetViewport(Vector2f::Zero, Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));
		}
	}

	unsigned int RenderTexture::GetWidth() const
	{
		return myWidth;
	}

	unsigned int RenderTexture::GetHeight() const
	{
		return myHeight;
	}

	const std::shared_ptr<DepthBuffer> & RenderTexture::GetDepthBuffer()
	{
		return myDepthBuffer;
	}

	std::shared_ptr<const DepthBuffer> RenderTexture::GetDepthBuffer() const
	{
		return myDepthBuffer;
	}

	ID3D11RenderTargetView * RenderTexture::GetView(const unsigned short aIndex) const
	{
		return myTextures[aIndex].renderTargetView;
	}

	const std::shared_ptr<Texture> & RenderTexture::GetTexture(const unsigned short aIndex) const
	{
		return myTextures[aIndex].texture;
	}

	void RenderTexture::AddRenderTexture(DXGI_FORMAT aFormat)
	{
		RenderTextureData data;
		data.texture = std::make_shared<Texture>(myWidth, myHeight, aFormat, true);
		data.format = aFormat;

		CheckDXError(
			Engine::GetInstance().GetRenderer().GetDevice()->CreateRenderTargetView(data.texture->GetTexture(), nullptr, &data.renderTargetView);
		);

		myTextures.Add(data);
	}

	void RenderTexture::Resize(unsigned aWidth, unsigned aHeight)
	{
		GrowingArray<RenderTextureData> previousData = myTextures;
		myTextures.RemoveAll();

		myWidth = aWidth;
		myHeight = aHeight;

		for (unsigned short i=0; i<previousData.Size(); i++)
		{
			AddRenderTexture(previousData[i].format);
			SAFE_RELEASE(previousData[i].renderTargetView);
		}
	}

	void RenderTexture::Clear(const Vector4f & aColor)
	{
		for (unsigned short i = 0; i < myTextures.Size(); i++)
		{
			Engine::GetInstance().GetRenderer().GetContext()->ClearRenderTargetView(myTextures[i].renderTargetView, &aColor.x);
		}

		if (myDepthBuffer)
		{
			myDepthBuffer->Clear();
		}
	}
}

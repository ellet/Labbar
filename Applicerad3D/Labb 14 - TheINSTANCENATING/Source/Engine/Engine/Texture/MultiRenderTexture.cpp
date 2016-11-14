#include "stdafx.h"
#include "Engine\Texture\MultiRenderTexture.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include "Engine\Buffer\DepthBuffer.h"
#include "RenderTexture.h"

namespace ENGINE_NAMESPACE
{
	MultiRenderTexture::MultiRenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer)
	{
		if (aGenerateDepthBuffer)
		{
			myDepthBuffer = std::make_unique<DepthBuffer>(aWidth, aHeight);
		}

		myWidth = aWidth;
		myHeight = aHeight;
	}

	void MultiRenderTexture::AddTexture(DXGI_FORMAT aFormat, eRenderTargets aRenderTarget)
	{
		if (static_cast<unsigned short> (aRenderTarget) >= myRenderTargetViews.Size())
		{
			myRenderTargetViews.Resize(static_cast<unsigned short> (aRenderTarget) + 1);
		}
		myRenderTargetViews[static_cast<unsigned short> (aRenderTarget)] = std::make_shared<RenderTexture>(myWidth, myHeight, false, aFormat);
	}

	MultiRenderTexture::~MultiRenderTexture()
	{
	}

	void MultiRenderTexture::Bind()
{
		Engine::GetRenderer().StoreRenderTargetResolution(Vector2f(static_cast<float>(myWidth), static_cast<float>(myHeight)));

		ID3D11RenderTargetView * views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
		for (unsigned short i = 0; i < myRenderTargetViews.Size(); i++)
		{
			views[i] = myRenderTargetViews[i]->GetView();
		}
		Engine::GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, views, myDepthBuffer->GetView());
	}

	unsigned int MultiRenderTexture::GetWidth() const
	{
		return myWidth;
	}

	unsigned int MultiRenderTexture::GetHeight() const
	{
		return myHeight;
	}
	
	const std::shared_ptr<DepthBuffer> & MultiRenderTexture::GetDepthBuffer()
	{
		return myDepthBuffer;
	}

	std::shared_ptr<const DepthBuffer> MultiRenderTexture::GetDepthBuffer() const
	{
		return myDepthBuffer;
	}

	const std::shared_ptr<ENGINE_NAMESPACE::RenderTexture> & MultiRenderTexture::GetRenderTexture(eRenderTargets aTarget) const
	{
		return myRenderTargetViews[static_cast<unsigned short> (aTarget)];
	}

	std::shared_ptr<ENGINE_NAMESPACE::RenderTexture> &MultiRenderTexture::GetRenderTexture(eRenderTargets aTarget)
	{
		return myRenderTargetViews[static_cast<unsigned short> (aTarget)];
	}

	void MultiRenderTexture::Clear(const Vector4f & aColor)
	{
		for (unsigned short i = 0; i < myRenderTargetViews.Size(); i++)
		{
			Engine::GetInstance().GetRenderer().GetContext()->ClearRenderTargetView(myRenderTargetViews[i]->GetView(), reinterpret_cast<const float*>(&aColor));

		}
		if (myDepthBuffer)
		{
			myDepthBuffer->Clear();
		}
	}
}

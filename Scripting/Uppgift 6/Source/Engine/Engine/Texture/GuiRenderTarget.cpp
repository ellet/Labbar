#include "stdafx.h"
#include "GuiRenderTarget.h"
#include "Engine/Rendering/SpriteRenderer.h"
#include "Engine/GenericEngineMessages.h"

namespace SB
{
	GuiRenderTarget::GuiRenderTarget(unsigned aWidth, unsigned aHeight)
		: RenderTexture(aWidth, aHeight, false, DXGI_FORMAT_R8G8B8A8_UNORM)
	{
		mySpriteRenderer = std::make_unique<SpriteRenderer>();
	}

	GuiRenderTarget::~GuiRenderTarget()
	{
	}

	void GuiRenderTarget::Render(const Sprite& aSprite) const
	{
		mySpriteRenderer->Render(aSprite);
	}

	SpriteRenderer& GuiRenderTarget::GetSpriteRenderer()
	{
		return *mySpriteRenderer;
	}

	void GuiRenderTarget::RenderBuffer()
	{
		Bind(0);
		mySpriteRenderer->RenderBuffer();
	}

	ReceiveResult GuiRenderTarget::Receive(const WindowSizeChangedMessage& aMessage)
	{
		Resize(aMessage.myWidth, aMessage.myHeight);
		return ReceiveResult::eContinue;
	}
}

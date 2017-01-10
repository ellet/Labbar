#pragma once
#include "RenderTexture.h"

namespace SB
{
	class SpriteRenderer;

	class GuiRenderTarget : public RenderTexture, public Subscriber<WindowSizeChangedMessage>
	{
	public:
		GuiRenderTarget(unsigned int aWidth, unsigned int aHeight);
		~GuiRenderTarget();

		void Render(const Sprite & aSprite) const;

		SpriteRenderer & GetSpriteRenderer();
		void RenderBuffer();

		ReceiveResult Receive(const WindowSizeChangedMessage& aMessage) override;
		
	private:
		std::unique_ptr<SpriteRenderer> mySpriteRenderer;
	};
}

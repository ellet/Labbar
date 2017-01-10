#pragma once

namespace SB
{
	class Effect;
	class Texture;
	class Model;

	class TextureDebugger
	{
	public:
		TextureDebugger(const unsigned int aNewWidth, const unsigned int aNewHeight);
		~TextureDebugger();

		void Resize(const unsigned int aNewWidth, const unsigned int aNewHeight);

		void Render();

		void QueueRender(std::shared_ptr<Texture> aTextureToView);

	private:
		Sprite mySprite;
		std::unique_ptr<RenderTexture> myRenderTexture;
	};
}

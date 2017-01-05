#pragma once

namespace SB
{

	class SpriteEffect;
	class QuadSpriteShape;
	class FullscreenQuadSpriteShape;
	class Sprite;

	template<typename T>
	class VertexBuffer;

	struct SpriteInstanceData
	{
		Matrix44f toWorld;
		Vector4f color;
		Vector2f textureTopLeft;
		Vector2f textureSize;
	};


	class SpriteRenderer
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Render(const Sprite &aSprite);
		void RenderBuffer();
		void RenderFullscreenQuad(const std::shared_ptr<Texture>& aTexture, std::shared_ptr<const Effect> aEffect = nullptr);

	private:
		void SetupInstanceBufferAndBind();

		std::shared_ptr<const Texture> myCurrentSpriteTexture;
		std::shared_ptr<const Effect> myCurrentSpriteEffect;

		GrowingArray<SpriteInstanceData, int> myInstanceData;
		GrowingArray<VertexBuffer<SpriteInstanceData>*> myInstanceBuffers;

		std::shared_ptr<SpriteEffect> mySpriteEffect;
		std::unique_ptr<QuadSpriteShape> myQuad;
		std::unique_ptr<FullscreenQuadSpriteShape> myFullscreenQuad;
	};

}

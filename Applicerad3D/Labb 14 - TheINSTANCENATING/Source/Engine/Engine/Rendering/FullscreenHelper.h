#pragma once
#include "..\Sprite\SpriteVertex.h"
#include "..\Texture\Texture.h"


namespace ENGINE_NAMESPACE
{

	

	struct SpriteVertex;

	template <typename TVertexBufferType>
	class VertexBuffer;


	enum class eEffectBundles
	{
		eBloom = 1 << 0,
		eHDR = 1 << 1,
		eMotionBlur = 1 << 2
	};

	inline unsigned int operator & (unsigned int aLeft, eEffectBundles aRight)
	{
		return aLeft & static_cast<unsigned int> (aRight);
	}

	inline unsigned int operator & (eEffectBundles aLeft, eEffectBundles aRight)
	{
		return static_cast<unsigned int> (aLeft) & static_cast<unsigned int> (aRight);
	}

	inline unsigned int operator | (unsigned int aLeft, eEffectBundles aRight)
	{
		return aLeft | static_cast<unsigned int> (aRight);
	}

	inline unsigned int operator | (eEffectBundles aLeft, eEffectBundles aRight)
	{
		return static_cast<unsigned int> (aLeft) | static_cast<unsigned int> (aRight);
	}

	class FullscreenHelper
	{
	public:
		enum class eFullscreenEffects
		{
			eCopy,
			eLuminance,
			eGaussianBlurHorizontal,
			eGaussianBlurVertical,
			eAdd,
			eToneMapping,
			eMotionBlur,
			eSizeOf
		};

		FullscreenHelper(unsigned int aWidth, unsigned int aHeight);
		~FullscreenHelper();

		void DoFullscreenEffects(std::shared_ptr<MultiRenderTexture> & aIntermediateTexture, unsigned int aEffectsToRun, unsigned int aStepsToShow);
		
		void DoEffectNoSwap(FullscreenHelper::eFullscreenEffects aEffect,
			std::shared_ptr<RenderTexture> aTargetTexture,
			std::shared_ptr<RenderTexture> aResourceTexture);

		void CopyRenderTexture(std::shared_ptr<RenderTexture> &aTarget, const std::shared_ptr<RenderTexture> &aSource);
	private:
		void DoEffect(eFullscreenEffects aEffect);
		void DoEffect(std::shared_ptr<RenderTexture> aTarget, std::shared_ptr<RenderTexture> aSourceTexture, std::shared_ptr<RenderTexture> aSecondSourceTexture, eFullscreenEffects aFullscreenEffect);
		void CopyInput();
		void DoHDR(bool aShowSteps);
		void Downsample(unsigned int aDestination);
		void DoBloom(bool aShowSteps);
		void DoMotionBlur();
		void DrawEffect(FullscreenHelper::eFullscreenEffects aEffect);

		std::shared_ptr<RenderTexture> myTargetTexture;

		std::shared_ptr<RenderTexture> myTextures[2];

		std::shared_ptr<RenderTexture> mySourceTexture;
		std::shared_ptr<RenderTexture> myInputTexture;
		GrowingArray<std::shared_ptr<RenderTexture>> myDownsamples;
		std::shared_ptr<RenderTexture> mySmallestBloomdownsample;

		SpriteVertex myVertices[6];
		GrowingArray<std::shared_ptr<Effect>>myEffects;

		std::unique_ptr<VertexBuffer<SpriteVertex>> myVertexBuffer;

		

		std::shared_ptr<RenderTexture> myFullSizeTextureTarget;
		std::shared_ptr<RenderTexture> myFullSizeTextureSource;
		void Interpolate();
	};
}

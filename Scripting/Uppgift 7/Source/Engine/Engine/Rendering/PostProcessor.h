#pragma once
#include "..\Sprite\SpriteVertex.h"
#include "..\Texture\Texture.h"

namespace SB
{

	struct MotionBlurConstantData
	{
		float blurMultiplier;
		Vector3f padding;
	};

	struct SpriteVertex;

	template <typename TVertexBufferType>
	class VertexBuffer;

	template <typename T>
	class ConstantBuffer;

	class WorldRenderTexture;

	struct BloomBufferData
	{
		BloomBufferData(const float aBloomAmount,const float aAllowBloomModification, const float aXCameraPos, const float aYCameraPos)
		{
			myBloomAmount = aBloomAmount;
			myAllowBloomModification = aAllowBloomModification;
			myXCameraPos = aXCameraPos;
			myYCameraPos = aYCameraPos;
		}
		BloomBufferData()
		{
			myBloomAmount = 1.0f;
			myAllowBloomModification = 0.f;
			myXCameraPos = 0.f;
			myYCameraPos = 0.f;
		}
		float myBloomAmount;
		float myAllowBloomModification;
		float myXCameraPos;
		float myYCameraPos;
	};

	enum class eEffectBundles
	{
		eBloom = 1 << 0,
		eHDR = 1 << 1,
		eMotionBlur = 1 << 2,
		eNone = 1 << 3
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

	class PostProcessor
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

		PostProcessor(unsigned int aWidth, unsigned int aHeight);
		~PostProcessor();

		void DoFullscreenEffects(const std::shared_ptr<WorldRenderTexture> & aWorldTexture, unsigned int aEffectsToRun, unsigned int aStepsToShow);
		
		void DoEffectNoSwap(eFullscreenEffects aEffect, const std::shared_ptr<RenderTexture> & aTargetTexture, const std::shared_ptr<Texture> & aResourceTexture);

		void CopyRenderTexture(const std::shared_ptr<RenderTexture> &aTarget, const std::shared_ptr<Texture> &aSource);
		void SetBloomValue(const float aBloomAmount,const float aXCameraSpacePos, const float aYCameraSpacePos) //0.0f for regular 1.0 for extreme;
		{
			myBloomAmount = 1.0f - aBloomAmount;
			myXCameraSpacePos = aXCameraSpacePos;
			myYCameraSpacePos = aYCameraSpacePos;
		}		
		void AllowBloomModification(bool aValue);
	private:
		void DoEffect(eFullscreenEffects aEffect);
		void DoEffect(const std::shared_ptr<RenderTexture> & aTarget, const std::shared_ptr<Texture> & aSourceTexture, const std::shared_ptr<Texture> & aSecondSourceTexture, eFullscreenEffects aFullscreenEffect, bool aBindSourcesFirst = true);
		void CopyInput();
		void DoHDR(bool aShowSteps);
		void Downsample(unsigned int aDestination);
		void DoBloom(bool aShowSteps);
		void DoMotionBlur();
		void DrawEffect(PostProcessor::eFullscreenEffects aEffect);

		std::shared_ptr<RenderTexture> myTargetTexture;

		std::shared_ptr<RenderTexture> myTextures[2];

		std::shared_ptr<RenderTexture> mySourceTexture;
		std::shared_ptr<RenderTexture> myInputTexture;
		std::shared_ptr<ConstantBuffer<BloomBufferData>> myBloomBufferData;
		GrowingArray<std::shared_ptr<RenderTexture>> myDownsamples;
		std::shared_ptr<RenderTexture> mySmallestBloomdownsample;

		SpriteVertex myVertices[6];
		GrowingArray<std::shared_ptr<Effect>>myEffects;

		std::unique_ptr<VertexBuffer<SpriteVertex>> myVertexBuffer;

		std::shared_ptr<ConstantBuffer<MotionBlurConstantData>> myMotionBlurData;

		std::shared_ptr<RenderTexture> myFullSizeTextureTarget;
		std::shared_ptr<RenderTexture> myFullSizeTextureSource;
		float myBloomAmount;
		float myAllowBloomModification;
		float myXCameraSpacePos;
		float myYCameraSpacePos;
		void Interpolate();
	};
}

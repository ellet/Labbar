#pragma once
#include "Engine\Buffer\VertexBuffer.h"


namespace ENGINE_NAMESPACE
{

	class FullScreenEffect;

	enum class FullScreenEffectTypes
	{
		eCopy,
		eLuminence,
		eAdd,
		eGaussianBlurHorizontal,
		eGaussianBlurVertical,
		eHDR,
		eMotionBlur,
		EnumLength
	};
	
	struct FullScreenVertex
	{
		Vector4f myPosition;
		Vector2f myUV;
	};

	class FullscreenHelper
	{
	public:
		FullscreenHelper();
		~FullscreenHelper();

		void DoEffect(const FullScreenEffectTypes aEffectType, const std::shared_ptr<Texture> & aTextureToCopyFrom);
		void DoEffect(const FullScreenEffectTypes aEffectType, const std::shared_ptr<Texture> & aTextureToCopyFrom, const std::shared_ptr<Texture> & aSecondToCopyFrom);

	private:
		unsigned short GetEffectSlot(const FullScreenEffectTypes aEffectType) { return static_cast<unsigned short>(aEffectType); }

		GrowingArray<FullScreenEffect*> myEffects;

		std::unique_ptr<VertexBuffer<FullScreenVertex>> myVertexBuffer;
		GrowingArray<FullScreenVertex> myVertices;
	};
	
}
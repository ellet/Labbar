#pragma once
#include "Engine\Effect\Effect.h"
#include "VisualEffectStructs.h"

namespace SB
{
	class VisualEffect : public Effect
	{
	public:
		VisualEffect();
		~VisualEffect();

		void UpdateCBufferDataAndBind(const Time & aDeltaTime, const Time & aRunTime);
		virtual void SetEffect();
		void SetTexture(std::shared_ptr<Texture> aShaderTexture);

		void BindTexture();

	protected:

		void DisableEffect();
		VisualEffectVertex * myVertexLayout;
		std::shared_ptr<Texture> myShaderTexture;
		ConstantBuffer<ShaderResourceCBufferData> myVariousResources;
	};
}
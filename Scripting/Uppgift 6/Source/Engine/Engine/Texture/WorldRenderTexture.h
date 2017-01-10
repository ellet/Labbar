#pragma once
#include "RenderTexture.h"

struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;

namespace SB
{
	class Texture;
	class DepthBuffer;

	enum class WorldRenderTarget
	{
		eDiffuse,
		eVelocity
	};

	class WorldRenderTexture : public RenderTexture
	{
	public:
		WorldRenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer);
		~WorldRenderTexture();

		ID3D11RenderTargetView * GetView(WorldRenderTarget aTarget) const;
		const std::shared_ptr<Texture> & GetTexture(WorldRenderTarget aTarget) const;
		ModelRenderer & GetModelRenderer();

	private:
		friend class Camera;
		std::unique_ptr<ModelRenderer> myModelRenderer;
		void RenderBuffer();
	};
}

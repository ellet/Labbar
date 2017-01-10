#pragma once

struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;

namespace SB
{
	class Texture;
	class DepthBuffer;

	class RenderTexture
	{
	public:
		RenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer, nullptr_t);
		RenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer, DXGI_FORMAT aFormat);
		RenderTexture(ID3D11Texture2D * aTexture, ID3D11RenderTargetView * aRenderTarget, ID3D11ShaderResourceView * aShaderResourceView, unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer);
		~RenderTexture();

		void AddRenderTexture(DXGI_FORMAT aFormat);
		void Resize(unsigned int aWidth, unsigned int aHeight);

		void Bind(int aSlot, bool aUpdateViewport = true);

		void Clear(const Vector4f & aColor);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		const std::shared_ptr<DepthBuffer> & GetDepthBuffer();
		std::shared_ptr<const DepthBuffer> GetDepthBuffer() const;

		ID3D11RenderTargetView * GetView(const unsigned short aIndex) const;
		const std::shared_ptr<Texture> & GetTexture(const unsigned short aIndex) const;

	private:
		struct RenderTextureData
		{
			std::shared_ptr<Texture> texture;
			ID3D11RenderTargetView * renderTargetView;
			DXGI_FORMAT format;
		};

		GrowingArray<RenderTextureData> myTextures;
		std::shared_ptr<DepthBuffer> myDepthBuffer;

		unsigned int myWidth;
		unsigned int myHeight;
	};
}

#pragma once

struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
enum class eRenderTargets
{
	eIntermediate,
	eVelocity
};
namespace ENGINE_NAMESPACE
{
	class Texture;
	class DepthBuffer;

	class MultiRenderTexture
	{
	public:
		MultiRenderTexture(unsigned int aWidth, unsigned int aHeight, bool aGenerateDepthBuffer);
		~MultiRenderTexture();
		void AddTexture(DXGI_FORMAT aFormat, eRenderTargets aRenderTarget);

		void Bind();

		void Clear(const Vector4f & aColor);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		
		const std::shared_ptr<DepthBuffer> & GetDepthBuffer();
		std::shared_ptr<const DepthBuffer> GetDepthBuffer() const;

		const std::shared_ptr<RenderTexture> &GetRenderTexture(eRenderTargets aTarget)const;
		std::shared_ptr<RenderTexture> &GetRenderTexture(eRenderTargets aTarget);
	private:
		GrowingArray<std::shared_ptr<RenderTexture>>	myRenderTargetViews;
		std::shared_ptr<DepthBuffer> myDepthBuffer;


		unsigned int myWidth;
		unsigned int myHeight;
	};
}

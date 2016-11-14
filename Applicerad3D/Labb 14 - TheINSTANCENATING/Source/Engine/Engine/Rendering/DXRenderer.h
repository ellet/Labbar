#pragma once

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11SamplerState;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;
struct ID3D11BlendState;
struct ID3D11DepthStencilView;
struct ID3D11Debug;

namespace ENGINE_NAMESPACE
{
	class RenderTexture;
	class DepthBuffer;
	class TextureDebugger;
	class ModelRenderer;
	class SpriteRenderer;
	class FullscreenHelper;
	class MultiRenderTexture;
	enum class eEffectBundles;

	class DXRenderer
	{
	public:
		DXRenderer();
		~DXRenderer();

		void Initialize(void *aOutputTarget, int aWidth, int aHeight, bool aFullscreen);

		void ClearFrame();
		void Present();

		void Resize(int aNewWidth, int aNewHeight);

		ID3D11Device * GetDevice();
		ID3D11DeviceContext * GetContext();

		const std::shared_ptr<RenderTexture> & GetBackBuffer();

		TextureDebugger & GetTextureDebugger();
		ModelRenderer & GetModelRenderer();
		SpriteRenderer & GetSpriteRenderer();

		void SetViewport(const Vector2f& aTopLeft, const Vector2f& aSize);
		void ResetViewport();

		void StoreRenderTargetResolution(const Vector2f & aRenderTargetResolution);
		const Vector2f & GetRenderTargetResolution() const;

		void EnableDepth();
		void DisableDepthWrite();
		void DisableDepthWriteRead();

		void EnableWireframe();
		void DisableWireframe();

		void RenderToBackBuffer();
		void DoFullscreenEffects();

		void ToggleBloom();
		bool HasBloom();

	private:
		void CreateBuffers(int aWidth, int aHeight);

		IDXGISwapChain * mySwapchain;
		ID3D11Device * myDevice;
		ID3D11DeviceContext * myDeviceContext;
		ID3D11SamplerState * mySamplerState;
		ID3D11RasterizerState * myRasterState;
		ID3D11RasterizerState * myRasterStateWireframe;
		ID3D11BlendState * myAlphaBlendingState;
		ID3D11DepthStencilState* myDepthStencilState;
		ID3D11DepthStencilState* myDepthStencilStateDisableWrite;
		ID3D11DepthStencilState* myDepthStencilStateDisableWriteRead;
		

		std::shared_ptr<RenderTexture> myBackbuffer;
		std::shared_ptr<MultiRenderTexture> myMultiRenderTarget;
		std::unique_ptr<FullscreenHelper> myFullscreenHelper;

		std::unique_ptr<TextureDebugger> myTextureDebugger;
		std::unique_ptr<ModelRenderer> myModelRenderer;
		std::unique_ptr<SpriteRenderer> mySpriteRenderer;

		Vector2f myCurrentRenderTargetResolution;
		ID3D11Debug * myD3dDebug;
		bool myShouldDoBloom;
	};

	inline ID3D11Device * DXRenderer::GetDevice()
	{
		return myDevice;
	}

	inline ID3D11DeviceContext * DXRenderer::GetContext()
	{
		return myDeviceContext;
	}
}
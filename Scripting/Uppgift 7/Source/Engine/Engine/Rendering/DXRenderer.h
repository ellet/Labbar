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
struct ID3DUserDefinedAnnotation;

namespace SB
{
	class RenderTexture;
	class DepthBuffer;
	class TextureDebugger;
	class PostProcessor;
	class FullscreenHelper;
	struct CameraConstantBuffer;
	enum class eEffectBundles;
	class WorldRenderTexture;
	
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
		ID3DUserDefinedAnnotation * GetAnnotationWriter() const;

		const std::shared_ptr<RenderTexture> & GetBackBuffer();
		TextureDebugger & GetTextureDebugger();
		PostProcessor & GetPostProcessor();

		void SetViewport(const Vector2f& aTopLeft, const Vector2f& aSize);
		void ResetViewport();

		void StoreRenderTargetResolution(const Vector2f & aRenderTargetResolution);
		const Vector2f & GetRenderTargetResolution() const;

		void EnableDepth();
		void DisableDepthWrite();
		void DisableDepthWriteRead();

		void EnableWireframe();
		void DisableWireframe();

		void DisableBackfaceCulling();
		void EnableBackfaceCulling();

		void EnableAdditiveBlendState();
		void DisableAdditiveBlendState();

		void DoFullscreenEffects(const std::shared_ptr<WorldRenderTexture> & aWorldTexture);

		void SetFullscreen(const bool aTrueFalse);
		bool IsFullscreen() const;
		
		void SetCamera(const CameraConstantBuffer & aCameraData);
		private:
		void CreateBuffers(int aWidth, int aHeight);

		IDXGISwapChain * mySwapchain;
		ID3D11Device * myDevice;
		ID3D11DeviceContext * myDeviceContext;
		ID3D11SamplerState * mySamplerState;
		ID3D11RasterizerState * myRasterState;
		ID3D11RasterizerState * myBackfaceRasterState;
		ID3D11RasterizerState * myRasterStateWireframe;
		ID3D11BlendState * myAlphaBlendingState;
		ID3D11BlendState * myAdditiveBlendingState;
		ID3D11DepthStencilState* myDepthStencilState;
		ID3D11DepthStencilState* myDepthStencilStateDisableWrite;
		ID3D11DepthStencilState* myDepthStencilStateDisableWriteRead;
		ID3DUserDefinedAnnotation * myAnnotationWriter;
		ID3D11Debug * myD3dDebug;

		std::shared_ptr<RenderTexture> myBackbuffer;
		std::unique_ptr<PostProcessor> myPostProcessor;

		std::unique_ptr<TextureDebugger> myTextureDebugger;

		std::unique_ptr<ConstantBuffer<CameraConstantBuffer>> myCameraConstantBuffer;

		Vector2f myCurrentRenderTargetResolution;
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

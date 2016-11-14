#include "stdafx.h"
#include "Engine\Rendering\DXRenderer.h"
#include <d3d11.h>
#include <dxgi.h>
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Texture\MultiRenderTexture.h"
#include "Engine\Texture\TextureDebugger.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Rendering\SpriteRenderer.h"
#include "FullscreenHelper.h"

namespace ENGINE_NAMESPACE
{
	DXRenderer::DXRenderer()
	{
		mySwapchain = nullptr;
		myDevice = nullptr;
		myDeviceContext = nullptr;
		mySamplerState = nullptr;
		myRasterState = nullptr;
		myAlphaBlendingState = nullptr;
		myDepthStencilState = nullptr;
		myD3dDebug = nullptr;
		myShouldDoBloom = true;
	}

	DXRenderer::~DXRenderer()
	{
		SAFE_RELEASE(mySwapchain);
		SAFE_RELEASE(myDevice);
		SAFE_RELEASE(myDeviceContext);
		SAFE_RELEASE(mySamplerState);
		SAFE_RELEASE(myRasterState);
		SAFE_RELEASE(myAlphaBlendingState);
		SAFE_RELEASE(myDepthStencilState);
		if (myD3dDebug != nullptr)
		{
			myD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		}
		SAFE_RELEASE(myD3dDebug);
	}

	void DXRenderer::Initialize(void *aOutputTarget, int aWidth, int aHeight, bool aFullscreen)
	{
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		// If the project is in a debug build, enable debugging via SDK Layers with this flag.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.Flags = 0;
		swapChainDesc.BufferDesc.Width = aWidth;
		swapChainDesc.BufferDesc.Height = aHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.BufferCount = 2;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		swapChainDesc.OutputWindow = reinterpret_cast<HWND>(aOutputTarget);
		swapChainDesc.Windowed = !aFullscreen;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		D3D_FEATURE_LEVEL featureLevel;
		featureLevel = D3D_FEATURE_LEVEL_11_0;

		CheckDXError(
			D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags,
				&featureLevel, 1,
				D3D11_SDK_VERSION,
				&swapChainDesc,
				&mySwapchain,
				&myDevice,
				nullptr,
				&myDeviceContext)
		);

		UINT levels;
		myDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &levels);

		myD3dDebug = nullptr;
#ifdef _DEBUG
		if (SUCCEEDED(myDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&myD3dDebug)))
		{
			ID3D11InfoQueue *d3dInfoQueue = nullptr;
			if (SUCCEEDED(myD3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
			{
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, false);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, false);

				D3D11_MESSAGE_ID hide[] =
				{
					D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS
				};

				D3D11_INFO_QUEUE_FILTER filter;
				memset(&filter, 0, sizeof(filter));
				filter.DenyList.NumIDs = _countof(hide);
				filter.DenyList.pIDList = hide;
				d3dInfoQueue->AddStorageFilterEntries(&filter);
			}
			SAFE_RELEASE(d3dInfoQueue);
		}
#endif

		CreateBuffers(aWidth, aHeight);


		D3D11_RASTERIZER_DESC rasterDesc;
		// Setup the raster description which will determine how and what polygons will be drawn.
		rasterDesc.AntialiasedLineEnable = false;

		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = true;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		// CreateInputLayout the rasterizer state from the description we just filled out.
		CheckDXError(
			myDevice->CreateRasterizerState(&rasterDesc, &myRasterState)
		);

		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		CheckDXError(
			myDevice->CreateRasterizerState(&rasterDesc, &myRasterStateWireframe)
		);

		myDeviceContext->RSSetState(myRasterState);

		D3D11_BLEND_DESC blendStateDescription;
		// Clear the blend state description.
		ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));
		// CreateInputLayout an alpha enabled blend state description.
		blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
		blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA; // D3D11_BLEND_ZERO;
		blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		/*blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;*/

		CheckDXError(
			myDevice->CreateBlendState(&blendStateDescription, &myAlphaBlendingState)
		);

		float blendFactor[4];

		// Setup the blend factor.
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;

		// Turn on the alpha blending.
		myDeviceContext->OMSetBlendState(myAlphaBlendingState, blendFactor, 0xffffffff);

		// Create sampler
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		CheckDXError(
			myDevice->CreateSamplerState(&samplerDesc, &mySamplerState)
		);

		myDeviceContext->PSSetSamplers(0, 1, &mySamplerState);

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

		// Initialize the description of the stencil state.
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		// Set up the description of the stencil state.
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		CheckDXError(
			myDevice->CreateDepthStencilState(&depthStencilDesc, &myDepthStencilState)
		);

		myDeviceContext->OMSetDepthStencilState(myDepthStencilState, 0);

		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		CheckDXError(
			myDevice->CreateDepthStencilState(&depthStencilDesc, &myDepthStencilStateDisableWrite)
		);

		depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;

		CheckDXError(
			myDevice->CreateDepthStencilState(&depthStencilDesc, &myDepthStencilStateDisableWriteRead)
		);
		myMultiRenderTarget = std::make_shared<MultiRenderTexture>(aWidth, aHeight, true);
		myMultiRenderTarget->AddTexture(DXGI_FORMAT_R16G16B16A16_FLOAT, eRenderTargets::eIntermediate);
		myMultiRenderTarget->AddTexture(DXGI_FORMAT_R16G16_FLOAT, eRenderTargets::eVelocity);

		myFullscreenHelper = std::make_unique<FullscreenHelper>(aWidth, aHeight);

		myTextureDebugger = std::make_unique<TextureDebugger>(static_cast<unsigned>(aWidth), static_cast<unsigned>(aHeight));
		myModelRenderer = std::make_unique<ModelRenderer>();
		//myModelRenderer->SetEffect(std::make_shared<Effect> ());
		mySpriteRenderer = std::make_unique<SpriteRenderer>();

		
	}

	void DXRenderer::ClearFrame()
	{
		myBackbuffer->Bind(0);
		myBackbuffer->Clear(Vector4f(1.f, 1.f, 1.f, 1.f)); // Vector4f(100.f / 255.f, 149.f / 255.f, 237.f / 255.f, 1.f));

		myMultiRenderTarget->Bind();
		myMultiRenderTarget->Clear(Vector4f(0.f, 0.f, 0.f, 1.f));
	}

	void DXRenderer::Present()
	{
		myModelRenderer->RenderBuffer();
		mySpriteRenderer->RenderBuffer();

		myTextureDebugger->Render();
	
		RenderToBackBuffer();

		Engine::GetDebugger().RenderFrame();

		mySwapchain->Present(0, 0);

		
	}

	void DXRenderer::Resize(int aNewWidth, int aNewHeight)
	{
		ID3D11RenderTargetView * renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
		myDeviceContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, renderTargets, nullptr);
		myBackbuffer = nullptr;

		CheckDXError(
			mySwapchain->ResizeBuffers(0, aNewWidth, aNewHeight, DXGI_FORMAT_UNKNOWN, 0);
		);

		CreateBuffers(aNewWidth, aNewHeight);

	}

	const std::shared_ptr<RenderTexture> & DXRenderer::GetBackBuffer()
	{
		return myBackbuffer;
	}

	TextureDebugger& DXRenderer::GetTextureDebugger()
	{
		return *myTextureDebugger;
	}

	ModelRenderer & DXRenderer::GetModelRenderer()
	{
		return *myModelRenderer;
	}

	SpriteRenderer & DXRenderer::GetSpriteRenderer()
	{
		return *mySpriteRenderer;
	}

	void DXRenderer::CreateBuffers(int aWidth, int aHeight)
	{
		ID3D11Texture2D *texture = nullptr;
		CheckDXError(
			mySwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture)
		);

		ID3D11RenderTargetView * backbuffer;
		CheckDXError(
			myDevice->CreateRenderTargetView(texture, NULL, &backbuffer)
		);

		ID3D11ShaderResourceView * shaderResourceView;
		CheckDXError(
			myDevice->CreateShaderResourceView(texture, nullptr, &shaderResourceView);
		);

		SetD3DObjectName(texture, "Backbuffer texture");
		SetD3DObjectName(backbuffer, "Backbuffer rendertargetview");
		SetD3DObjectName(shaderResourceView, "Backbuffer shader resource view");

		myBackbuffer = std::make_shared<RenderTexture>(texture, backbuffer, shaderResourceView, aWidth, aHeight, false);

		myBackbuffer->Bind(0);

		SAFE_RELEASE(texture);
		SAFE_RELEASE(backbuffer);
		SAFE_RELEASE(shaderResourceView);
	}

	void DXRenderer::SetViewport(const Vector2f & aTopLeft, const Vector2f & aSize)
	{
		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = aTopLeft.x;
		viewport.TopLeftY = aTopLeft.y;
		viewport.Width = aSize.x;
		viewport.Height = aSize.y;
		viewport.MinDepth = 0.f;
		viewport.MaxDepth = 1.f;

		myDeviceContext->RSSetViewports(1, &viewport);
	}

	void DXRenderer::ResetViewport()
	{
		SetViewport(Vector2f::Zero, Vector2f(static_cast<float>(myBackbuffer->GetWidth()), static_cast<float>(myBackbuffer->GetHeight())));
	}

	void DXRenderer::StoreRenderTargetResolution(const Vector2f & aRenderTargetResolution)
	{
		myCurrentRenderTargetResolution = aRenderTargetResolution;
	}

	const Vector2f & DXRenderer::GetRenderTargetResolution() const
	{
		return myCurrentRenderTargetResolution;
	}

	void DXRenderer::EnableDepth()
	{
		myDeviceContext->OMSetDepthStencilState(myDepthStencilState, 0);
	}

	void DXRenderer::DisableDepthWrite()
	{
		myDeviceContext->OMSetDepthStencilState(myDepthStencilStateDisableWrite, 0);
	}

	void DXRenderer::DisableDepthWriteRead()
	{
		myDeviceContext->OMSetDepthStencilState(myDepthStencilStateDisableWriteRead, 0);
	}

	void DXRenderer::EnableWireframe()
	{
		myDeviceContext->RSSetState(myRasterStateWireframe);
	}

	void DXRenderer::DisableWireframe()
	{
		myDeviceContext->RSSetState(myRasterState);
	}

	void DXRenderer::RenderToBackBuffer()
	{
		myFullscreenHelper->CopyRenderTexture(myBackbuffer, myMultiRenderTarget->GetRenderTexture(eRenderTargets::eIntermediate));
		myMultiRenderTarget->GetRenderTexture(eRenderTargets::eIntermediate)->GetTexture()->UnbindFromPS(0);

	}

	void DXRenderer::DoFullscreenEffects()
	{
		myModelRenderer->RenderBuffer();
		mySpriteRenderer->RenderBuffer();

		DisableDepthWrite();
		if (myShouldDoBloom == true)
		{
			myFullscreenHelper->DoFullscreenEffects(myMultiRenderTarget, eEffectBundles::eBloom | eEffectBundles::eHDR, 0);
		}
		else
		{
			myFullscreenHelper->DoFullscreenEffects(myMultiRenderTarget, static_cast<unsigned int>(eEffectBundles::eHDR), 0);
		}
		EnableDepth();
		myMultiRenderTarget->Bind();
	}

	void DXRenderer::ToggleBloom()
	{
		myShouldDoBloom = !myShouldDoBloom;
	}


	bool DXRenderer::HasBloom()
	{
		return myShouldDoBloom;
	}

}

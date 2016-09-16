#include "stdafx.h"
#include "HUGDXFramework.h"


CHUGDXFramework::CHUGDXFramework()
{
	myAspectRatio.x = 16.f;
	myAspectRatio.y = 9.f;

	mySwapChain = nullptr;
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myRenderTargetView = nullptr;
	myDepthStencilBuffer = nullptr;
	myDepthStencilState = nullptr;
	myDepthStencilView = nullptr;
	myRasterState = nullptr;
}


CHUGDXFramework::~CHUGDXFramework()
{
	mySwapChain->Release();
	myDevice->Release();
	myDeviceContext->Release();
	myRenderTargetView->Release();

	mySwapChain = nullptr;
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myRenderTargetView = nullptr;

	ReleaseBuffers();
}

void CHUGDXFramework::CleanFrame()
{
	CU::Vector4f tempColor;

	// Setup the color to clear the buffer to.
	tempColor.r = 0.f;
	tempColor.g = 1.f;
	tempColor.b = 1.f;
	tempColor.a = 1.f;
	

	// Clear the back buffer.
	myDeviceContext->ClearRenderTargetView(myRenderTargetView, &tempColor.r);

	// Clear the depth buffer.
	myDeviceContext->ClearDepthStencilView(myDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void CHUGDXFramework::Present()
{
	mySwapChain->Present(0, 0);
}

void CHUGDXFramework::Init(void* aHWND, const CU::Vector2ui & aScreenWidthHeight)
{
	HRESULT tempResult = S_OK;


#pragma region SwapChainSetup
	DXGI_SWAP_CHAIN_DESC tempSwapChainDescription;

	// Initialize the swap chain description.
	ZeroMemory(&tempSwapChainDescription, sizeof(tempSwapChainDescription));

	// Set to a single back buffer.
	tempSwapChainDescription.BufferCount = 1;

	// Set the width and height of the back buffer.
	tempSwapChainDescription.BufferDesc.Width = aScreenWidthHeight.x;
	tempSwapChainDescription.BufferDesc.Height = aScreenWidthHeight.y;

	// Set regular 32-bit surface for the back buffer.
	tempSwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


	// Set the refresh rate of the back buffer.
	tempSwapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
	tempSwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;


	// Set the usage of the back buffer.
	tempSwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	tempSwapChainDescription.OutputWindow = *static_cast<HWND*>(aHWND);

	// Turn multisampling off.
	tempSwapChainDescription.SampleDesc.Count = 1;
	tempSwapChainDescription.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	tempSwapChainDescription.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	tempSwapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tempSwapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	tempSwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	tempSwapChainDescription.Flags = 0;
#pragma endregion

	// Set the feature level to DirectX 11.
	D3D_FEATURE_LEVEL tempFeatureLevel = D3D_FEATURE_LEVEL_11_0; // TESTSHIT^^ 1 on the end!!

	
	// Create the swap chain, Direct3D device, and Direct3D device context.
	tempResult = D3D11CreateDeviceAndSwapChain(  
		NULL,							//IDXGIAdapter
		D3D_DRIVER_TYPE_HARDWARE,		//D3D_DRIVER_TYPE
		NULL,							//HMODULE
		0,								//UINT - Flags
		&tempFeatureLevel,				//const D3D_FEATURE_LEVEL
		1,								//UINT - FeatureLevels
		D3D11_SDK_VERSION,				//UINT - SDKVersion
		&tempSwapChainDescription,		//const DXGI_SWAP_CHAIN_DESC
		&mySwapChain,					//IDXGISwapChain
		&myDevice,						//ID3D11Device
		NULL,							//D3D_Feature_Level
		&myDeviceContext				//ID3D11DeviceContext
		);

	DL_ASSERT(tempResult == S_OK, "Failed to create devices and/or swapchain");

	CreateBuffers(aScreenWidthHeight);
	CreateViewPort(aScreenWidthHeight);
}

void CHUGDXFramework::UpdateViewportSize(const CU::Vector2ui aNewSize)
{
	if (myDeviceContext != nullptr)
	{
		HRESULT tempResult = S_OK;

		myDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
		myRenderTargetView->Release();
		ReleaseBuffers();

		DXGI_SWAP_CHAIN_DESC tempSwapchainDesc;
		mySwapChain->GetDesc(&tempSwapchainDesc);
		tempResult = mySwapChain->ResizeBuffers(tempSwapchainDesc.BufferCount, aNewSize.x, aNewSize.y, tempSwapchainDesc.BufferDesc.Format, tempSwapchainDesc.Flags);
		DL_ASSERT(tempResult == S_OK, "Failed to resize window - swapchain buffer");

		CreateBuffers(aNewSize);
		CreateViewPort(aNewSize);
	}
}

ID3D11DeviceContext & CHUGDXFramework::GetDeviceContext()
{
	return *myDeviceContext;
}

ID3D11Device & CHUGDXFramework::GetDevice()
{
	return *myDevice;
}

void CHUGDXFramework::CreateViewPort(const CU::Vector2ui & aScreenWidthHeight)
{
	/*
		kolla om f�nster storlek �r samma som target resolution aspect ratio

		ANNARS

		LETTERBOXA!!
		ta f�nster resolution och anpassa till aspect ration
	*/

	// Setup the viewport for rendering.
	D3D11_VIEWPORT tempViewport;
	tempViewport.Width = static_cast<float>(aScreenWidthHeight.x);
	tempViewport.Height = static_cast<float>(aScreenWidthHeight.y);
	tempViewport.MinDepth = 0.0f;
	tempViewport.MaxDepth = 1.0f;
	tempViewport.TopLeftX = 0;
	tempViewport.TopLeftY = 0;

	// Create the viewport.
	myDeviceContext->RSSetViewports(1, &tempViewport);
}

void CHUGDXFramework::CreateBuffers(const CU::Vector2ui & aScreenWidthHeight)
{
	HRESULT tempResult = S_OK;

	ID3D11Texture2D* tempBackBufferPtr;

	// Get the pointer to the back buffer.
	tempResult = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tempBackBufferPtr);

	DL_ASSERT(tempResult == S_OK, "Failed to get backbuffer");

	// Create the render target view with the back buffer pointer.
	tempResult = myDevice->CreateRenderTargetView(tempBackBufferPtr, NULL, &myRenderTargetView);

	DL_ASSERT(tempResult == S_OK, "Failed to create rendertarget view");

	// Release pointer to the back buffer as we no longer need it.
	tempBackBufferPtr->Release();
	tempBackBufferPtr = nullptr;

	// Initialize the description of the depth buffer.
	D3D11_TEXTURE2D_DESC tempDepthBufferDescription;
	ZeroMemory(&tempDepthBufferDescription, sizeof(tempDepthBufferDescription));

	// Set up the description of the depth buffer.
	tempDepthBufferDescription.Width = aScreenWidthHeight.x;
	tempDepthBufferDescription.Height = aScreenWidthHeight.y;
	tempDepthBufferDescription.MipLevels = 1;
	tempDepthBufferDescription.ArraySize = 1;
	tempDepthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tempDepthBufferDescription.SampleDesc.Count = 1;
	tempDepthBufferDescription.SampleDesc.Quality = 0;
	tempDepthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	tempDepthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tempDepthBufferDescription.CPUAccessFlags = 0;
	tempDepthBufferDescription.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	tempResult = myDevice->CreateTexture2D(&tempDepthBufferDescription, NULL, &myDepthStencilBuffer);

	DL_ASSERT(tempResult == S_OK, "Failed to create depth buffer texture");

	// Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC tempDepthStencilDescription;
	ZeroMemory(&tempDepthStencilDescription, sizeof(tempDepthStencilDescription));

	// Set up the description of the stencil state.
	tempDepthStencilDescription.DepthEnable = true;
	tempDepthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tempDepthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;

	tempDepthStencilDescription.StencilEnable = true;
	tempDepthStencilDescription.StencilReadMask = 0xFF;
	tempDepthStencilDescription.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	tempDepthStencilDescription.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	tempDepthStencilDescription.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	tempDepthStencilDescription.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	tempDepthStencilDescription.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	tempDepthStencilDescription.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	tempDepthStencilDescription.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	tempDepthStencilDescription.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	tempDepthStencilDescription.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	tempResult = myDevice->CreateDepthStencilState(&tempDepthStencilDescription, &myDepthStencilState);

	DL_ASSERT(tempResult == S_OK, "Failed to create depth stencil state!");

	// Set the depth stencil state.
	myDeviceContext->OMSetDepthStencilState(myDepthStencilState, 1);

	// Initialize the depth stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC tempDepthStencilViewDescription;
	ZeroMemory(&tempDepthStencilViewDescription, sizeof(tempDepthStencilViewDescription));

	// Set up the depth stencil view description.
	tempDepthStencilViewDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tempDepthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	tempDepthStencilViewDescription.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	tempResult = myDevice->CreateDepthStencilView(myDepthStencilBuffer, &tempDepthStencilViewDescription, &myDepthStencilView);
	DL_ASSERT(tempResult == S_OK, "Failed to create depth stencil view!");

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	myDeviceContext->OMSetRenderTargets(1, &myRenderTargetView, myDepthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	D3D11_RASTERIZER_DESC tempRasterDescription;
	tempRasterDescription.AntialiasedLineEnable = false;
	tempRasterDescription.CullMode = D3D11_CULL_BACK;
	tempRasterDescription.DepthBias = 0;
	tempRasterDescription.DepthBiasClamp = 0.0f;
	tempRasterDescription.DepthClipEnable = true;
	tempRasterDescription.FillMode = D3D11_FILL_SOLID;
	tempRasterDescription.FrontCounterClockwise = false;
	tempRasterDescription.MultisampleEnable = false;
	tempRasterDescription.ScissorEnable = false;
	tempRasterDescription.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	tempResult = myDevice->CreateRasterizerState(&tempRasterDescription, &myRasterState);
	DL_ASSERT(tempResult == S_OK, "Failed to create rasterizer state!");

	// Now set the rasterizer state.
	myDeviceContext->RSSetState(myRasterState);

}

void CHUGDXFramework::ReleaseBuffers()
{
	myDepthStencilBuffer->Release();
	myDepthStencilState->Release();
	myDepthStencilView->Release();
	myRasterState->Release();

	myDepthStencilBuffer = nullptr;
	myDepthStencilState = nullptr;
	myDepthStencilView = nullptr;
	myRasterState = nullptr;
}
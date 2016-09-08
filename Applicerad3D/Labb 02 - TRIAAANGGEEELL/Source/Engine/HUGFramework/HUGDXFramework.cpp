#include "stdafx.h"
#include "HUGDXFramework.h"


CHUGDXFramework::CHUGDXFramework()
{
	mySwapChain = nullptr;
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myRenderTargetView = nullptr;
}


CHUGDXFramework::~CHUGDXFramework()
{
}

void CHUGDXFramework::Init(void* aHWND, const CU::Vector2ui & aScreenWidthHeight)
{
	HRESULT tempResult = S_OK;


#pragma region SwapChainSetup
	DXGI_SWAP_CHAIN_DESC tempSwapChainDescription; // QUE?^^ Swith to DXGI_SWAP_CHAIN_DESC1?

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
	tempSwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //QUE?^^ backbuffer?

	// Set the handle for the window to render to.
	tempSwapChainDescription.OutputWindow = static_cast<HWND>(aHWND); //QUE?^^ kasta till pekare och avreferara

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

	
	//TODO^^ creata rendertargetview med backbuffer

	//TODO^^ releasa backbuffer

	//TODO^^ binda targetview och depth stencil till output render pipeine

	//TODO^^ setup viewport
}

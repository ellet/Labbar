#pragma once
/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
//using namespace DirectX;



class CHUGDXFramework
{
public:
	CHUGDXFramework();
	~CHUGDXFramework();

	void CleanFrame();
	void Present();

	void Init(void* aHWND, const CU::Vector2ui & aScreenWidthHeight);

	ID3D11DeviceContext & GetDeviceContext();
	ID3D11Device & GetDevice();

private:
	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
	ID3D11RenderTargetView* myRenderTargetView;
	ID3D11Texture2D* myDepthStencilBuffer;
	ID3D11DepthStencilState* myDepthStencilState;
	ID3D11DepthStencilView* myDepthStencilView;
	ID3D11RasterizerState* myRasterState;
};


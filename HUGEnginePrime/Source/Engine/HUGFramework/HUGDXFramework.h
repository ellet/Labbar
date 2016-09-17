#pragma once
/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>


class CHUGDXFramework
{
public:
	CHUGDXFramework();
	~CHUGDXFramework();

	void CleanFrame();
	void Present();

	void Init(void* aHWND, const CU::Vector2ui & aScreenWidthHeight);

	void UpdateViewportSize(const CU::Vector2ui aNewSize);

	ID3D11DeviceContext & GetDeviceContext();
	ID3D11Device & GetDevice();

private:
	void CreateViewPort(const CU::Vector2ui & aScreenWidthHeight);
	void CreateBuffers(const CU::Vector2ui & aScreenWidthHeight);
	void ReleaseBuffers();

	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
	ID3D11RenderTargetView* myRenderTargetView;
	ID3D11Texture2D* myDepthStencilBuffer;
	ID3D11DepthStencilState* myDepthStencilState;
	ID3D11DepthStencilView* myDepthStencilView;
	ID3D11RasterizerState* myRasterState;


	CU::Vector2f myAspectRatio;
};


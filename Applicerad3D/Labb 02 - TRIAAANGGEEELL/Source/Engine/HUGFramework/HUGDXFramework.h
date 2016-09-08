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

	void Init(void* aHWND, const CU::Vector2ui & aScreenWidthHeight);



private:
	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
	ID3D11RenderTargetView* myRenderTargetView;


	//maybe need these? // TODO:: remove this
	/*ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;*/
};


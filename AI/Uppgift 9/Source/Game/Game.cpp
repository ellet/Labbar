#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"
#include "imgui.h"

#include <tga2d/error/error_manager.h>
#include <Windowsx.h>
#include "ImGui/imgui_impl_dx11.h"
#include "tga2d/windows/windows_window.h"
#include "tga2d/d3d/direct_3d.h"
#include "Rendering/BDTextRenderer.h"

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")
#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG

SB::GrowingArray<InputCallback *> CGame::ourInputCallbacks;

const unsigned short windowWidth = 1536;
const unsigned short windowHeight = 1080;

CGame::CGame()
{
	BDRenderer::Create();
	BDTextRenderer::Create();
}


CGame::~CGame()
{
	BDRenderer::Destroy();
	BDTextRenderer::Destroy();
}


bool CGame::Init(const std::wstring& aVersion, HWND aHWND)
{
	


    Tga2D::SEngineCreateParameters createParameters;
	//createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps | Tga2D::eDebugFeature_Mem | Tga2D::eDebugFeature_Filewatcher | Tga2D::eDebugFeature_Cpu | Tga2D::eDebugFeature_Drawcalls | Tga2D::eDebugFeature_OptimiceWarnings;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this, _1);
	createParameters.myWinProcCallback = std::bind(&CGame::WinProc, this, _1, _2, _3, _4);
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = windowWidth;
	createParameters.myTargetHeight = windowHeight;
	createParameters.myWindowSetting = Tga2D::EWindowSetting_Overlapped;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set(0.0f / 255.0f, 143.0f / 255.0f, 212.0f / 255.0f, 1.0f );
	createParameters.myStartInFullScreen = false;

	if (aHWND != nullptr)
	{
		createParameters.myHwnd = new HWND(aHWND);
	}
	
	std::wstring architecture = L"32 Bit";
#ifdef _AMD64_
	architecture = L"64 Bit";
#endif
	std::wstring appname = L"TGA 2D RELEASE [" + aVersion + L"] " + architecture;
#ifdef _DEBUG
	appname = L"TGA 2D DEBUG  [" + aVersion + L"] " + architecture;
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    Tga2D::CEngine::CreateInstance( createParameters );

    if( !Tga2D::CEngine::GetInstance()->Start() )
    {
        ERROR_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
		return false;
    }

	return true;
}


void CGame::RegisterInputCallback(InputCallback & aCallback)
{
	ourInputCallbacks.Add(&aCallback);
}

void CGame::UnregisterInputCallback(InputCallback & aCallback)
{
	ourInputCallbacks.RemoveCyclic(&aCallback);
}


SB::KeyboardKey CGame::ConvertVirtualKey(const WPARAM& aVirtualKey)
{
	switch (aVirtualKey)
	{
	case 0x30:
		return SB::KeyboardKey::eNum0;
	case 0x31:
		return SB::KeyboardKey::eNum1;
	case 0x32:
		return SB::KeyboardKey::eNum2;
	case 0x33:
		return SB::KeyboardKey::eNum3;
	case 0x34:
		return SB::KeyboardKey::eNum4;
	case 0x35:
		return SB::KeyboardKey::eNum5;
	case 0x36:
		return SB::KeyboardKey::eNum6;
	case 0x37:
		return SB::KeyboardKey::eNum7;
	case 0x38:
		return SB::KeyboardKey::eNum8;
	case 0x39:
		return SB::KeyboardKey::eNum9;
	case 0x41:
		return SB::KeyboardKey::eA;
	case 0x42:
		return SB::KeyboardKey::eB;
	case 0x43:
		return SB::KeyboardKey::eC;
	case 0x44:
		return SB::KeyboardKey::eD;
	case 0x45:
		return SB::KeyboardKey::eE;
	case 0x46:
		return SB::KeyboardKey::eF;
	case 0x47:
		return SB::KeyboardKey::eG;
	case 0x48:
		return SB::KeyboardKey::eH;
	case 0x49:
		return SB::KeyboardKey::eI;
	case 0x4A:
		return SB::KeyboardKey::eJ;
	case 0x4B:
		return SB::KeyboardKey::eK;
	case 0x4C:
		return SB::KeyboardKey::eL;
	case 0x4D:
		return SB::KeyboardKey::eM;
	case 0x4E:
		return SB::KeyboardKey::eN;
	case 0x4F:
		return SB::KeyboardKey::eO;
	case 0x50:
		return SB::KeyboardKey::eP;
	case 0x51:
		return SB::KeyboardKey::eQ;
	case 0x52:
		return SB::KeyboardKey::eR;
	case 0x53:
		return SB::KeyboardKey::eS;
	case 0x54:
		return SB::KeyboardKey::eT;
	case 0x55:
		return SB::KeyboardKey::eU;
	case 0x56:
		return SB::KeyboardKey::eV;
	case 0x57:
		return SB::KeyboardKey::eW;
	case 0x58:
		return SB::KeyboardKey::eX;
	case 0x59:
		return SB::KeyboardKey::eY;
	case 0x5A:
		return SB::KeyboardKey::eZ;
	case 0xDC:
		return SB::KeyboardKey::eConsoleButton;
	case VK_F1:
		return SB::KeyboardKey::eF1;
	case VK_F2:
		return SB::KeyboardKey::eF2;
	case VK_F3:
		return SB::KeyboardKey::eF3;
	case VK_F4:
		return SB::KeyboardKey::eF4;
	case VK_F5:
		return SB::KeyboardKey::eF5;
	case VK_F6:
		return SB::KeyboardKey::eF6;
	case VK_F7:
		return SB::KeyboardKey::eF7;
	case VK_F8:
		return SB::KeyboardKey::eF8;
	case VK_F9:
		return SB::KeyboardKey::eF9;
	case VK_F10:
		return SB::KeyboardKey::eF10;
	case VK_F11:
		return SB::KeyboardKey::eF11;
	case VK_F12:
		return SB::KeyboardKey::eF12;
	case VK_ESCAPE:
		return SB::KeyboardKey::eEscape;
	case VK_RETURN:
		return SB::KeyboardKey::eReturn;
	case VK_SPACE:
		return SB::KeyboardKey::eSpace;
	case VK_CONTROL:
		return SB::KeyboardKey::eControl;
	case VK_SHIFT:
		return SB::KeyboardKey::eShift;
	case VK_LEFT:
		return SB::KeyboardKey::eLeft;
	case VK_RIGHT:
		return SB::KeyboardKey::eRight;
	case VK_UP:
		return SB::KeyboardKey::eUp;
	case VK_DOWN:
		return SB::KeyboardKey::eDown;
	case VK_LMENU:
		return SB::KeyboardKey::eAlt;
	default:
		return SB::KeyboardKey::eNone;
	}
}





LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplDX11_WndProcHandler(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_RBUTTONUP:
	{
		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->MouseReleased(SB::MouseKey::eRight);
		}
		return 0;
		break;
	}
	case WM_LBUTTONUP:
	{
		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->MouseReleased(SB::MouseKey::eLeft);
		}
		return 0;
		break;
	}
	case WM_LBUTTONDOWN:
	{
		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->MousePressed(SB::MouseKey::eLeft);
		}
		return 0;
		break;
	}
	case WM_RBUTTONDOWN:
	{
		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->MousePressed(SB::MouseKey::eRight);
		}
		return 0;
		break;
	}
	case WM_MOUSEMOVE:
	{
		POINT mpos;
		GetCursorPos(&mpos);

		ScreenToClient(hWnd, &mpos);
		SB::Vector2f mousePosition;
		//mousePosition.x = static_cast<float>(mpos.x);
		//mousePosition.y = static_cast<float>(mpos.y);
		mousePosition.x = static_cast<float>(GET_X_LPARAM(lParam));
		mousePosition.y = static_cast<float>(GET_Y_LPARAM(lParam));

		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->MousePositionUpdate(mousePosition);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		SB::KeyboardKey keyDown = ConvertVirtualKey(wParam);
		// Bit 0 - 15 is the repeat count
		int repeatCount = static_cast<int>(HIWORD(lParam) & KF_REPEAT);
		if (repeatCount == 0)
		{
			for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
			{
				ourInputCallbacks[iInput]->KeyPressed(keyDown);
			}
		}
		return 0;
	}
	break;


	case WM_KEYUP:
	{
		SB::KeyboardKey keyUp = ConvertVirtualKey(wParam);
		for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
		{
			ourInputCallbacks[iInput]->KeyReleased(keyUp);
		}
		return 0;
	}
	break;

		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CGame::InitCallBack()
{
	ImGui_ImplDX11_Init(Tga2D::CEngine::GetInstance()->GetWindow().GetWindowHandle(), Tga2D::CEngine::GetInstance()->GetDirect3D().GetDevice(), Tga2D::CEngine::GetInstance()->GetDirect3D().GetContext());

	//ImGuiIO& io = ImGui::GetIO();
	//io.DisplaySize.x = windowWidth;
	//io.DisplaySize.y = windowHeight;
	//io.IniFilename = "imgui.ini";
	//io.RenderDrawListsFn = nullptr;//my_render_function;  // Setup a render function, or set to NULL and call GetDrawData() after Render() to access the render data.
	//											// TODO: Fill others settings of the io structure

	//											// Load texture atlas
	//											// There is a default font so you don't need to care about choosing a font yet
	//unsigned char* pixels;
	//int width, height;
	//io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	BDTextRenderer::Init();

    myGameWorld.Init();
}


void CGame::UpdateCallBack(const float aDeltaTime)
{
	ImGui_ImplDX11_NewFrame();

	myGameWorld.Update(aDeltaTime);
	myGameWorld.Render();
	BDRenderer::Render();
	BDTextRenderer::Render();

	for (unsigned short iInput = 0; iInput < ourInputCallbacks.Size(); ++iInput)
	{
		ourInputCallbacks[iInput]->Update();
	}

	ImGui::Render();
}


void CGame::LogCallback( std::string aText )
{
}

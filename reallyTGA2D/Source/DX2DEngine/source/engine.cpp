#include "stdafx.h"

#include "engine.h"
#include "d3d/direct_3d.h"
#include "drawers/debug_drawer.h"
#include "error/error_manager.h"
#include "filewatcher/file_watcher.h"
#include "light/light_manager.h"
#include "render/renderer.h"
#include "text/text_service.h"
#include "texture/texture_manager.h"
#include "windows/windows_window.h"
#include <windows.h>


#pragma comment( lib, "user32.lib" )


using namespace Tga2D;


CEngine* Tga2D::CEngine::myInstance = nullptr;


void Tga2D::CEngine::CreateInstance( const SEngineCreateParameters& aCreateParameters )
{
	if (!myInstance)
	{
		myInstance = new CEngine(aCreateParameters);
	}
	else
	{
		ERROR_PRINT("%s", "DX2D::CEngine::CreateInstance called twice, thats bad.");
	}
}


CEngine::CEngine( const SEngineCreateParameters& aCreateParameters)
: myWindow(nullptr)
, myDirect3D(nullptr)
, myRenderer(nullptr)
, myTextureManager(nullptr)
, myDebugDrawer(nullptr)
, myInputManager(nullptr)
, myHwnd(nullptr)
, myHInstance(nullptr)
, myLightManager(nullptr)
, myCreateParameters(aCreateParameters)
, myRunEngine(true)
, myTotalTime(0.0f)
, myDeltaTime(0.0f)
, myShouldExit(false)
, myWantToUpdateSize(false)
{
	myWindowSize.x = myCreateParameters.myWindowWidth;
	myWindowSize.y = myCreateParameters.myWindowHeight;

	myRenderSize.x = myCreateParameters.myRenderWidth;
	myRenderSize.y = myCreateParameters.myRenderHeight;

	myTargetSize = myRenderSize;
	if (myCreateParameters.myTargetWidth > 0 && myCreateParameters.myTargetHeight > 0)
	{
		myTargetSize.x = myCreateParameters.myTargetWidth;
		myTargetSize.y = myCreateParameters.myTargetHeight;
	}
	

	myDebugDrawer = new CDebugDrawer(myCreateParameters.myActivateDebugSystems);

	myInitFunctionToCall = myCreateParameters.myInitFunctionToCall;
	myUpdateFunctionToCall = myCreateParameters.myUpdateFunctionToCall;
	myHwnd = myCreateParameters.myHwnd;
	myHInstance = myCreateParameters.myHInstance;
	myCreateParameters.myHInstance = myCreateParameters.myHInstance;
	myClearColor = myCreateParameters.myClearColor;

	myErrorManager = new CErrorManager();
	myErrorManager->AddLogListener(aCreateParameters.myLogFunction, aCreateParameters.myErrorFunction);
}


CEngine::~CEngine()
{
	SAFE_DELETE(myWindow);
	SAFE_DELETE(myRenderer);
	SAFE_DELETE(myDebugDrawer);
	SAFE_DELETE(myTextService);
	SAFE_DELETE(myLightManager);
	SAFE_DELETE(myErrorManager);
	SAFE_DELETE(myFileWatcher);
	SAFE_DELETE(myTextureManager);
	SAFE_DELETE(myDirect3D);
}


void Tga2D::CEngine::DestroyInstance()
{
	if (myInstance)
	{
		myInstance->Shutdown();
	}
	
	SAFE_DELETE(myInstance);
}


bool CEngine::Start()
{
	INFO_PRINT("%s", "---TGA 2D Starting, dream big and dare to fail---");
	INFO_PRINT("%s", "Creating window");
	myFileWatcher = new CFileWatcher();
	myWindow = new CWindowsWindow();
	if (!myWindow->Init(myWindowSize, myHwnd, &myCreateParameters, myHInstance, myCreateParameters.myWinProcCallback))
	{
		ERROR_PRINT("%s", "Window failed to be created!");
		return false;
	}

	myDirect3D = new CDirectEngine();
	if (!myDirect3D->Init(*this, myRenderSize, myCreateParameters.myEnableVSync, myCreateParameters.myStartInFullScreen))
	{
		ERROR_PRINT("%s", "D3D failed to be created!");
		myWindow->Close();
		return false;
	}

	myDirect3D->SetClearColor(myClearColor);

	myRenderer = new CRenderer();
	myTextureManager = new CTextureManager();
	myTextureManager->Init();

	/*myFBXLoader = new CFbxLoader();*/
	myTextService = new CTextService();
	myTextService->Init();


	myLightManager = new CLightManager();
	CalculateRatios();

	if (myDebugDrawer)
	{
		myDebugDrawer->Init();
	}

	if (myInitFunctionToCall)
	{
		myInitFunctionToCall();
	}

	myStartOfTime = std::chrono::steady_clock::now();

    if( myUpdateFunctionToCall )
    {
        StartStep();

        DestroyInstance();
    }

	return true;
}

void Tga2D::CEngine::Shutdown()
{
	myRunEngine = false;
}

void Tga2D::CEngine::StartStep()
{
	DoStep();
}


void Tga2D::CEngine::DoStep()
{
	MSG msg = {0};

	while (myRunEngine)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)
			{
				INFO_PRINT("%s", "Exiting...");
				break;
			}
		}
		else
		{
			myTimer.Tick([&]()
			{
				myDeltaTime = static_cast<float>(myTimer.GetElapsedSeconds());
				myTotalTime += static_cast<float>(myTimer.GetElapsedSeconds());

				myFileWatcher->FlushChanges();
				myDirect3D->PostRenderFrame();
				myTextureManager->Update();
				myTextService->Update();
				if (myUpdateFunctionToCall)
				{
					myUpdateFunctionToCall();
				}

				myRenderer->Update();
				if (myDebugDrawer)
				{
					myDebugDrawer->Update(myDeltaTime);
					myDebugDrawer->Render();
				}
				myDirect3D->RenderFrame();

				myLightManager->PostFrameUpdate();

				if (myWantToUpdateSize)
				{
					UpdateWindowSizeChanges();
					myWantToUpdateSize = false;
				}
			});

			std::this_thread::yield();
		}
	}
}

void GetDesktopResolution(int& horizontal, int& vertical, HWND aHwnd)
{
	RECT r;
	GetClientRect(aHwnd, &r); //get window rect of control relative to screen
	horizontal = r.right - r.left;
	vertical = r.bottom - r.top;
}

void Tga2D::CEngine::UpdateWindowSizeChanges()
{
	if (!myCreateParameters.myAutoUpdateViewportWithWindow)
	{
		return;
	}

	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical, *myHwnd);

	// Both these values must be your real window size, so of course these values can't be static
	float screen_width = (float)horizontal;
	float screen_height = (float)vertical;

	// This is your target virtual resolution for the game, the size you built your game to
	float virtual_width = (float)myTargetSize.x;
	float  virtual_height = (float)myTargetSize.y;

	float targetAspectRatio = virtual_width / virtual_height;

	// figure out the largest area that fits in this resolution at the desired aspect ratio
	float  width = screen_width;
	float  height = (float)(width / targetAspectRatio);

	if (height > screen_height)
	{
		//It doesn't fit our height, we must switch to pillarbox then
		height = screen_height;
		width = (float)(height * targetAspectRatio );
	}

	// set up the new viewport centered in the backbuffer
	float  vp_x = (screen_width / 2.0f) - (width / 2.0f);
	float  vp_y = (screen_height / 2.0f) - (height / 2.0f);

	static float lastWidth = 0.0f;
	static float lastHeight = 0.0f;

	{
		lastWidth = width;
		lastHeight = height;
		SetViewPort(vp_x, vp_y, width, height, 0, 1, true);
	}
}
/*


void Tga2D::CEngine::SetWorldMatrixPosition( const Vector2f &aPosition )
{
	Vector2f correctedPos = aPosition;
	// Helpers to get the right camera position
	float ratio = GetWindowRatio();
	correctedPos.x = (((correctedPos.x * -1.0f) * 2.0f) ) + ratio;
	correctedPos.y *= 2.0f;
	correctedPos.y -= 1.0f;

	myDirect3D->SetWorldMatrixPosition(correctedPos, aPosition);
}


void Tga2D::CEngine::SetWorldMatrixZoom( float aZoom )
{
	myDirect3D->SetWorldMatrixZoom(aZoom);
}
*/


float Tga2D::CEngine::GetWindowRatio() const
{
	return myWindowRatio;
}

float Tga2D::CEngine::GetWindowRatioInversed() const
{
	return myWindowRatioInversed;
}

Vector2f Tga2D::CEngine::GetWindowRatioVec() const
{
	return myWindowRatioVec;
}

Vector2f Tga2D::CEngine::GetWindowRatioInversedVec() const
{
	return myWindowRatioInversedVec;
}

void Tga2D::CEngine::SetResolution(const Tga2D::Vector2<unsigned int> &aResolution, bool aAlsoSetWindowSize)
{
	myWindowSize = aResolution;
	if (aAlsoSetWindowSize)
	{
		myWindow->SetResolution(aResolution);
	}
	myDirect3D->SetResolution(aResolution);
	CalculateRatios();

}

void Tga2D::CEngine::CalculateRatios()
{
	float sizeX = static_cast<float>(myWindowSize.x);
	float sizeY = static_cast<float>(myWindowSize.y);
	if (sizeY > sizeX)
	{
		float temp = sizeX;
		sizeX = sizeY;
		sizeY = temp;
	}

	myWindowRatio = static_cast<float>(sizeX) / static_cast<float>(sizeY);
	myWindowRatioInversed = static_cast<float>(sizeY) / static_cast<float>(sizeX);
	
	myWindowRatioVec.x = 1.0f;
	myWindowRatioVec.y = 1.0f;
	myWindowRatioInversedVec.x = 1.0f;
	myWindowRatioInversedVec.y = 1.0f;
	if (sizeX >= sizeY)
	{
		myWindowRatioVec.y = myWindowRatio;
		myWindowRatioInversedVec.y = myWindowRatioInversed;
	}
	else
	{
		myWindowRatioVec.x = myWindowRatio;
		myWindowRatioInversedVec.x = myWindowRatioInversed;
	}
}

HWND* Tga2D::CEngine::GetHWND() const
{
	return myHwnd;
}


HINSTANCE Tga2D::CEngine::GetHInstance() const
{
	return myHInstance;
}

void Tga2D::CEngine::SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth, float aMaxDepth, bool aSetEngineResolution)
{
	if (myDirect3D)
	{
		if (aSetEngineResolution)
		{
			SetResolution(Tga2D::Vector2<unsigned int>(static_cast<unsigned int>(aWidth), static_cast<unsigned int>(aHeight)), false);
		}	
		myDirect3D->SetViewPort(aTopLeftX, aTopLeftY, aWidth, aHeight, aMinDepth, aMaxDepth);
	}
}

void Tga2D::CEngine::SetFullScreen(bool aFullScreen)
{
	if (myDirect3D)
	{
		myDirect3D->SetFullScreen(aFullScreen);
	}
}

bool Tga2D::CEngine::IsDebugFeatureOn(eDebugFeatures aFeature) const
{
	const bool all = ((myCreateParameters.myActivateDebugSystems & eDebugFeature_All) != 0);
	if (all)
	{
		return true;
	}

	const bool specific = ((myCreateParameters.myActivateDebugSystems & aFeature) != 0);
	return specific;
}


void Tga2D::CEngine::SetSampler(ESamplerType aType)
{
	if (myDirect3D)
	{
		myDirect3D->SetSampler(aType);
	}
}

ESamplerType Tga2D::CEngine::GetSamplerType() const
{
	if (myDirect3D)
	{
		return myDirect3D->GetSamplerType();
	}
	return ESamplerType_Linear;
}

bool CEngine::BeginFrame(const CColor &aClearColor)
{
	if (myShouldExit)
	{
		return false;
	}
	MSG msg = { 0 };

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			INFO_PRINT("%s", "Exiting...");
			myShouldExit = true;
			return false;
		}
	}

    myFileWatcher->FlushChanges();
    myDirect3D->Clear( aClearColor );
    myTextureManager->Update();
    myTextService->Update();
	return true;
}


void CEngine::EndFrame( void )
{
	myTimer.Tick([&]()
	{
		myDeltaTime = static_cast<float>(myTimer.GetElapsedSeconds());
		myTotalTime += static_cast<float>(myTimer.GetElapsedSeconds());

		myRenderer->Update();

		if (myDebugDrawer)
		{
			myDebugDrawer->Update(myDeltaTime);
			myDebugDrawer->Render();
		}

		myDirect3D->RenderFrame();

		myLightManager->PostFrameUpdate();

		if (myWantToUpdateSize)
		{
			UpdateWindowSizeChanges();
			myWantToUpdateSize = false;
		}
	});

    std::this_thread::yield();
}

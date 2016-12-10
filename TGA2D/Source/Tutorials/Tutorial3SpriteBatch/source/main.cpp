#include <string>
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>

#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>


// Set USE_CONSOLE_COMMAND to 1 to enable the console window for logging and error
// messages etc.
//
#define USE_CONSOLE_COMMAND (1)


// If USE_CONSOLE_COMMAND is set then link the application as a windows console
// application.
#if USE_CONSOLE_COMMAND
#pragma comment(linker, "/SUBSYSTEM:console")
#else
#pragma comment(linker, "/SUBSYSTEM:windows")
#endif // USE_CONSOLE_COMMAND


// Making sure that DX2DEngine lib is linked
//
#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")
#elif NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // _DEBUG


// This is where the application actually starts
//
void Go( void );


#if USE_CONSOLE_COMMAND
// This is the application starting point used if we start from a console window.
// The WinMain function should copy this except for how console parameters are
// handled.
//
int main( const int /*argc*/, const char * /*argc*/[] )
{
    Go();

    return 0;
}
#else
// This is the application starting point used if we start without a console window.
// The functionality inside is identical to that of the standard main function. If we
// wish to check console arguments it will have to be done a bit differently from
// the console version.
//
int WINAPI WinMain( HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, char*, int /*nShowCmd*/ )
{
    Go();

    return 0;
}
#endif // USE_CONSOLE_COMMAND


// This is where the application starts of for real. By keeping this in it's own file
// we will have the same behaviour for both console and windows startup of the
// application.
//
void Go( void )
{
    // Lets keep the window size as hardcoded constants for now.
    //
    const unsigned short windowWidth  = 1280;
    const unsigned short windowHeight = 720;

    // Here the settings used when setting up the DX2D-engine are set.
    Tga2D::SEngineCreateParameters createParameters;
    createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps
                                            | Tga2D::eDebugFeature_Mem
                                            | Tga2D::eDebugFeature_Filewatcher
                                            | Tga2D::eDebugFeature_Cpu
                                            | Tga2D::eDebugFeature_Drawcalls;

    createParameters.myActivateDebugSystems = true;
    createParameters.myWindowWidth          = static_cast<unsigned short>( windowWidth );
    createParameters.myWindowHeight         = static_cast<unsigned short>( windowHeight );
    createParameters.myRenderWidth          = static_cast<unsigned short>( windowWidth );
    createParameters.myRenderHeight         = static_cast<unsigned short>( windowHeight );
    createParameters.myEnableVSync          = true;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );

    std::wstring appname = L"TGA2D: Tutorial 3";
#ifdef _DEBUG
    appname += L" [Debug]";
#endif

    createParameters.myApplicationName = appname;

    Tga2D::CEngine::CreateInstance( createParameters );
    if( !Tga2D::CEngine::GetInstance()->Start() )
    {
        ERROR_PRINT( "Fatal error! Engine could not start!" );
        system("pause");
        exit( -1 );
    }


	// MAIN LOOP
	Tga2D::CSpriteBatch spriteBatch(true); // When inited to true the batch takes ownership of newed sprites and will delete them
	spriteBatch.Init("sprites/tga_logo.dds");

	for (unsigned int i=0; i< 1000; i++)
	{
		Tga2D::CSprite* sprite = new Tga2D::CSprite(nullptr); // Make sure to send null here as it is the batch that holds the texture!

		float randomX = static_cast<float>(rand() % 1000) / 1000.0f;
		float randomY = static_cast<float>(rand() % 1000) / 1000.0f;

		sprite->SetPosition(Tga2D::Vector2f(randomX, randomY));
		sprite->SetColor(Tga2D::CColor(randomX, randomY, randomX, 1));
		sprite->SetPivot(Tga2D::Vector2f(0.5f, 0.5f));
		sprite->SetSize(Tga2D::Vector2f(0.1f, 0.1f));

		spriteBatch.AddObject(sprite); // Add the sprites to the batch
	}
	
	while (true)
	{
		if (!Tga2D::CEngine::GetInstance()->BeginFrame(Tga2D::CColor(0, 0, 0.3f, 1)))
		{
			break;
		}

		// Render the image on the screen
		spriteBatch.Render();



		Tga2D::CEngine::GetInstance()->EndFrame();
	}

}

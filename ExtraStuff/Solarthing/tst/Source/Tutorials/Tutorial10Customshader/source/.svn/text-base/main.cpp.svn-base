#include <string>
#include <tga2d/engine.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/texture/texture_manager.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/shaders/customshader.h>

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
    const unsigned short windowWidth  = 1920;
    const unsigned short windowHeight = 1080;

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
	createParameters.myAutoUpdateViewportWithWindow = true;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );

    std::wstring appname = L"TGA2D: Tutorial 10";
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

	// Create the sprite with the path to the image
	Tga2D::CSprite sprite("sprites/tga_logo.dds");

	// Setting the pivot so all operations will be in the middle of the image (rotation, position, etc.)
	sprite.SetPivot(Tga2D::Vector2f(0.5f, 0.5f));


	/////////// Custom shader

	// Create a new shader
	Tga2D::CCustomShader customShader; // Create
	customShader.SetShaderdataFloat4(Tga2D::Vector4f(1, 0, 1, 1), Tga2D::EShaderDataID_1); // Add some data to it
	customShader.SetTextureAtRegister(Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture("sprites/tga_logo.dds"), Tga2D::EShaderTextureSlot_1); // Add a texture

	// Run PostInit to set all the data
	customShader.PostInit("../source/tutorials/Tutorial3Customshader/custom_sprite_vertex_shader.fx", "../source/tutorials/Tutorial3Customshader//custom_sprite_pixel_shader.fx", Tga2D::EShaderDataBufferIndex_1);

	// Tell the sprite to use this shader
	sprite.SetCustomShader(&customShader);
	/////////// Custom shader

	float timer = 0;
	while (true)
	{
		timer += 1.0f / 60.0f;
		if (!Tga2D::CEngine::GetInstance()->BeginFrame(Tga2D::CColor(0, 0, 0.3f, 1)))
		{
			break;
		}

		// Set a new position
		sprite.SetPosition(Tga2D::Vector2f( (cos(timer) + 1) / 2, (sin(timer) + 1) / 2));
		// Set the rotation
		sprite.SetRotation(cos(timer));
		// Render the image on the screen
		sprite.Render();

		// using the same instance we reuse the image and set a new position
		sprite.SetPosition(Tga2D::Vector2f((sin(timer) + 1) / 2, (cos(timer) + 1) / 2));

		// Render it a second time at a new position
		sprite.Render();

		Tga2D::CEngine::GetInstance()->EndFrame();
	}

}

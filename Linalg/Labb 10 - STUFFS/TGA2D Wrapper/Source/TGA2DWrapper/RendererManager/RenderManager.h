#pragma once

#include <string>

#include <GrowingArray\GrowingArray.h>

#include "Commands\Sprite\RenderCommand.h"
#include "Commands\Lines\RenderCommandLine.h"
#include "..\BaseClasses\BaseGameObject\BaseGameObject.h"


struct Settings;

namespace DX2D
{
	class CSpriteBatch;
}

class RenderManager
{
public:

	static bool Create();
	static bool Destroy();
	
	static void SwapBuffers();
	static void Render();

	static void AddRenderCommand(const RenderCommand &aRenderCommand);
	static void AddRenderCommandLine(const RenderCommandLine &aRenderCommand);

	static void DrawDebugLine();


private:

	static RenderManager* ourInstance;
	CommonUtilities::GrowingArray<RenderCommand> *myRenderCommandsOffscreen, *myRenderCommandsActive;
	CommonUtilities::GrowingArray<RenderCommandLine> *myRenderCommandLinesOffscreen, *myRenderCommandLinesActive;

	DX2D::CSprite *myBorderSprite;

	DX2D::CSpriteBatch * myBallBatch;

	RenderManager();
	~RenderManager();

	static RenderManager* GetInstance();

	void SwapBuffersInternal();
	void RenderInternal();

};

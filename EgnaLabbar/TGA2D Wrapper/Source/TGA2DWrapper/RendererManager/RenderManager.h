#pragma once

#include <string>

#include <GrowingArray\GrowingArray.h>

#include "Commands\Sprite\RenderCommand.h"
#include "Commands\Lines\RenderCommandLine.h"
#include "Text\TextRenderCommand.h"
#include "..\BaseClasses\BaseGameObject\BaseGameObject.h"

struct Settings;

class RenderManager
{
public:

	static bool Create();
	static bool Destroy();
	
	static void SwapBuffers();
	static void Render();

	static void AddRenderCommand(const RenderCommand &aRenderCommand, const float aPriority = 0.f);
	static void AddRenderCommandText(const TextRenderCommand &aRenderCommand);
	static void AddRenderCommandLine(const RenderCommandLine &aRenderCommand);

private:

	struct RenderCommandOrderStruct
	{
		RenderCommandOrderStruct();
		RenderCommandOrderStruct(const unsigned short aCommandIndex, const float aPriority);
		unsigned short myCommandIndex;
		float myPriority;
	};

	static RenderManager* ourInstance;

	CommonUtilities::GrowingArray<RenderCommand> *myRenderCommandsOffscreen, *myRenderCommandsActive;
	CommonUtilities::GrowingArray<RenderCommandOrderStruct> *myRenderCommandOrderOffscreen, *myRenderCommandOrderActive;

	CommonUtilities::GrowingArray<TextRenderCommand> *myRenderCommandTextOffscreen, *myRenderCommandTextActive;
	CommonUtilities::GrowingArray<RenderCommandLine> *myRenderCommandLinesOffscreen, *myRenderCommandLinesActive;

	DX2D::CSprite *myBorderSprite;

	RenderManager();
	~RenderManager();

	static RenderManager* GetInstance();

	void SwapBuffersInternal();
	void RenderInternal();

};

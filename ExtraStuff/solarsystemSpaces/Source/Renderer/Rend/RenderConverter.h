#pragma once
#include "Rend/Renderer.h"
#include <CU/PostMaster/MessageReceiver.h>

class StaticSprite;
class Camera2D;

class RenderConverter : public MessageReceiver
{
public:
	static void Create();
	static void Destroy();

	static void Init(const CU::Vector2ui & aWindowSize);

	static void CalculateAndRenderSprite(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition);
	static void RenderSpriteNormalized(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition);

	static void DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor = CU::Vector4f::One);

	static void Draw();
	//static void SetCamera(const Camera2D & aCamera);

	static void SwapBuffers();
	static void ClearCommands();

	static void SetShouldCull(const bool aCullingFlag);

	//virtual bool RecieveMessage(const SetMainCameraMessage & aMessage) override;

private:
	RenderConverter();
	~RenderConverter();

	static RenderConverter * ourInstance;

	static RenderConverter & GetInstance();
	void AddRenderCommand(RenderCommand & aRenderCommand);

	const Camera2D * myCamera;

	CU::Vector2ui myLevelTileLayout;
	CU::Vector2ui myWindowSize;
	Renderer myRenderer;
};

inline RenderConverter & RenderConverter::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "RenderConverter Singleton instance is nullptr");
	return *ourInstance;
}


#define DRAWLINE(aStartPosition, aEndPosition) RenderConverter::DrawLine((aStartPosition),(aEndPosition));
#define DRAWISOMETRICLINE(aStartPosition, aEndPosition) RenderConverter::DrawIsometricLine((aStartPosition),(aEndPosition));
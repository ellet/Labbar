#include "RenderManager.h"

#include <utility>

#include <tga2d\sprite\sprite.h>
#include <tga2d\engine.h>

#include <DLDebug/DL_Debug.h>

#include "..\Utility\ScreenResolution.h"
#include <tga2d\sprite\sprite_batch.h>

RenderManager* RenderManager::ourInstance;

bool RenderManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new RenderManager();
		return true;
	}
	return false;
}
bool RenderManager::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
	return false;
}

void RenderManager::SwapBuffers()
{
	GetInstance()->SwapBuffersInternal();
}
void RenderManager::Render()
{
	GetInstance()->RenderInternal();
}

void RenderManager::AddRenderCommand(const RenderCommand &aRenderCommand)
{
	GetInstance()->myRenderCommandsOffscreen->Add(aRenderCommand);
}

void RenderManager::AddRenderCommandLine(const RenderCommandLine &aRenderCommand)
{
	GetInstance()->myRenderCommandLinesOffscreen->Add(aRenderCommand);
}

void RenderManager::DrawDebugLine()
{

}


RenderManager::RenderManager()
{

	myRenderCommandsOffscreen = new CommonUtilities::GrowingArray<RenderCommand>();
	myRenderCommandsActive = new CommonUtilities::GrowingArray<RenderCommand>();

	myRenderCommandsOffscreen->Init(32);
	myRenderCommandsActive->Init(32);

	myRenderCommandLinesOffscreen = new CommonUtilities::GrowingArray<RenderCommandLine>();
	myRenderCommandLinesActive = new CommonUtilities::GrowingArray<RenderCommandLine>();

	myRenderCommandLinesOffscreen->Init(32);
	myRenderCommandLinesActive->Init(32);

	myBorderSprite = new DX2D::CSprite("Sprites/BlackSquare16x16.dds");
	myBorderSprite->SetColor(DX2D::CColor(0.f, 0.f, 0.f, 1.f));
	myBorderSprite->SetPivot(DX2D::Vector2f(0.f, 0.f));

	myBallBatch = new DX2D::CSpriteBatch(true);
	myBallBatch->Init("Sprites/chokladboll.dds");
}
RenderManager::~RenderManager()
{

	delete myRenderCommandsOffscreen;
	delete myRenderCommandsActive;
	delete myRenderCommandLinesOffscreen;
	delete myRenderCommandLinesActive;
	delete myBorderSprite;

}

RenderManager* RenderManager::GetInstance()
{
	DL_ASSERT((ourInstance != nullptr), "RenderManager instance is nullptr");
	return ourInstance;
}

void RenderManager::SwapBuffersInternal()
{
	std::swap(myRenderCommandsActive, myRenderCommandsOffscreen);
	std::swap(myRenderCommandLinesActive, myRenderCommandLinesOffscreen);
}

void RenderManager::RenderInternal()
{

	//TODO::Remove when it detects window size change.
	ScreenResolution::UpdateResolution();

	const DX2D::Vector2ui virtualScreenSize = DX2D::CEngine::GetInstance()->GetWindowSize();

	const Vector2f& position = Vector2f::Zero; //ScreenResolution::GetViewTransform();
	const Vector2f& size = ScreenResolution::GetViewScale();

	for (unsigned short i = 0; i < myRenderCommandsActive->Size(); ++i)
	{
		myBallBatch->AddObject((*myRenderCommandsActive)[i].Render(position, size));
	}

	for (unsigned short i = 0; i < myRenderCommandLinesActive->Size(); ++i)
	{
		(*myRenderCommandLinesActive)[i].Render(position, size);
	}
	
	/*if (ScreenResolution::GetViewScale().y < 1.f)
	{
		
		myBorderSprite->SetSize(DX2D::Vector2f(virtualScreenSize.x / 16.f, (virtualScreenSize.y / 16.f) * position.y));

		myBorderSprite->SetPosition(DX2D::Vector2f(0.f, 0.f));
		myBorderSprite->Render();
		myBorderSprite->SetPosition(DX2D::Vector2f(0.f, (1.f - size.y) / 2 + size.y));
		myBorderSprite->Render();
		
	}
	else if (ScreenResolution::GetViewScale().x < 1.f)
	{
		myBorderSprite->SetSize(DX2D::Vector2f((virtualScreenSize.x / 16.f) * position.x, virtualScreenSize.y / 16.f));
		
		myBorderSprite->SetPosition(DX2D::Vector2f(0.f, 0.f));
		myBorderSprite->Render();
		myBorderSprite->SetPosition(DX2D::Vector2f((1.f - size.x) / 2 + size.x, 0.f));
		myBorderSprite->Render();
	}*/

	myBallBatch->Render();
	myBallBatch->ClearAll();

	myRenderCommandsActive->RemoveAll();
	myRenderCommandLinesActive->RemoveAll();

}

#include "RenderManager.h"

#include <utility>

#include <tga2d\sprite\sprite.h>
#include <tga2d\engine.h>

#include <DLDebug/DL_Debug.h>

#include "..\Utility\ScreenResolution.h"

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

void RenderManager::AddRenderCommand(const RenderCommand &aRenderCommand, const float aPriority)
{
	
	RenderManager &instance = *GetInstance();

	instance.myRenderCommandsOffscreen->Add(aRenderCommand);

	//TODO::Faster sort. Optimazation purpose only.
	for (unsigned short i = 0; i < instance.myRenderCommandOrderOffscreen->Size(); ++i)
	{
		if (aPriority < (*instance.myRenderCommandOrderOffscreen)[i].myPriority)
		{
			RenderCommandOrderStruct order(instance.myRenderCommandsOffscreen->Size() - 1, aPriority);
			instance.myRenderCommandOrderOffscreen->Insert(i, order);
			return;
		}
	}

	instance.myRenderCommandOrderOffscreen->Add(RenderCommandOrderStruct(instance.myRenderCommandsOffscreen->Size() - 1, aPriority));

}
void RenderManager::AddRenderCommandText(const TextRenderCommand &aRenderCommand)
{
	GetInstance()->myRenderCommandTextOffscreen->Add(aRenderCommand);
}
void RenderManager::AddRenderCommandLine(const RenderCommandLine &aRenderCommand)
{
	GetInstance()->myRenderCommandLinesOffscreen->Add(aRenderCommand);
}

RenderManager::RenderManager()
{

	myRenderCommandsOffscreen = new CommonUtilities::GrowingArray<RenderCommand>();
	myRenderCommandsActive = new CommonUtilities::GrowingArray<RenderCommand>();
	myRenderCommandsOffscreen->Init(32);
	myRenderCommandsActive->Init(32);

	myRenderCommandOrderOffscreen = new CommonUtilities::GrowingArray<RenderCommandOrderStruct>();
	myRenderCommandOrderActive = new CommonUtilities::GrowingArray<RenderCommandOrderStruct>();
	myRenderCommandOrderOffscreen->Init(32);
	myRenderCommandOrderActive->Init(32);

	myRenderCommandTextOffscreen = new CommonUtilities::GrowingArray<TextRenderCommand>();
	myRenderCommandTextActive = new CommonUtilities::GrowingArray<TextRenderCommand>();
	myRenderCommandTextOffscreen->Init(8);
	myRenderCommandTextActive->Init(8);

	myRenderCommandLinesOffscreen = new CommonUtilities::GrowingArray<RenderCommandLine>();
	myRenderCommandLinesActive = new CommonUtilities::GrowingArray<RenderCommandLine>();
	myRenderCommandLinesOffscreen->Init(32);
	myRenderCommandLinesActive->Init(32);

	myBorderSprite = new DX2D::CSprite("Sprites/BlackSquare16x16.dds");
	myBorderSprite->SetColor(DX2D::CColor(0.f, 0.f, 0.f, 1.f));
	myBorderSprite->SetPivot(DX2D::Vector2f(0.f, 0.f));

}
RenderManager::~RenderManager()
{

	delete myRenderCommandsOffscreen;
	delete myRenderCommandsActive;
	delete myRenderCommandOrderOffscreen;
	delete myRenderCommandOrderActive;
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
	std::swap(myRenderCommandOrderActive, myRenderCommandOrderOffscreen);
	std::swap(myRenderCommandTextActive, myRenderCommandTextOffscreen);
	std::swap(myRenderCommandLinesActive, myRenderCommandLinesOffscreen);
}

void RenderManager::RenderInternal()
{

	//TODO::Remove when it detects window size change.
	ScreenResolution::UpdateResolution();

	const DX2D::Vector2ui virtualScreenSize = DX2D::CEngine::GetInstance()->GetWindowSize();

	const Vector2f& position = ScreenResolution::GetViewTransform();
	const Vector2f& size = ScreenResolution::GetViewScale();

	for (unsigned short i = 0; i < myRenderCommandOrderActive->Size(); ++i)
	{
		(*myRenderCommandsActive)[(*myRenderCommandOrderActive)[i].myCommandIndex].Render(position, size);
	}

	for (unsigned short i = 0; i < myRenderCommandTextActive->Size(); ++i)
	{
		(*myRenderCommandTextActive)[i].Render(position, size);
	}

	for (unsigned short i = 0; i < myRenderCommandLinesActive->Size(); ++i)
	{
		(*myRenderCommandLinesActive)[i].Render(position, size);
	}

	if (ScreenResolution::GetViewScale().y < 1.f)
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

	}

	myRenderCommandsActive->RemoveAll();
	myRenderCommandOrderActive->RemoveAll();
	myRenderCommandTextActive->RemoveAll();
	myRenderCommandLinesActive->RemoveAll();

}

RenderManager::RenderCommandOrderStruct::RenderCommandOrderStruct()
{
}
RenderManager::RenderCommandOrderStruct::RenderCommandOrderStruct(const unsigned short aCommandIndex, const float aPriority)
	:myCommandIndex(aCommandIndex), myPriority(aPriority)
{
}

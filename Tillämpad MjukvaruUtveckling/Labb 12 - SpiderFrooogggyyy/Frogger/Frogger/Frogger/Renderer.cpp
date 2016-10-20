#include "stdafx.h"
#include "Renderer.h"




void Renderer::AddRenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition)
{
	myBuildBuffer->Add(new RenderCommand(aSprite, aPosition));
}


void Renderer::AddStretchedRenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition, const CommonUtilities::Vector2f & aOtherPosition)
{
	myBuildBuffer->Add(new StretchedRenderCommand(aSprite, aPosition, aOtherPosition));
}

void Renderer::AddTextRenderCommand(hgeFont& aFont, const CommonUtilities::Vector2f & aPosition, const unsigned int aAlignID, const std::string & aText)
{
	myBuildBuffer->Add(new TextRenderCommand(aFont, aPosition, aAlignID, aText));
}

void Renderer::Render()
{
	unsigned short tempSize = myRenderBuffer->Count();
	for (unsigned short iRender = 0; iRender < tempSize; ++iRender)
	{
		(*myRenderBuffer)[iRender]->Render();
	}
}

void Renderer::ChangeBuildBuffer()
{
	std::lock_guard<std::mutex> lock(myBufferLock);
	//MUTAX LOCK
	std::swap(myBuildBuffer, myInactiveBuffer);
	myBuildBuffer->DeleteAll();

}

void Renderer::ChangeRenderBuffer()
{
	std::lock_guard<std::mutex> lock(myBufferLock);
	//MUTAX LOCK
	std::swap(myRenderBuffer, myInactiveBuffer);
	
}

Renderer::Renderer()
{
	myBuildBuffer = &myRenderBuffer1;
	myRenderBuffer = &myRenderBuffer2;
	myInactiveBuffer = &myRenderBuffer3;
}


Renderer::~Renderer()
{
}
#pragma once
#include "GrowingArray.h"
#include "RenderCommand.h"
#include <mutex>
#include <atomic>



class Renderer
{	
	friend class MainSingleton;
public:

	void AddRenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition);
	void AddStretchedRenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition, const CommonUtilities::Vector2f & aOtherPosition);
	void AddTextRenderCommand(hgeFont& aFont, const CommonUtilities::Vector2f & aPosition, const unsigned int aAlignID, const std::string & aText);
	void Render();

	void ChangeBuildBuffer();
	void ChangeRenderBuffer();

	

private:
	std::mutex myBufferLock;


	Renderer();
	~Renderer();

	

	CommonUtilities::GrowingArray<BaseRenderCommand*> * myRenderBuffer;
	CommonUtilities::GrowingArray<BaseRenderCommand*> * myBuildBuffer;
	CommonUtilities::GrowingArray<BaseRenderCommand*> * myInactiveBuffer;
	
	CommonUtilities::GrowingArray<BaseRenderCommand*> myRenderBuffer1;
	CommonUtilities::GrowingArray<BaseRenderCommand*> myRenderBuffer2;
	CommonUtilities::GrowingArray<BaseRenderCommand*> myRenderBuffer3;
};


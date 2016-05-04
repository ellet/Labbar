#include "stdafx.h"
#include "Renderer.h"

Renderer * Renderer::ourInstance = nullptr;

void Renderer::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Renderer();
	}
}

void Renderer::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}







Renderer::Renderer()
{
	myBoardsToDraw.Init(3); 
	myFinalBoardsToDraw.Init(10);
}


Renderer::~Renderer()
{
}

void Renderer::InternalDrawBoards(DX2D::CSprite & horseSprite, DX2D::CSprite & tileSprite, std::mutex & aMutex)
{
	/*for (unsigned short iBoard = 0; iBoard < myBoardsToDraw.Size(); ++iBoard)
	{
		myBoardsToDraw[iBoard].DrawBoard(horseSprite, tileSprite);
	}*/
	//std::lock_guard<std::mutex> daGaurd(aMutex);
	aMutex.lock();

	/*if (myBoardsToDraw.Size() > 0)
	{
		myLatestBoardToDraw = myBoardsToDraw.GetLast();
	}*/

	myBoardsToDraw.RemoveAll();

	myLatestBoardToDraw.DrawBoard(DX2D::Vector2f(0.f, .15f), 0.04f, horseSprite, tileSprite);
	aMutex.unlock();

	for (unsigned short iBoard = 0; iBoard < myFinalBoardsToDraw.Size(); ++iBoard)
	{
		myFinalBoardsToDraw[iBoard].DrawBoard(DX2D::Vector2f(0.15f * iBoard, 0.55f), 0.02f, horseSprite, tileSprite);
	}
}
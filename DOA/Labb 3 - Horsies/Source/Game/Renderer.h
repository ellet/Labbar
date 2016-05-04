#pragma once

#include <GrowingArray/GrowingArray.h>
#include <DLDebug/DL_Debug.h>
#include "Board.h"
#include <mutex>

namespace DX2D
{
	class CSprite;
}


class Renderer
{
public:
	static void Create();
	static void Destroy();

	static inline void DrawBoard(DX2D::CSprite & horseSprite, DX2D::CSprite & tileSprite, std::mutex & aMutex);
	static inline void AddBoardToDraw(const Board & aBoardToDraw, std::mutex & aMutex);

	static inline void AddFinalBoard(const Board & aBoardToDraw);

private:
	Renderer();
	~Renderer();

	void InternalDrawBoards(DX2D::CSprite & horseSprite, DX2D::CSprite & tileSprite, std::mutex & aMutex);

	static Renderer * ourInstance;

	CU::GrowingArray<Board> myBoardsToDraw;
	CU::GrowingArray<Board> myFinalBoardsToDraw;
	Board myLatestBoardToDraw;

	static Renderer & GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "ourinstance is nullptr");
		return *ourInstance;
	}
};

inline void Renderer::AddBoardToDraw(const Board & aBoardToDraw, std::mutex & aMutex)
{
	aMutex.lock();
	//GetInstance().myBoardsToDraw.Add(aBoardToDraw);
	GetInstance().myLatestBoardToDraw = aBoardToDraw;
	aMutex.unlock();
}

void Renderer::DrawBoard(DX2D::CSprite & horseSprite, DX2D::CSprite & tileSprite, std::mutex & aMutex)
{
	GetInstance().InternalDrawBoards(horseSprite, tileSprite, aMutex);
}

void Renderer::AddFinalBoard(const Board & aBoardToDraw)
{
	GetInstance().myFinalBoardsToDraw.Add(aBoardToDraw);
}
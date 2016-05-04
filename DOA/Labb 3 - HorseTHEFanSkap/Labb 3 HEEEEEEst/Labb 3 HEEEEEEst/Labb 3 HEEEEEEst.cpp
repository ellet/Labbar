// Labb 3 HEEEEEEst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GrowingArray/GrowingArray.h>
#include <NameSpaceAliases.h>
#include "Classes/Board.h"
#include <thread>


void Logic()
{
	short boardSize = 3;
	Board testBoard(boardSize);
	while (true)
	{
		std::cout << "Calculating with size " << boardSize << "x" << boardSize << std::endl;
		testBoard.AddMaximumHorsies(0, 0);
		testBoard.DrawBoard();
		++boardSize;
		testBoard.SetBoardSize(boardSize);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	DL_Debug::Debug::Create();

	std::thread * logicThread = new std::thread(&Logic);

	system("pause");
	std::exit(0);
	logicThread->join();
	return 0;
}

#include "stdafx.h"
#include "Board.h"


Board Board::AddMaximumHorsies(const short X, const short Y)
{
	static size_t ID = 0;
	size_t thisFunctionID = ID;
	++ID;

	AddHORSEFAN(X, Y);
	Board tempBestBoard(*this);
	int tempX = X;
	for (unsigned short iY = Y; iY < mySideSize; ++iY)
	{
		for (; tempX < mySideSize; ++tempX)
		{
			if (CHECKhorsefan(tempX, iY) == true)
			{
				Board testBoard(*this);
				testBoard.AddMaximumHorsies(tempX, iY);
				if (testBoard.CheckHorsiesOnBoard() > tempBestBoard.CheckHorsiesOnBoard())
				{
					tempBestBoard = testBoard;
					if (thisFunctionID == 0)
					{
						std::cout << "Best so far " << tempBestBoard.CheckHorsiesOnBoard() << std::endl;
					}
				}
			}
		}
		tempX = 0;
	}
	*this = tempBestBoard;
	return *this;
}

#pragma once

#include <bitset> 

class Board
{
public:
	inline Board(const short aBoardSize);
	inline ~Board();

	inline void SetBoardSize(const short aBoardSize);

	inline void DrawBoard() const;

	Board AddMaximumHorsies(const short X, const short Y);

	inline void AddHORSEFAN(const short X, const short Y);

	inline bool CHECKhorsefan(const short X, const short Y);

	inline bool CheckTileForPRETTYPONIA(const short X, const short Y);

	inline size_t CheckHorsiesOnBoard();

private:
	std::bitset<128> myBoard;
	size_t myHorseISE;
	short mySideSize;
};


inline Board::Board(const short aBoardSize)
{
	SetBoardSize(aBoardSize);
}

inline Board::~Board()
{
}

inline void Board::SetBoardSize(const short aBoardSize)
{
	mySideSize = aBoardSize;
	myHorseISE = 0;

	for (unsigned short iSquare = 0; iSquare < 128; ++iSquare)
	{
		myBoard[iSquare] = false;
	}
}

inline void Board::DrawBoard() const
{
	for (unsigned short iColumns = 0; iColumns < mySideSize; ++iColumns)
	{
		for (unsigned short iRows = 0; iRows < mySideSize; ++iRows)
		{
			if (myBoard[(iColumns * mySideSize) + iRows] == true)
			{
				std::cout << " H ";
			}
			else
			{
				std::cout << " O ";
			}
		}
		std::cout << std::endl;
	}

	std::cout << "There are " << myHorseISE << " HORSIES" << std::endl;
}


inline void Board::AddHORSEFAN(const short X, const short Y)
{
	DL_ASSERT(myBoard[(Y * mySideSize) + X] == false, "Trying TO Put Pony on OTher pony, YOU DIRTY FUCKER!");
	myBoard[(Y * mySideSize) + X] = true;
	++myHorseISE;
}

inline bool Board::CHECKhorsefan(const short X, const short Y)
{
	if (myBoard[(Y * mySideSize) + X] == true)
	{
		return false;
	}
	else
	{
		if ((CheckTileForPRETTYPONIA(X + 2, Y + 1) == false &&
			CheckTileForPRETTYPONIA(X + 2, Y - 1) == false
			)
			&&
			(CheckTileForPRETTYPONIA(X - 2, Y + 1) == false &&
			CheckTileForPRETTYPONIA(X - 2, Y - 1) == false
			)
			&&
			(CheckTileForPRETTYPONIA(X - 1, Y + 2) == false &&
			CheckTileForPRETTYPONIA(X - 1, Y - 2) == false
			)
			&&
			(CheckTileForPRETTYPONIA(X + 1, Y + 2) == false &&
			CheckTileForPRETTYPONIA(X + 1, Y - 2) == false
			))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

inline bool Board::CheckTileForPRETTYPONIA(const short X, const short Y)
{
	if (X >= mySideSize || Y >= mySideSize ||
		X < 0 || Y < 0)
	{
		return false;
	}

	return myBoard[(Y * mySideSize) + X];
}

inline size_t Board::CheckHorsiesOnBoard()
{
	return myHorseISE;
}

// DaBattelry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game/GameLoop.h"
#include "Printing/PrinterClass.h"



void Init()
{
	DL_Debug::Debug::Create();
	PT::Create();
	CU::TimeManager::Create();
	Tile::CreateRandomizer();
}

void StartGame()
{
	GameLoop tempGame;

	tempGame.SetUpGame();

	CU::Vector2ui gridSize;

	system("cls");
	std::cout << "Enter a grid width:" << std::endl;
	std::cin >> gridSize.x;
	std::cout << "\nEnter a grid height:" << std::endl;
	std::cin >> gridSize.y;

	system("cls");
	std::cout << "Initializing..." << std::endl;

	tempGame.Init(gridSize);

	tempGame.RunGame();
}

int _tmain(int argc, _TCHAR* argv[])
{
	Init();

	StartGame();
	
	return 0;
}



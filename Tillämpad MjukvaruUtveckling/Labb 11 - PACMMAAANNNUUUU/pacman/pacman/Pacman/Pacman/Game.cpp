#include "Game.h"

#include "TileGrid.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	TileGrid::Create();
	myPlayer.Init();
	myDotContainer.Init();
	myScoreCounter.Init();
	myCherry.Init();

	myEnemyContainer.Init();

	myConditions.Init();

}

bool Game::Update()
{
	myConditions.GetReady(myPlayer.GetLife());
	myPlayer.Update();
	myDotContainer.Update(myPlayer,myScoreCounter);
	myCherry.Update(myPlayer,myScoreCounter);
	myEnemyContainer.Update(myPlayer,myScoreCounter);

	if(myConditions.YouLose(myPlayer.GetLife()))
	{
		return false;
	}

 	if(myConditions.YouWin(myDotContainer.GetDotsLeft()))
 	{
		return false;
 	}
	
	return true;
}

void Game::Render()
{
	TileGrid::GetInstance()->Render();
	myDotContainer.Render();
	myCherry.Render();

	myEnemyContainer.Render();
	myPlayer.Render();

	myScoreCounter.Render();
	myConditions.Render();
	
}

#include "EnemyContainer.h"
#include "Enemy.h"
#include "Player.h"
#include "ScoreCounter.h"

EnemyContainer::EnemyContainer()
{
}

EnemyContainer::~EnemyContainer()
{
}

void EnemyContainer::Init()
{
	myEnemys.Init(4,10);

	Enemy* enemy = new Enemy();
	enemy->Init("Data/ghost3.png",CU::Vector2f(312.5f,362.5f),RANDOM);
	myEnemys.Add(enemy);

	enemy = new Enemy();
	enemy->Init("Data/ghost4.png",CU::Vector2f(337.5f,362.5f),AMBUSHER);
	myEnemys.Add(enemy);

	enemy = new Enemy();
	enemy->Init("Data/ghost.png",CU::Vector2f(362.5f,362.5f),RANDOM);
	myEnemys.Add(enemy);

	enemy = new Enemy();
	enemy->Init("Data/ghost2.png",CU::Vector2f(337.5f,287.5f),CHASER);
	myEnemys.Add(enemy);

	myScore = 100;


}
void EnemyContainer::Update(Player& aPlayer, ScoreCounter& aScoreCounter)
{

	bool resetPointMultiplyer = true;
	bool isDead = false;

	for(int i = 0; i < myEnemys.Count(); i++)
	{
		if(aPlayer.IsInvincible() == true)
		{
			myEnemys[i]->SetLifeState(KILLABLE);
			myEnemys[i]->ResetKillableTimer();
		}
		myEnemys[i]->Update(aPlayer);

		if(resetPointMultiplyer == true && myEnemys[i]->IsNotKillable() == false)
		{
			resetPointMultiplyer = false;
		}



		CU::Vector2f lengthVector = aPlayer.GetPosition();
		lengthVector -= myEnemys[i]->GetPosition();

		if(lengthVector.Length() < 12.5f)
		{
			if(myEnemys[i]->GetLifeState()== KILLABLE)
			{
				myEnemys[i]->SetLifeState(DEAD);
				myScore *= 2; 
				aScoreCounter.AddScore(myScore);
			}
			else if(myEnemys[i]->GetLifeState()== ALIVE)
			{
				aPlayer.Dead();
				isDead = true;
				
			}
		}
	}

	if(isDead == true)
	{
		for(int i = 0; i < myEnemys.Count(); i++)
		{
			myEnemys[i]->ResetPosition();
		}
	}

	if(resetPointMultiplyer == true)
	{
		myScore = 100;
	}

	aPlayer.SetIsInvincible(false);

}

void EnemyContainer::Render()
{
	for(int i = 0; i < myEnemys.Count(); i++)
	{
		myEnemys[i]->Render();

	}
}
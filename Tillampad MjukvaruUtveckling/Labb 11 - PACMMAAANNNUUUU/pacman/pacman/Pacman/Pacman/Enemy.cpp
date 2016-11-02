#include "Enemy.h"

#include "Player.h"
#include "TileGrid.h"
#include "TI_TimeManager.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(char* aTexturePath, CU::Vector2f aPosition, EnemyType aEnemyType)
{
	myVisualReps[ALIVE].Init(aTexturePath);
	myVisualReps[ALIVE].CenterHotspot();
	myVisualReps[KILLABLE].Init("Data/killableGhost.png");
	myVisualReps[KILLABLE].CenterHotspot();
	myVisualReps[DEAD].Init("Data/deadGhost.png");
	myVisualReps[DEAD].CenterHotspot();

	myLifeState = ALIVE;

	myPosition = aPosition;
	myStartPosition = aPosition;

	myMovementBehaviors.Init(myPosition);
	myMovementBehaviors.NewDirection();

	myBlinkTimer = 0.0f;
	myKillableTimer = 10.0f;
	myFollowPlayerTimer = 5.0f;
	myIsVisible = true;

	myIsFollowingPlayer = true;

	myEnemyType = aEnemyType;

}

void Enemy::Update(Player& aPlayer)
{
	if(myEnemyType == RANDOM)
	{
		Random();
	}
	else if(myEnemyType == CHASER)
	{
		Chaser();
	}
	else
	{
		Ambusher(aPlayer);
	}

}

void Enemy::Render()
{
	if(myIsVisible == true)
	{
		myVisualReps[myLifeState].Render(myPosition);
	}
}

const CU::Vector2f& Enemy::GetPosition()
{
	return myPosition;
}

void Enemy::SetLifeState( LifeStates aState )
{
	if(myLifeState != DEAD)
	{
		if(aState == KILLABLE)
		{
			myIsVisible = true;
			myMovementBehaviors.SetSpeed(75.0f);
		}
		
		myLifeState = aState;
	}
}

void Enemy::ResetPosition()
{
	myPosition = myStartPosition;
	myMovementBehaviors.NewDirection();
	myBlinkTimer = 0.0f;
	myKillableTimer = 10.0f;
	myFollowPlayerTimer = 5.0f;
	myIsVisible = true;
	myIsFollowingPlayer = true;
	myLifeState = ALIVE;
	myMovementBehaviors.ResetWaypoints();
}

void Enemy::Blink()
{
	myBlinkTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();

	if(myBlinkTimer > 0.1)
	{
		myIsVisible ^= 1;
		myBlinkTimer = 0;
	}

}

const LifeStates& Enemy::GetLifeState()
{
	return myLifeState;
}

void Enemy::TimeKillable()
{
	myKillableTimer -= TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();
	if(myKillableTimer < 3)
	{
		Blink();
	}
	if(myKillableTimer < 0)
	{
		myLifeState = ALIVE;
		if(myEnemyType == CHASER)
		{
			myMovementBehaviors.SetSpeed(200.0f);
		}
		else
		{
			myMovementBehaviors.SetSpeed(150.0f);
		}

		myIsVisible = true;
		myKillableTimer = 10.0f;
	}
}

bool Enemy::IsNotKillable()
{
	if(myKillableTimer == 10.0f)
	{
		return true;
	}

	return false;
}

void Enemy::ResetKillableTimer()
{
	myKillableTimer = 10.0f;
}

void Enemy::Random()
{
	if(myLifeState == DEAD)
	{
		if(myMovementBehaviors.MoveHome() == true)
		{
			myLifeState = ALIVE;
			myMovementBehaviors.SetSpeed(150.0f);
			myIsVisible = true;
			myKillableTimer = 10.0f;
			myMovementBehaviors.NewDirection();
		}
	}
	else if(myLifeState == KILLABLE)
	{
		myMovementBehaviors.MoveRandom();
		myMovementBehaviors.PortalThePlayer();
		TimeKillable();
	}
	else
	{
		myMovementBehaviors.MoveRandom();
		myMovementBehaviors.PortalThePlayer();
	}
}

void Enemy::Chaser()
{
	if(myLifeState == DEAD)
	{
		if(myMovementBehaviors.MoveHome() == true)
		{
			myLifeState = ALIVE;
			myMovementBehaviors.SetSpeed(200.0f);
			myIsVisible = true;
			myKillableTimer = 10.0f;
			myMovementBehaviors.NewDirection();
		}
	}
	else if(myLifeState == KILLABLE)
	{
		myMovementBehaviors.MoveRandom();
		myMovementBehaviors.PortalThePlayer();
		TimeKillable();
	}
	else
	{
		myMovementBehaviors.MoveRandom();
		myMovementBehaviors.PortalThePlayer();
	}
}

void Enemy::Ambusher(Player& aPlayer)
{
	if(myLifeState == DEAD)
	{
		if(myMovementBehaviors.MoveHome() == true)
		{
			myLifeState = ALIVE;
			myMovementBehaviors.SetSpeed(150.0f);
			myIsVisible = true;
			myKillableTimer = 10.0f;
			myMovementBehaviors.NewDirection();
		}
	}
	else if(myLifeState == KILLABLE)
	{
		myMovementBehaviors.ResetWaypoints();
		myMovementBehaviors.MoveRandom();
		myMovementBehaviors.PortalThePlayer();
		TimeKillable();
	}
	else
	{
		myFollowPlayerTimer -= TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();
		if(myFollowPlayerTimer < 0 && myIsFollowingPlayer == true)
		{
			if(myIsFollowingPlayer == true)
			{
				myIsFollowingPlayer = false;
				myFollowPlayerTimer = 10.0f;
				myMovementBehaviors.NewDirection();
			}
			else if(myIsFollowingPlayer == false)
			{
				myIsFollowingPlayer = true;
				myFollowPlayerTimer = 5.0f;
				myMovementBehaviors.NewDirection();
			}
		}
		if(myIsFollowingPlayer == false)
		{
			myMovementBehaviors.MoveRandom();
			
		}
		else
		{
			if(myMovementBehaviors.MoveToPlayer(aPlayer)==true)
			{
				myIsFollowingPlayer = false;
				myFollowPlayerTimer = 10.0f;
			}
			myMovementBehaviors.NewDirection();
		}

		myMovementBehaviors.PortalThePlayer();
	}
}
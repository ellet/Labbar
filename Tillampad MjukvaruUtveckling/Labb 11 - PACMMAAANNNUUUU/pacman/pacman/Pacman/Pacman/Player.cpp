#include "Player.h"

#include "TI_TimeManager.h"
#include "TileGrid.h"
#include "HgeSingelton.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	myVisualRep.Init("Data/player.png");
	myVisualRep.CenterHotspot();
	myOpenMouthRep[UP].Init("Data/playerUp.png");
	myOpenMouthRep[UP].CenterHotspot();

	myOpenMouthRep[DOWN].Init("Data/playerDown.png");
	myOpenMouthRep[DOWN].CenterHotspot();

	myOpenMouthRep[LEFT].Init("Data/playerLeft.png");
	myOpenMouthRep[LEFT].CenterHotspot();

	myOpenMouthRep[RIGHT].Init("Data/playerRight.png");
	myOpenMouthRep[RIGHT].CenterHotspot();

	mySize = 12.5f;
	myCheckSize = 13.5f;

	TileGrid::GetInstance()->GetPixelFromTile(CU::Vector2f(3,3));
	myPosition.Set(487.5f,562.5f);
	myVelocity.Set(0,0);
	myCurrentVelocity.Set(0,0);

	myIsInvincible = false;

	myLife = 2;
	myMouthTimer = 0.0f;

	myMouthIsOpen = true;
	myMoveState = LEFT;
	myCurrentMoveState = LEFT;

	mySpeed = 150.0f;
}

void Player::Update()
{
	InputUpdate();

	/*if((myCurrentVelocity.x != myVelocity.x || myCurrentVelocity.y != myVelocity.y) && TileGrid::GetInstance()->IsWalkable(myPosition+(myCurrentVelocity*myCheckSize) - (myVelocity * mySize)) && TileGrid::GetInstance()->IsWalkable(myPosition + (myCurrentVelocity*myCheckSize) + (myVelocity * mySize)))
	{
		myMoveState = myCurrentMoveState;
		myVelocity = myCurrentVelocity;
	}*/

	if (myVelocity.Length2() > 0.f)
	{
		CU::Vector2f oldPosition = myPosition;
		OpenMouthTimer();

		if (TileGrid::GetInstance()->IsWalkable(myPosition + myVelocity * myCheckSize))
		{
			myPosition += (myVelocity*mySpeed)*TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();
		}
		else
		{
			myVelocity.Set(0.f, 0.f);
			myPosition.x = static_cast<float>(static_cast<int>(myPosition.x) / TileGrid::GetInstance()->GetTileSize() * TileGrid::GetInstance()->GetTileSize()) + myCheckSize;
			myPosition.y = static_cast<float>(static_cast<int>(myPosition.y) / TileGrid::GetInstance()->GetTileSize() * TileGrid::GetInstance()->GetTileSize()) + myCheckSize;
		}

		int oldTileX = static_cast<int>((oldPosition.x - myCheckSize) / TileGrid::GetInstance()->GetTileSize());
		int oldTileY = static_cast<int>((oldPosition.y - myCheckSize) / TileGrid::GetInstance()->GetTileSize());
		int newTileX = static_cast<int>((myPosition.x - myCheckSize) / TileGrid::GetInstance()->GetTileSize());
		int newTileY = static_cast<int>((myPosition.y - myCheckSize) / TileGrid::GetInstance()->GetTileSize());

		bool isTargetOnSameAxis = myMoveState == myCurrentMoveState;
		if (myMoveState == UP && myCurrentMoveState == DOWN)
			isTargetOnSameAxis = true;
		if (myMoveState == DOWN && myCurrentMoveState == UP)
			isTargetOnSameAxis = true;
		if (myMoveState == LEFT && myCurrentMoveState == RIGHT)
			isTargetOnSameAxis = true;
		if (myMoveState == RIGHT && myCurrentMoveState == LEFT)
			isTargetOnSameAxis = true;

		if (isTargetOnSameAxis == false)
		{
			if (oldTileX != newTileX)
			{
				if (TileGrid::GetInstance()->IsWalkable(myPosition + myCurrentVelocity * (myCheckSize + 2.f)))
				{
					myPosition.x = std::floorf(myPosition.x / TileGrid::GetInstance()->GetTileSize()) * TileGrid::GetInstance()->GetTileSize() + mySize;
					myMoveState = myCurrentMoveState;
					myVelocity = myCurrentVelocity;
				}
			}
			if (oldTileY != newTileY)
			{
				if (TileGrid::GetInstance()->IsWalkable(myPosition + myCurrentVelocity * (myCheckSize + 2.f)))
				{
					myPosition.y = std::floorf(myPosition.y / TileGrid::GetInstance()->GetTileSize()) * TileGrid::GetInstance()->GetTileSize() + mySize;
					myMoveState = myCurrentMoveState;
					myVelocity = myCurrentVelocity;
				}
			}
		}
		else
		{
			myVelocity = myCurrentVelocity;
			myMoveState = myCurrentMoveState;
		}
	}
	else
	{
		myVelocity = myCurrentVelocity;
		myMoveState = myCurrentMoveState;
	}
	

	PortalThePlayer();
}

void Player::Render()
{
	if(myMouthIsOpen == false)
	{
		myVisualRep.Render(myPosition);
	}
	else
	{
		myOpenMouthRep[myMoveState].Render(myPosition);
	}
	
}

void Player::InputUpdate()
{
	if(HGES->Input_GetKeyState(HGEK_UP) == true)
	{
		myCurrentMoveState = UP;
		myCurrentVelocity.Set(0,-1);
	}
	else if(HGES->Input_GetKeyState(HGEK_DOWN) == true)
	{
		myCurrentMoveState = DOWN;
		myCurrentVelocity.Set(0,1);
	}
	else if(HGES->Input_GetKeyState(HGEK_LEFT) == true)
	{
		myCurrentMoveState = LEFT;
		myCurrentVelocity.Set(-1,0);
	}
	else if(HGES->Input_GetKeyState(HGEK_RIGHT) == true)
	{
		myCurrentMoveState = RIGHT;
		myCurrentVelocity.Set(1,0);
	}
		
}

const CU::Vector2f& Player::GetPosition()
{
	return myPosition;
}

const float& Player::GetSize()
{
	return mySize;
}

void Player::PortalThePlayer()
{
	if(myPosition.x < 0 && myVelocity.x == -1)
	{
		myPosition.x = 650;
	}
	else if(myPosition.x > 650 && myVelocity.x == 1)
	{
		myPosition.x = 0;
	}
}

void Player::ResetPosition()
{
	myPosition.Set(487.5f,562.5f); 
	myVelocity.Set(0,0);
	myCurrentVelocity.Set(0,0);
}

bool Player::IsInvincible()
{
	return myIsInvincible;
}

void Player::SetIsInvincible(bool aBool)
{
	myIsInvincible = aBool;
}


void Player::Dead()
{
	TI_Time::TimeManager::GetInstance()->SetClockPauseState(TI_Time::GAME_CLOCK_01,true);
	myLife--;
	ResetPosition();
}

int Player::GetLife()
{
	return myLife;
}

void Player::OpenMouthTimer()
{
	myMouthTimer += TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime();
	if(myMouthTimer > 0.1)
	{
		myMouthIsOpen^=1;
		myMouthTimer = 0.0f;
	}

}

#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	myMoney = 100.f;
	myIsAlive = true;
}


Player::~Player()
{
}

void Player::ChangeMoney(float aChangeWith)
{
	myMoney += aChangeWith;
}

float Player::GetMoney()
{
	return myMoney;
}

bool Player::GetAlive()
{
	return myIsAlive;
}

void Player::PlayerDied()
{
	myIsAlive = false;
}
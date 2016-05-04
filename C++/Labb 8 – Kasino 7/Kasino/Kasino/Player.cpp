#include "stdafx.h"
#include "Player.h"
#include <iostream>

bool CheckNameValidity(const std::string & aNameToCheck);
bool CheckLetter(const char & ch);

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

std::string Player::GetPlayerName()
{
	return myUserName;
}

void Player::TellSetPlayerName()
{
	std::string tmpName;
	do
	{
		std::cout << "What is your name?" << std::endl;
		std::getline(std::cin, tmpName);
	} while (CheckNameValidity(tmpName));
	
	myUserName = tmpName;
}

bool CheckNameValidity(const std::string & aNameToCheck)
{
	if (aNameToCheck.size() == 0)
	{
		std::cout << "You must input a name" << std::endl;
		return true;
	}
	for (int iCheckEachLetter = 0; iCheckEachLetter < static_cast<int>(aNameToCheck.size()); iCheckEachLetter++)
	{
		if (!CheckLetter(aNameToCheck[iCheckEachLetter]))
		{
			std::cout << "You can only use alphabetical letters" << std::endl;
			return true;
		}
	}
	return false;
}

bool CheckLetter(const char & ch)
{
	if (!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch == ' ') || (ch == '-') || (ch == 'é')))
	{
		return false;
	}
	else
	{
		return true;
	}
}
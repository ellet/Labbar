#pragma once
#include <string>

class Player
{
public:
	Player();
	~Player();

	void ChangeMoney(float aChangeWith);
	float GetMoney();
	bool GetAlive();
	void PlayerDied();
	std::string GetPlayerName();
	void TellSetPlayerName();

private:
	float myMoney;
	bool myIsAlive;
	std::string myUserName;
};


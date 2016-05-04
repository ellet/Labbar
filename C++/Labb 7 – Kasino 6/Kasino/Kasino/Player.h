#pragma once
class Player
{
public:
	Player();
	~Player();

	void ChangeMoney(float aChangeWith);
	float GetMoney();
	bool GetAlive();
	void PlayerDied();

private:
	float myMoney;
	bool myIsAlive;
};


#pragma once
#include <mutex>


struct Account
{
	Account()
	{
		myBalance = 0.0;
	}
	Account(const Account& aCopy)
	{

	}
	double myBalance;
	void Sync() { myMutex.lock(); }
	void Release() { myMutex.unlock(); }
private:
	std::mutex myMutex;
};

class CDeadlock
{
public:
	CDeadlock();
	~CDeadlock();
	void Run();

private:
	static void Transfer(Account* from, Account* to, double amount);

	static void Withdraw(Account* anAcount, double amount);
	static void Deposit(Account* anAcount, double amount);

	Account myFirstAccount;
	Account mySecondAccount;
};


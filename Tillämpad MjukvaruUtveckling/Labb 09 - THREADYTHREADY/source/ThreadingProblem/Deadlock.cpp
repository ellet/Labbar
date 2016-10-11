#include "Deadlock.h"
#include <thread>         // std::thread
#include <functional>
#include <assert.h>

using namespace std::placeholders;

volatile bool myIsOkToTransfer = false;  // Simulates that two transactions happens at once

CDeadlock::CDeadlock()
{
}


CDeadlock::~CDeadlock()
{
}

void CDeadlock::Run()
{
	myFirstAccount.myBalance = 50;
	mySecondAccount.myBalance = 50;

	std::thread first(&CDeadlock::Transfer, &myFirstAccount, &mySecondAccount, 50); // Take 50kr from Account one and give to Account two
	std::thread second(&CDeadlock::Transfer, &mySecondAccount, &myFirstAccount, 50); // Take 50kr from Account TWO and give to Account one
	
	myIsOkToTransfer = true; // Simulates that two transactions happens at once


	second.join();
	first.join();

	assert(myFirstAccount.myBalance == mySecondAccount.myBalance && myFirstAccount.myBalance == 50 && "account balances not equal");

	// Both account should end up with 50kr each
}

void CDeadlock::Transfer(Account* from, Account* to, double amount)
{
	while (!myIsOkToTransfer)
	{
		continue;
	}
	from->Sync();
	Withdraw(from, amount);
	from->Release();
	to->Sync();
	Deposit(to, amount);
	to->Release();
}

void CDeadlock::Withdraw(Account* anAcount, double amount)
{
	anAcount->myBalance -= amount;
}

void CDeadlock::Deposit(Account* anAcount, double amount)
{
	anAcount->myBalance += amount;
}
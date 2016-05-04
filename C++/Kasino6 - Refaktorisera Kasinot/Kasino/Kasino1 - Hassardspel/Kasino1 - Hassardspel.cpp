// Kasino1 - Hassardspel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Kasino1 - Hassardspel.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	
	Kasino::GameMenu();

	return 0;
}
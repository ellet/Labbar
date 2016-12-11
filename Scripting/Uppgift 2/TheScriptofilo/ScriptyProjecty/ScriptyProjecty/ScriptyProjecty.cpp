// ScriptyProjecty.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Script\ScriptSystem.h"


int main()
{
	ScriptSystem::Create();

	std::system("pause");

	ScriptSystem::Destroy();
    return 0;
}


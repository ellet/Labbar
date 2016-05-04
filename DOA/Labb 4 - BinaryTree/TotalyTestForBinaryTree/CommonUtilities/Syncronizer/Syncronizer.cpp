#include "Syncronizer.h"


Syncronizer::Syncronizer()
{
	myThreads.Init(5);
	myThreadsShouldRun = true;
}


Syncronizer::~Syncronizer()
{
}


#include "Work.h"


Work::Work(const WorkFunction & someWork)
{
	myWork = someWork;
}

Work::~Work()
{
}

void Work::DoWork() const
{
	myWork();
}

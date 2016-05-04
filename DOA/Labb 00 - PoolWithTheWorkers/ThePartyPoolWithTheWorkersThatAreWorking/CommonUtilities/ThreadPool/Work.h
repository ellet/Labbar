#pragma once
#include <functional>

typedef std::function<void(void)> WorkFunction;

class Work
{
public:
	Work(const WorkFunction & someWork);
	~Work();

	void DoWork() const;

private:
	WorkFunction myWork;


};


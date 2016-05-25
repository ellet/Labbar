#pragma once
#include <string>

class CeePlusPlusClass
{
public:
	CeePlusPlusClass();
	~CeePlusPlusClass();

	void SetApa(const int aNumber);

	int GetApa() const;

	void SetText(const std::string & aTexty);

	const std::string & GetTexty();

private:
	int myApa;
	std::string myText;
};


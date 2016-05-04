#pragma once
#include <string>
#include "Buff.h"

class VitalStat
{
public:
	VitalStat(const enumVitalTypes aVitalType);
	~VitalStat();

	void TimeCheckBuffs(const unsigned int aTurnCount);

	void GetPrintOfVital(std::string & aStringToAddTo) const;

	void SetVital(const float aVitalValue, const bool aKeepPercentage = false);

	void ChangeVital(const float aChangeWith);

	enumVitalTypes GetVitalType() const;

	float GetVitalValue() const;

	bool GetVitalState() const;

	float GetVitalhPercentage() const;

	void RecalculateValue();

	void AddMainBuff(const Buff & aBuffToAdd);

	void AddTempBuff(const Buff & aBuffToAdd);

	unsigned int GetMainBuffCount() const;

	unsigned int GetTempBuffCount() const;

	void ClearMainBuffs();

private:
	void RemoveTempBuff(unsigned int aTempBuffIndex);

	void SetType(const enumVitalTypes aVitalType);
	void SetNameFromType();
	void CheckVitalIsCorrect();
	void CheckVital();

	enumVitalTypes myType;
	std::string myName;

	std::vector<Buff> myMainBuffs;
	std::vector<Buff> myTempBuffs;

	float myVitalValue;
	float myBaseValue;
	float myMaxVital;
	bool myVitalIsPositive;
};


#pragma once
#include <vector>
#include "VitalStat.h"
#include "Buff.h"

class VitalsManager
{
public:
	VitalsManager();
	~VitalsManager();

	void PrintVitals() const;

	bool GetVitalState(const enumVitalTypes aVitalToCheck) const;

	void IncreaseVital(const float aIncreaseWith, const enumVitalTypes aVitalToIncrease);

	void SetVital(const float aValueToSetTo, const enumVitalTypes aVitalToSet);

	void ReceiveMainBuffs(const std::vector<Buff> & aVectorOfStatBuffs);

	void AddMainBuffToVital(const Buff aBuffToAdd);

	void AddTempBuffToVital(const Buff aBuffToAdd);

	float GetVitalValue(const enumVitalTypes aVitalType) const;

	void TimeCheckTrigger(const unsigned int aTurnCount);

	void ChangeVital(const float aValueToChangeWith, const enumVitalTypes aVitalToChange);

	VitalStat & GetVitalStat(const enumVitalTypes aVitalToGet);

private:
	void ClearAllMainBuffs();

	void CreateAllVitals();


	std::vector<VitalStat> myVitals;

};


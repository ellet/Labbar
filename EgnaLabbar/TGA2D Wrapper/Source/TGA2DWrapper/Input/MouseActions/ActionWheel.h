#pragma once
//#include "WheelOption.h"
#include <GrowingArray/GrowingArray.h>
#include <DLDebug/DL_Debug.h>
#include <string>
#include "BaseWheelOption.h"

#include "../../../Game/Object/ElemenTypes.h"

class Object;
class BaseWheelOption;

class ActionWheel
{
public:
	ActionWheel();
	~ActionWheel();

	void Update();
	void Draw();

	bool inline GetActiveState();

	void inline SetIsActive();
	void inline SetIsDisabled();

	void inline SetActiveObject(Object* const aObjectPointer);

	void inline ActivateElementalAction(const eElementType aTypeToActive);

	void inline PreparePositions();

	void CheckIfSphereIsFullyInsideWorld(Vector2f & aPositionToCheckAndChange);

	inline std::string MyFirePath() const;
	inline void MyFirePath(std::string val);
	inline std::string MyWindPath() const;
	inline void MyWindPath(std::string val);
	inline std::string MyWaterPath() const;
	inline void MyWaterPath(std::string val);
	inline std::string MyEarthPath() const;
	inline void MyEarthPath(std::string val);
	inline std::string MyClickPath() const;
	inline void MyClickPath(std::string val);
	inline std::string MyExaminePath() const;
	inline void MyExaminePath(std::string val);
private:
	bool myIsActive;
	Object * myActiveObject;

	float myRangeFromCenter;
	float mySizeOfActionBall;

	void SetPositions();

	CU::GrowingArray<BaseWheelOption*> myWheelOptions;
	std::string myFirePath;
	std::string myWindPath;
	std::string myWaterPath;
	std::string myEarthPath;
	std::string myClickPath;
	std::string myExaminePath;
};


bool ActionWheel::GetActiveState()
{
	return myIsActive;
}

void ActionWheel::SetIsActive()
{
	myIsActive = true;

	//SetPositions();
}

void ActionWheel::SetIsDisabled()
{
	myIsActive = false;
}

void ActionWheel::SetActiveObject(Object* const aObjectPointer)
{
	DL_ASSERT(aObjectPointer != nullptr, "Mouse input Recieved object nullptr");
	myActiveObject = aObjectPointer;
}

inline std::string ActionWheel::MyFirePath() const { return myFirePath; }
inline void ActionWheel::MyFirePath(std::string val) { myFirePath = val; myWheelOptions[static_cast<unsigned short>(eElementType::eFire)]->SetWheelSprite(myFirePath); }
inline std::string ActionWheel::MyWindPath() const { return myWindPath; }
inline void ActionWheel::MyWindPath(std::string val) { myWindPath = val;  myWheelOptions[static_cast<unsigned short>(eElementType::eWind)]->SetWheelSprite(myWindPath); }
inline std::string ActionWheel::MyWaterPath() const { return myWaterPath; }
inline void ActionWheel::MyWaterPath(std::string val) { myWaterPath = val;  myWheelOptions[static_cast<unsigned short>(eElementType::eWater)]->SetWheelSprite(myWaterPath); }
inline std::string ActionWheel::MyEarthPath() const { return myEarthPath; }
inline void ActionWheel::MyEarthPath(std::string val) { myEarthPath = val; myWheelOptions[static_cast<unsigned short>(eElementType::eEarth)]->SetWheelSprite(myEarthPath); }
inline std::string ActionWheel::MyClickPath() const { return myClickPath; }
inline void ActionWheel::MyClickPath(std::string val) { myClickPath = val;  myWheelOptions[4]->SetWheelSprite(myClickPath); }
inline std::string ActionWheel::MyExaminePath() const { return myExaminePath; }
inline void ActionWheel::MyExaminePath(std::string val) { myExaminePath = val;  myWheelOptions[5]->SetWheelSprite(myExaminePath); }



void ActionWheel::ActivateElementalAction(const eElementType aTypeToActive)
{
	myWheelOptions[static_cast<unsigned short>(aTypeToActive)]->ActiveWheelOption();
}

inline void ActionWheel::PreparePositions()
{
	SetPositions();
}
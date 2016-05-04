#pragma once
#include "..\..\TGA2DWrapper\BaseClasses\BaseGameObject\BaseAnimatedObject\BaseAnimatedGameObject.h"
#include <string>

#include <GrowingArray\GrowingArray.h>
#include "ElemenTypes.h"

class Event;
struct EventCollider;
class PlayDialogEvent;


class Object : public BaseAnimatedGameObject
{
public:
	Object();
	~Object();

	void Init(std::string &aName);
	const std::string &GetName() const;
	void SetEventCollider(EventCollider *aEventColldier);
	void Update(const float aDeltaTime) override;
	void SetPositionAndCollider(const Vector2f & aPosition);
	void AddElementEvent(eElementType aElementType, Event *aEvent);
	void SetExamineEvent(PlayDialogEvent * const aDialogueEvent);
	void TriggerElementEvent(eElementType aElementType);
	void TriggerOnUse();
	void TriggerOnExamine();
	void SetName(const std::string aString);
	


private:

	std::string myName;
	EventCollider *myEventCollider;

	PlayDialogEvent * myExamineEvent;

	CommonUtilities::GrowingArray<Event*> myFireEvents;
	CommonUtilities::GrowingArray<Event*> myWindEvents;
	CommonUtilities::GrowingArray<Event*> myWaterEvents;
	CommonUtilities::GrowingArray<Event*> myEarthEvents;
};


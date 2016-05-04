#pragma once
#include "Event.h"
#include <string>

class PlayDialogEvent : public Event

{
public:
	PlayDialogEvent(std::string &aAvatarID, std::string &aText);
	~PlayDialogEvent();

	virtual void OneShotEvent() override;
private:
	std::string myAvatarID;
	std::string myText;
};


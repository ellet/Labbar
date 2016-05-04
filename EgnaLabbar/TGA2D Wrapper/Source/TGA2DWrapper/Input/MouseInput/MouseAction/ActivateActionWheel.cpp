#include "ActivateActionWheel.h"
#include "../MouseInput.h"

ActivateActionWheel::ActivateActionWheel()
{
}


ActivateActionWheel::~ActivateActionWheel()
{
}

void ActivateActionWheel::DoOnRelease()
{
	MouseInput::ActivateWheel();
}

void ActivateActionWheel::DoOnClick()
{
	MouseInput::PrepareActionWheel();
}

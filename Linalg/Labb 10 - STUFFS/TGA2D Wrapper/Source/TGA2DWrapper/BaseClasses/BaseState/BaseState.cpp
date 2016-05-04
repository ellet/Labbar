#include "BaseState.h"

BaseState::BaseState()
{
	myActiveFlagDraw = true;
	myActiveFlagUpdate = true;
}
BaseState::~BaseState()
{
}

void BaseState::Init()
{

}

void BaseState::Update(const float aDeltaTime)
{
	(aDeltaTime);
}
void BaseState::Draw() const
{
}

void BaseState::DoOnChangeFrom()
{

}

void BaseState::DoOnChangeTo()
{

}

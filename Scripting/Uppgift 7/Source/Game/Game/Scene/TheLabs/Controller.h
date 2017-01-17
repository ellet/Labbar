#pragma once

class Unit;

namespace SB
{
	class GuiRenderTarget;
}

class Controller
{
public:
	Controller(const Unit & aParentUnit);
	virtual ~Controller();

	virtual SB::Vector2f GetDirection(const SB::Time & aDeltaTime);
	
	const SB::Vector2f & GetPosition();
	SB::Vector2f GetFuturePosition(const float aTimeDelta) const;

	const Unit * GetUnit() const;

	virtual void DebugRender(const SB::GuiRenderTarget & aRenderTarget) const;

protected:
	SB::Vector2f myDirection;
	const Unit * myUnit;
};


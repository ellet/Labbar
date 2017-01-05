#include "stdafx.h"
#include "Unit.h"
#include "Engine\Texture\GuiRenderTarget.h"
#include "PollingStation.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"


Unit::Unit()
{
	PollingStation::RegisterUnit(*this);

	myController = nullptr;

	SetSprite("Sprites/unit.dds");

	mySprite.SetOrigin(SB::Vector2f(32.f, 32.f));

	SB::Randomizer temp;

	mySpeed = SB::Vector2f::Zero;//SB::Vector2f::UnitX * SB::Matrix33f::CreateRotateAroundZ(temp.GetRandomValue(0.f, 2.f));
	myDirection = SB::Vector2f::UnitX;

	myRadius = 32.f;
}


Unit::~Unit()
{
	PollingStation::UnRegisterUnit(*this);
}

float Unit::GetRadius() const
{
	return myRadius;
}

const SB::Vector2f & Unit::GetPosition() const
{
	return myPosition;
}

void Unit::SetPosition(const SB::Vector2f & aPosition)
{
	myPosition = aPosition;
}

SB::Vector2f Unit::GetDirection() const
{
	return mySpeed.GetNormalized();
}

SB::Vector2f Unit::GetFuturePosition(const float aTimeDelta) const
{
	return GetPosition() + (GetSpeed() * aTimeDelta);
}

const SB::Vector2f & Unit::GetSpeed() const
{
	return mySpeed;
}

void Unit::Update(const SB::Time aDeltaTime)
{
	if (myController != nullptr)
	{
		SB::Vector2f currentDirectionAndSpeed = myController->GetDirection(aDeltaTime);

		mySpeed = currentDirectionAndSpeed;
	}

	if (mySpeed != SB::Vector2f::Zero)
	{
		SB::Vector2f delta = mySpeed * aDeltaTime.InSeconds();
		myPosition += delta;
	}

	mySprite.SetPosition(myPosition);
}


void Unit::Render(const SB::GuiRenderTarget & aRenderTargetToRenderTo)
{
	aRenderTargetToRenderTo.Render(mySprite);
}

void Unit::DebugRender(const SB::GuiRenderTarget & aRenderTargetToRenderTo)
{
	if (myController != nullptr)
	{
		myController->DebugRender(aRenderTargetToRenderTo);
	}
}

Controller & Unit::GetController()
{
	return *myController;
}

void Unit::SetSprite(const std::string & aFilePath)
{
	mySprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>(aFilePath));
}

#pragma once

class Actor;

class BaseController
{
public:
	BaseController(const Actor & aActor);
	virtual ~BaseController();

	virtual SB::Vector2f Update(const float aDeltaTime) = 0;

	const SB::Vector2f GetPosition() const;
	const Actor & GetActor() const;

private:
	const Actor * myActor;
};


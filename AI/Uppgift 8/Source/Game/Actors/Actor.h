#pragma once
#include "Rendering\BDSprite.h"

class BaseController;

class Actor
{
public:
	Actor();
	~Actor();

	template<typename ControllerType>
	ControllerType & SetController()
	{
		ControllerType * newController = new ControllerType(*this);
		myController = newController;
		return *newController;
	}

	void Update(const float aDeltaTime);
	void Render() const;

	void SetSprite(const std::string & aFilePath);

	const SB::Vector2f & GetPosition() const;
	void SetPosition(const SB::Vector2f aPosition);
	void AddToPosition(const SB::Vector2f & aDelta);

private:
	BaseController * myController;
	SB::Vector2f myPosition;
	BDSprite mySprite;
};


#pragma once
#include "Controller.h"
#include "FormationController.h"

class FormationGroup;

class Unit
{
public:
	Unit();
	~Unit();

	float GetRadius() const;
	const SB::Vector2f & GetPosition() const;

	void SetPosition(const SB::Vector2f & aPosition);
	
	template <typename TControllerType>
	void SetControllerType()
	{
		if (myController != nullptr)
		{
			delete myController;
			myController = nullptr;
		}

		myController = new TControllerType(*this);
	}

	//template <typename TControllerType>
	void SetControllerType(FormationGroup & aGroup)
	{
		if (myController != nullptr)
		{
			delete myController;
			myController = nullptr;
		}

		myController = new FormationController(*this, aGroup);
	}

	void SetTargetPosition(const unsigned short aVolumeIndex);

	void SetIndex(const unsigned short aIndex);

	SB::Vector2f GetDirection() const;
	SB::Vector2f GetFuturePosition(const float aTimeDelta) const;
	const SB::Vector2f & GetSpeed() const;

	void Update(const SB::Time aDeltaTime);
	void Render(const SB::GuiRenderTarget & aRenderTargetToRenderTo);
	void DebugRender(const SB::GuiRenderTarget & aRenderTargetToRenderTo);

	Controller & GetController();

	unsigned short GetTargetIndex() const;
	void SetSprite(const std::string & aFilePath);
private:
	void ReachedTarget();

	SB::Vector2f myTargetPosition;
	unsigned short myTargetIndex;

	unsigned short myIndex;
	SB::Sprite mySprite;
	SB::Vector2f myPosition;
	SB::Vector2f myDirection;
	float myRadius;
	SB::Vector2f mySpeed;
	Controller * myController;
};


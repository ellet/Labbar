#pragma once
#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <string>

class InterfaceBase : public BaseGameObject
{
public:
	InterfaceBase();
	~InterfaceBase();
	void Draw()const override;
	void SetShowInterface(bool aShow);
	bool GetIsShowing() const;
	void SetIsShowing(bool aValue);
	std::string Getname();
protected:
	bool myShowInterface;
	std::string myName;
};


#pragma once
#include "..\Engine\Engine\Input\InputListener.h"

class OptionsScene : public SB::Scene
{
public:
	OptionsScene(SB::PostMasterState & aPostMasterState);
	~OptionsScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;
	virtual void OnEnter() override;

private:
	void Return();
	void Derpy();

	std::shared_ptr<SB::InputListener> myInputListener;
	bool myBloomToggle;

protected:
	virtual void BindGUIFunctions() override;

};


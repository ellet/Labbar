#pragma once
#include "..\Engine\Engine\Input\InputListener.h"

class CreditsScene : public SB::Scene
{
public:
	CreditsScene(SB::PostMasterState & aPostMasterState);
	~CreditsScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;
	virtual void OnEnter() override;

private:
	void BackToMainMenu();
	std::shared_ptr<SB::InputListener> myInputListener;

protected:
	virtual void BindGUIFunctions() override;

};


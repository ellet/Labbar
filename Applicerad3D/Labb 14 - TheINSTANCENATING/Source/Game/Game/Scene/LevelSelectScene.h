#pragma once
#include "..\Engine\Engine\Input\InputListener.h"
class LevelSelectScene : public SB::Scene
{
public:
	LevelSelectScene(SB::PostMasterState & aPostMasterState);
	~LevelSelectScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;


	virtual void OnEnter() override;


private:
	void StartLevel(unsigned short aLevelPath);
	void BackToMainMenu();
	std::shared_ptr<SB::InputListener> myInputListener;
	

protected:
	virtual void BindGUIFunctions() override;

};


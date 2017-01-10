#pragma once
#include <Engine\Scene\Scene.h>


class YlfTestScene :
	public SB::Scene
{
public:
	YlfTestScene(SB::PostMasterState & aPostMasterState);
	~YlfTestScene();

	//virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;
	virtual void OnEnter() override;

private:


};


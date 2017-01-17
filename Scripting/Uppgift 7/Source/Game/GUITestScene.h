#pragma once
class GUITestScene : public SB::Scene
{
public:
	GUITestScene(SB::PostMasterState & aPostMasterState);
	~GUITestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

	virtual void OnEnter() override;
	void TestClickFunction();
	void TestHoverFunction();
	void TestKeyFunction();

protected:
	virtual void BindGUIFunctions() override;
};


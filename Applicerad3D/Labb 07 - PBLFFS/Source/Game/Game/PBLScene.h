#pragma once

#include <Engine/Scene/Scene.h>

class PBLScene : public Scene
{
public:
	PBLScene();
	~PBLScene();

	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

private:
	void CreateFactories();

};